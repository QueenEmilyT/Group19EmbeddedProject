Temperature Alarm System Using Arduino

Overview
This project, developed by Group 19, is a Temperature Alarm System using four interconnected Arduino boards to monitor temperature and humidity, log data, and trigger alerts when readings exceed predefined thresholds. It can be deployed in various environments, including:

- Server rooms to prevent overheating.
- Greenhouses for monitoring plant health.
- Warehouses storing sensitive goods to prevent spoilage.
- Industrial facilities where environmental control is crucial.

The system helps ensure timely alerts to maintain stable conditions in these areas.

Components
The key components used in this project are:

1. Arduino Boards (x4): Handles data processing and different tasks.
2. DHT11 Sensor: Measures temperature and humidity.
3. Push Button: Toggles data transmission and controls system functions.
4. LED/Buzzer: Provides alert notifications.
5. EEPROM: Logs data for persistent storage.
6. Resistors and Jumper Wires: Ensure proper connections and current control.

 System Design and Functionality
The system consists of four main boards, each assigned specific tasks:

Board 1: Temperature and Humidity Sensing
- Reads temperature and humidity data using a DHT11 sensor**.
- Toggles data transmission with a push button.
- Uses ADC (Analog-to-Digital Converter)for sensor readings and GPIO for input/output handling.
- Configured with external interrupts for button presses using EICRA and EIMSK registers.

Board 2: Data Logging
- Receives sensor data from Board 1.
- Logs data into EEPROM for persistent storage.
- Forwards data to Board 3 for further processing.

Board 3: Threshold Check and Alert Trigger
- Receives data from Board 2 and checks against predefined thresholds (e.g., 25°C for temperature, 70% for humidity).
- Activates an alert (LED/Buzzer) if values exceed thresholds.
- Signals Board 4 for data readiness.

Board 4: Data Display
- Receives processed data from Board 3.
- Displays the temperature and humidity readings on the serial monitor.
- Uses signaling pins to manage communication with Board 3.

 Technical Implementation
- Serial Communication: Utilizes TX/RX pins for data transfer between boards.
- EEPROM Storage: Stores readings to maintain data after power loss.
- Interrupts and Debouncing: Ensures accurate button presses and stable input.
- Threshold Alert System: Monitors readings and triggers an alert if limits are breached.
- Shared Ground: Ensures proper communication between all boards by connecting them to a common ground.

Serial Communication Setup
The communication setup between the boards is as follows:

- Board 1 TX (D1) → Board 2 RX (D0)
- Board 2 TX (D1) → Board 3 RX (D0)
- Board 3 TX (D1) → Board 4 RX (D0)
- Board 4 TX (D1) → Board 3 RX (D0)
- Signaling Pins (PD5 and PD6)**: Used for handshaking between Board 3 and Board 4.

Note:
All boards must be connected to a **shared ground** for proper signal interpretation and reliable operation.

How to Run the Project
1. Setup the Arduino IDE and install the required libraries for DHT11 and EEPROM.
2. Upload the code to each Arduino board as per their designated tasks (Board 1 to Board 4).
3. Connect the components as per the circuit design:
   - Attach the DHT11 sensor to Board 1.
   - Connect LEDs/Buzzer for alerts.
   - Ensure the ground (GND) pins of all boards are connected.
4. Power on the system and monitor the serial output for temperature and humidity readings.

 Troubleshooting
- No Data Transmission: Check the TX/RX connections and ensure proper serial communication setup.
- Incorrect Sensor Readings: Verify the connections to the DHT11 sensor and ensure it’s functioning properly.
- Alert Not Triggering: Check the threshold values set in the code and ensure the alert components (LED/Buzzer) are connected correctly.
- EEPROM Data Loss: Ensure proper use of `EEPROM.update()` instead of `EEPROM.write()` to prevent excessive wear.

Future Enhancements
- Integration with Wi-Fi or Bluetooth modules for remote monitoring.
- Adding a display (LCD/OLED) for real-time data visualization.
- Implementing a web dashboard for historical data analysis.






