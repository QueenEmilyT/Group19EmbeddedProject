#include <EEPROM.h>
#include <avr/io.h>

int eepromAddress = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Board 2 initialized.");
}

void loop() {
    if (Serial.available()) {
        String data = Serial.readStringUntil('\n');
        Serial.print("Board 2 received: ");
        Serial.println(data);
        logToEEPROM(data);
        forwardToBoard3(data);
    }
}

void logToEEPROM(String data) {
    for (int i = 0; i < data.length(); i++) {
        EEPROM.update(eepromAddress + i, data[i]);
    }
    eepromAddress += data.length() + 1;
    Serial.println("Data logged to EEPROM.");
}

void forwardToBoard3(String data) {
    Serial.println("Forwarding data to Board 3:");
    Serial.println(data);
}
