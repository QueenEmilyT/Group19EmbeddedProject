//board 3
#include <avr/io.h>
#define ALERT_PIN PD4 // LED or Buzzer
#define PIN_READY_3 PD5 // Signal to Board 4
#define PIN_READY_4 PD6 // Signal from Board 4
const int tempThreshold = 25; // Temperature threshold
const int humThreshold = 70; // Humidity threshold
void setup() { 
 // Use pointers for DDRD and PORTD
 volatile uint8_t *ddrD = &DDRD; 
 volatile uint8_t *portD = &PORTD; 
 *ddrD |= (1 << ALERT_PIN) | (1 << PIN_READY_3); // Set ALERT_PIN and 
PIN_READY_3 as outputs
 *ddrD &= ~(1 << PIN_READY_4); // Set PIN_READY_4 as input
 Serial.begin(9600); 
 Serial.println("Board 3 initialized."); 
} 
void loop() { 
 if (Serial.available()) { 
 String data = Serial.readStringUntil('\n'); 
 String *dataPtr = &data; 
 Serial.print("Board 3 received: "); 
 Serial.println(*dataPtr); 
 checkThresholds(dataPtr); // Pass data as a pointer
 // Wait for Board 4 to be ready
 while (PIND & (1 << PIN_READY_4)) { 
 delay(10); 
 } 
 // Use a pointer to manipulate PORTD
 volatile uint8_t *portD = &PORTD; 
 *portD |= (1 << PIN_READY_3); // Signal to Board 4
 Serial.println(*dataPtr); 
 *portD &= ~(1 << PIN_READY_3); // Clear signal
 } 
} 
void checkThresholds(String *dataPtr) { 
 int tempIndex = dataPtr->indexOf("T:") + 2; 
 int humIndex = dataPtr->indexOf("H:") + 2; 
 String tempStr = dataPtr->substring(tempIndex, dataPtr->indexOf(" ", 
tempIndex)); 
 String humStr = dataPtr->substring(humIndex); 
 // Use pointers for temperature and humidity
 float temperature = tempStr.toFloat(); 
 float humidity = humStr.toFloat(); 
 float *temperaturePtr = &temperature; 
 float *humidityPtr = &humidity; 
 volatile uint8_t *portD = &PORTD; 
 if (*temperaturePtr > tempThreshold || *humidityPtr > humThreshold) { 
 *portD |= (1 << ALERT_PIN); // Trigger alert
 Serial.println("Alert: Temperature/Humidity threshold exceeded!"); 
 } else { 
 *portD &= ~(1 << ALERT_PIN); // Reset alert
 } 
} 
