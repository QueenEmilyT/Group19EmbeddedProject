#include <DHT.h>

#define DHT_PIN 2           // DHT data pin on PD2
#define BUTTON_PIN 3        // Button on PD3 (INT1)
DHT dht(DHT_PIN, DHT11);
volatile bool sendData = false;

void setup() {
    DDRD &= ~(1 << DHT_PIN); // Set DHT pin as input (PD2)
    DDRD &= ~(1 << BUTTON_PIN); // Set button pin as input with pull-up (PD3)
    PORTD |= (1 << BUTTON_PIN); // Enable pull-up resistor for button
    EICRA |= (1 << ISC11);      // Falling edge interrupt on INT1
    EIMSK |= (1 << INT1);       // Enable INT1
    Serial.begin(9600);
    dht.begin();
    sei();
    Serial.println("Board 1 initialized.");
}

void loop() {
    if (sendData) {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        if (!isnan(temperature) && !isnan(humidity)) {
            sendTemperatureHumidity(temperature, humidity);
            delay(1000);
        } else {
            Serial.println("Failed to read from DHT sensor.");
        }
    }
}

void sendTemperatureHumidity(float temperature, float humidity) {
    Serial.print("T:");
    Serial.print(temperature);
    Serial.print(" H:");
    Serial.println(humidity);
    Serial.println("Data sent from Board 1."); // Debug
}

ISR(INT1_vect) {
    sendData = !sendData;
}