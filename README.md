# Intelligent Four-Lane Adaptive Traffic Signal Using ESP32

A four-lane educational traffic-signal prototype using an ESP32 and four HC-SR04 ultrasonic sensors. Each lane is checked for a nearby object/vehicle, and the green duration is selected from the measured distance.

> **Accuracy note:** This is sensor-based adaptive control. It does not currently contain an AI or machine-learning model, and it does not count individual vehicles.

## Features
- Four independent lane-detection sensors
- ESP32-based signal control
- Distance bands determine green duration
- 2-second yellow transition
- All other lanes are held red while one lane is green
- Serial Monitor distance/status output

## Hardware
- 1 × ESP32 30-pin development board
- 4 × HC-SR04 ultrasonic modules
- 4 × red LEDs
- 4 × yellow LEDs
- 4 × green LEDs
- 12 × LED current-limiting resistors (typically 220–330 ohms)
- 4 × ECHO voltage-divider networks (one per HC-SR04)
- Breadboard and jumper wires
- Suitable regulated power supply

## Proposed pin mapping
See [`hardware/pin_connections.md`](hardware/pin_connections.md). Verify the printed labels on the exact ESP32 board before wiring.

## Timing logic
| Measured distance | Green duration |
|---|---:|
| 0–50 cm | 20 s |
| >50–100 cm | 15 s |
| >100–150 cm | 10 s |
| >150–200 cm | 5 s |
| No echo or >200 cm | Skip lane |

Yellow duration: 2 seconds. The prototype serves detected lanes in a simple lane 1 → lane 4 round-robin order.

## Uploading
1. Install Arduino IDE and the Espressif ESP32 board package.
2. Open `src/traffic_signal.ino`.
3. Select the correct ESP32 board and COM port.
4. Upload the sketch.
5. Open Serial Monitor at 115200 baud.
6. Test one sensor and one lane at a time before connecting all hardware.

## Safety and electrical notes
- **Never connect an HC-SR04 ECHO output directly to an ESP32 GPIO.** The common HC-SR04 operates at 5 V and its ECHO signal can be 5 V; ESP32 GPIOs are not 5 V tolerant. Use a voltage divider or appropriate level shifter on each ECHO output.
- A typical divider is 1 kΩ from ECHO to the GPIO junction and 2 kΩ from the junction to GND. Confirm the resulting voltage before connecting.
- Power HC-SR04 modules from a suitable 5 V supply and connect all grounds together.
- Use one current-limiting resistor per LED.
- GPIO2 is a boot-strapping pin on the classic ESP32. The proposed mapping uses it for Lane 4 red and its default low level is compatible with the active-high LED-to-GND arrangement, but verify boot behavior on the exact board.
- Do not connect real road traffic lights or deploy this prototype on public roads. It is an educational model only.

## Limitations
- Ultrasonic distance is only a rough proxy for queue demand; it cannot reliably count vehicles or measure queue length by itself.
- The fixed lane-order sequence may cause unnecessary delay if an earlier lane has repeated detections.
- Sensor cross-talk, vehicle angle, weather, and mounting height can affect readings.
- This code is a newly reconstructed baseline, not the original lost source code. It must be bench-tested and tuned against the actual prototype.

## Future work
- Vehicle counting using suitable sensors or computer vision
- Emergency vehicle priority
- Fairness/maximum-wait scheduling
- Camera-based traffic classification
- IoT dashboard and logging
- A validated AI/ML traffic prediction model

## Project status
Four-lane hardware prototype reported complete by the project owner. Source code in this repository is a reconstructed starting version and has not been verified against the physical wiring.
