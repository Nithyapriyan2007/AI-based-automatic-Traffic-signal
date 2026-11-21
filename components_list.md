# Components List

| Component | Quantity | Notes |
|---|---:|---|
| ESP32 30-pin development board | 1 | Verify exact board revision |
| HC-SR04 ultrasonic sensor | 4 | 5 V module assumed |
| Red LED | 4 | One per lane |
| Yellow LED | 4 | One per lane |
| Green LED | 4 | One per lane |
| LED current-limiting resistor | 12 | Typically 220–330 Ω |
| ECHO voltage-divider resistors | 8 | Per sensor: 1 kΩ + 2 kΩ |
| Breadboard | 1 or more | Based on prototype layout |
| Jumper wires | As required | Male/female as appropriate |
| Regulated 5 V supply | 1 | Must support sensor current |

The user confirmed the ESP32, four HC-SR04 sensors, red/yellow/green LEDs with resistors, and breadboard. The resistor values and 5 V supply details above are recommended implementation requirements and must be checked against the parts actually available.
