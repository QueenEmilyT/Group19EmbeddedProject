#include <DHT.h>

#define DHT_PIN 2           // DHT data pin on PD2
#define BUTTON_PIN 3        // Button on PD3 (INT1)

DHT dht(DHT_PIN, DHT11);

volatile bool sendData = false;

void setup() {
    // Use pointers to modify DDRD and PORTD registers
    volatile uint8_t *ddrD = &DDRD;
    volatile uint8_t *portD = &PORTD;

    *ddrD &= ~(1 << DHT_PIN);       // Set DHT pin as input (PD2)
    *ddrD &= ~(1 << BUTTON_PIN);   // Set button pin as input with pull-up (PD3)
    *portD |= (1 << BUTTON_PIN);   // Enable pull-up resistor for button

    // Use pointers for EICRA register
    volatile uint8_t *eicra = &EICRA;
    *eicra |= (1 << ISC11);        // Falling edge interrupt on INT1

    Serial.begin(9600);

    // Use pointer to call the begin function
    DHT *dhtPointer = &dht;
    dhtPointer->begin();

    sei();

    Serial.println("Board 1 initialized.");
}

void loop() {
    if (sendData) {
        // Use pointer to access readTemperature and readHumidity
        DHT *dhtPointer = &dht;
        float temperature = dhtPointer->readTemperature();
        float humidity = dhtPointer->readHumidity();

        if (!isnan(temperature) && !isnan(humidity)) {
            sendTemperatureHumidity(&temperature, &humidity); // Pass pointers to the function
            delay(1000);
        } else {
            Serial.println("Failed to read from DHT sensor.");
        }
    }
}

void sendTemperatureHumidity(float *temperature, float *humidity) {
    // Dereference pointers to print values
    Serial.print("T:");
    Serial.print(*temperature);
    Serial.print(" H:");
    Serial.println(*humidity);
    Serial.println("Data sent from Board 1."); // Debug
}

// ISR uses a pointer to toggle sendData
ISR(INT1_vect) {
    volatile bool *sendDataPtr = &sendData;
    *sendDataPtr = !(*sendDataPtr);
}