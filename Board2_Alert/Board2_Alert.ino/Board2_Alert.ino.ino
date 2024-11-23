#include <EEPROM.h>
#include <avr/io.h>

// Use a pointer for the EEPROM address
int eepromAddress = 0;
int *eepromAddressPtr = &eepromAddress;

void setup() {
    Serial.begin(9600);
    Serial.println("Board 2 initialized.");
}

void loop() {
    if (Serial.available()) {
        // Use a pointer to handle incoming data
        String data = Serial.readStringUntil('\n');
        String *dataPtr = &data;

        Serial.print("Board 2 received: ");
        Serial.println(*dataPtr);

        logToEEPROM(dataPtr);        // Pass data as a pointer
        forwardToBoard3(dataPtr);   // Pass data as a pointer
    }
}

void logToEEPROM(String *dataPtr) {
    for (int i = 0; i < dataPtr->length(); i++) {
        EEPROM.update(*eepromAddressPtr + i, (*dataPtr)[i]);
    }
    *eepromAddressPtr += dataPtr->length() + 1; // Update the address using the pointer
    Serial.println("Data logged to EEPROM.");
}

void forwardToBoard3(String *dataPtr) {
    Serial.println("Forwarding data to Board 3:");
    Serial.println(*dataPtr);
}
