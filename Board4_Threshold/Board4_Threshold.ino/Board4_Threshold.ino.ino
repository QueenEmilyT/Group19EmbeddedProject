#define PIN_READY_3 PD5 // Signal from Board 3

void setup() {
    // Use pointers for DDRD and Serial initialization
    volatile uint8_t *ddrD = &DDRD;
    volatile uint8_t *portD = &PIND;

    *ddrD &= ~(1 << PIN_READY_3); // Set PIN_READY_3 as input
    Serial.begin(9600);
    Serial.println("Board 4 initialized.");
}

void loop() {
    // Use a pointer to read PIN_READY_3
    volatile uint8_t *pinD = &PIND;

    if (*pinD & (1 << PIN_READY_3)) { // Check if Board 3 is ready to send data
        if (Serial.available()) {
            // Use a pointer for the received data
            String data = Serial.readStringUntil('\n');
            String *dataPtr = &data;

            Serial.print("Board 4 received: ");
            Serial.println(*dataPtr);

            displayData(dataPtr); // Pass the data pointer to the function
        }
    }
}

void displayData(String *dataPtr) {
    // Parse temperature and humidity from the data string
    int tempIndex = dataPtr->indexOf("T:") + 2;
    int humIndex = dataPtr->indexOf("H:") + 2;

    if (tempIndex != -1 && humIndex != -1) {
        // Extract and convert the values using pointers
        String tempStr = dataPtr->substring(tempIndex, dataPtr->indexOf(" ", tempIndex));
        String humStr = dataPtr->substring(humIndex);

        float temperature = tempStr.toFloat();
        float humidity = humStr.toFloat();
        float *temperaturePtr = &temperature;
        float *humidityPtr = &humidity;

        // Output parsed values
        Serial.print("Parsed Temperature: ");
        Serial.println(*temperaturePtr);
        Serial.print("Parsed Humidity: ");
        Serial.println(*humidityPtr);
        Serial.print("Temperature: ");
        Serial.print(*temperaturePtr);
        Serial.println(" C");
        Serial.print("Humidity: ");
        Serial.print(*humidityPtr);
        Serial.println(" %");
    } else {
        Serial.println("Invalid data format!");
    }
}
