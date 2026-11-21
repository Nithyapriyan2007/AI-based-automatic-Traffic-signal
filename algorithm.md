# Control Algorithm

```text
START
  |
Initialize ESP32 pins and Serial Monitor
  |
Set all lanes RED
  |
Read ultrasonic sensors for lanes 1 to 4
  |
For each lane:
  |-- No echo or distance > 200 cm -> skip
  |-- distance <= 50 cm -> green 20 s
  |-- distance <= 100 cm -> green 15 s
  |-- distance <= 150 cm -> green 10 s
  |-- otherwise (<= 200 cm) -> green 5 s
  |
After green -> yellow 2 s -> all red clearance
  |
Repeat
```

The initial implementation is a simple round-robin scan, not a globally optimized traffic scheduler.
