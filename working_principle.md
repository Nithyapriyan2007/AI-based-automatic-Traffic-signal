# Working Principle

1. Each HC-SR04 emits an ultrasonic burst when triggered.
2. The sensor's ECHO pulse duration is used to estimate distance.
3. The ESP32 checks whether the measured distance is within 200 cm.
4. A distance band selects a green duration of 5, 10, 15, or 20 seconds.
5. The selected lane turns green; all other lanes stay red.
6. The selected lane turns yellow for 2 seconds.
7. The controller proceeds to the next detected lane.
8. If no lane has a valid detection, all signals remain red.

Distance is used only as a rough demand indicator. It does not directly measure the number of waiting vehicles.
