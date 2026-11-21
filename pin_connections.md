# Hardware and Pin Connections

## Proposed ESP32 30-pin mapping

| Lane | HC-SR04 TRIG | HC-SR04 ECHO (through divider) | Red LED | Yellow LED | Green LED |
|---|---:|---:|---:|---:|---:|
| 1 | GPIO13 | GPIO34 | GPIO18 | GPIO19 | GPIO21 |
| 2 | GPIO14 | GPIO35 | GPIO22 | GPIO23 | GPIO25 |
| 3 | GPIO16 | GPIO36 | GPIO26 | GPIO27 | GPIO32 |
| 4 | GPIO17 | GPIO39 | GPIO2* | GPIO4 | GPIO33 |

`*` GPIO5 is a classic ESP32 strapping pin. Its external circuit must not disturb the required boot level. If boot is unreliable, change the pin design or use an I/O expander. Check the exact board schematic/pinout before wiring; 30-pin board layouts are not all identical.

## HC-SR04 wiring (repeat for all four sensors)
- VCC → regulated 5 V
- GND → common GND
- TRIG → assigned ESP32 GPIO
- ECHO → voltage divider → assigned ESP32 GPIO

### ECHO voltage divider
Use a 1 kΩ resistor from the sensor ECHO pin to a junction. Connect a 2 kΩ resistor from that junction to GND. Connect the junction to the ESP32 ECHO GPIO. This reduces a nominal 5 V ECHO signal to about 3.33 V. Use a divider for each sensor, not one shared divider.

## LED wiring
For each LED: assigned GPIO → series resistor (220–330 Ω) → LED anode; LED cathode → GND. Confirm LED polarity. Do not connect an LED without a current-limiting resistor.

## Common ground and power
- ESP32 GND, all sensor GNDs, and LED supply GND must be common.
- Do not power four HC-SR04 modules from an overloaded 3.3 V output. Use a suitable regulated 5 V supply.
- Ensure the ESP32 is powered through its supported USB/5 V input arrangement. Avoid feeding 5 V into a GPIO.

No circuit diagram is included because the project owner has not supplied one and does not want a fabricated diagram.
