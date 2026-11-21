/*
  INTELLIGENT FOUR-LANE ADAPTIVE TRAFFIC SIGNAL
  Board: ESP32 30-pin development board
  Sensors: 4 x HC-SR04 ultrasonic modules

  IMPORTANT:
  - HC-SR04 ECHO is 5V. Use a voltage divider on EVERY ECHO line.
  - GPIO pin assignment is a proposed mapping; verify your exact board labels.
  - GPIO2 is a strapping pin (default low on the classic ESP32). In this
    mapping it drives an LED wired from GPIO through a resistor to GND;
    verify boot behavior on the exact board before permanent assembly.
  - This is sensor-based adaptive control, not an AI/ML model.

  Timing:
  Distance <= 50 cm:   20 seconds green
  Distance <= 100 cm:  15 seconds green
  Distance <= 150 cm:  10 seconds green
  Distance <= 200 cm:   5 seconds green
  No valid detection: skip lane
  Yellow: 2 seconds
*/

#include <Arduino.h>

constexpr uint8_t LANE_COUNT = 4;
constexpr float DETECTION_LIMIT_CM = 200.0f;
constexpr uint32_t ECHO_TIMEOUT_US = 25000UL;
constexpr uint32_t SENSOR_GAP_MS = 60UL;
constexpr uint32_t YELLOW_TIME_MS = 2000UL;
constexpr uint32_t ALL_RED_CLEARANCE_MS = 300UL;

// Proposed pins for a common 30-pin ESP32 DevKit.
// Echo pins 34, 35, 36 and 39 are input-only, which is suitable for ECHO.
const uint8_t TRIG_PINS[LANE_COUNT] = {13, 14, 16, 17};
const uint8_t ECHO_PINS[LANE_COUNT] = {34, 35, 36, 39};

// LED order: red, yellow, green
const uint8_t RED_PINS[LANE_COUNT]    = {18, 22, 26, 2};
const uint8_t YELLOW_PINS[LANE_COUNT] = {19, 23, 27, 4};
const uint8_t GREEN_PINS[LANE_COUNT]  = {21, 25, 32, 33};

float distanceCm[LANE_COUNT];

float readDistanceCm(uint8_t lane) {
  digitalWrite(TRIG_PINS[lane], LOW);
  delayMicroseconds(3);
  digitalWrite(TRIG_PINS[lane], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PINS[lane], LOW);

  const unsigned long duration =
      pulseIn(ECHO_PINS[lane], HIGH, ECHO_TIMEOUT_US);

  delay(SENSOR_GAP_MS); // helps reduce cross-talk between adjacent sensors

  if (duration == 0) {
    return -1.0f; // no echo / out of range
  }

  return (duration * 0.0343f) / 2.0f;
}

void setAllRed() {
  for (uint8_t lane = 0; lane < LANE_COUNT; lane++) {
    digitalWrite(RED_PINS[lane], HIGH);
    digitalWrite(YELLOW_PINS[lane], LOW);
    digitalWrite(GREEN_PINS[lane], LOW);
  }
}

uint8_t greenSecondsForDistance(float cm) {
  if (cm < 0.0f || cm > DETECTION_LIMIT_CM) return 0;
  if (cm <= 50.0f) return 20;
  if (cm <= 100.0f) return 15;
  if (cm <= 150.0f) return 10;
  return 5;
}

void showGreen(uint8_t lane, uint8_t seconds) {
  setAllRed();

  Serial.printf("Lane %u: GREEN for %u seconds (distance %.1f cm)\n",
                lane + 1, seconds, distanceCm[lane]);

  digitalWrite(RED_PINS[lane], LOW);
  digitalWrite(GREEN_PINS[lane], HIGH);
  delay((uint32_t)seconds * 1000UL);

  digitalWrite(GREEN_PINS[lane], LOW);
  digitalWrite(YELLOW_PINS[lane], HIGH);
  Serial.printf("Lane %u: YELLOW for 2 seconds\n", lane + 1);
  delay(YELLOW_TIME_MS);

  setAllRed();
  delay(ALL_RED_CLEARANCE_MS);
}

void scanAllLanes() {
  for (uint8_t lane = 0; lane < LANE_COUNT; lane++) {
    distanceCm[lane] = readDistanceCm(lane);

    Serial.printf("Lane %u distance: ", lane + 1);
    if (distanceCm[lane] < 0.0f) {
      Serial.println("No echo");
    } else {
      Serial.printf("%.1f cm\n", distanceCm[lane]);
    }
  }
}

void setup() {
  Serial.begin(115200);

  for (uint8_t lane = 0; lane < LANE_COUNT; lane++) {
    pinMode(TRIG_PINS[lane], OUTPUT);
    pinMode(ECHO_PINS[lane], INPUT);
    digitalWrite(TRIG_PINS[lane], LOW);

    pinMode(RED_PINS[lane], OUTPUT);
    pinMode(YELLOW_PINS[lane], OUTPUT);
    pinMode(GREEN_PINS[lane], OUTPUT);
  }

  setAllRed();
  Serial.println("\nFour-lane adaptive traffic signal started.");
  Serial.println("Open Serial Monitor at 115200 baud.");
}

void loop() {
  scanAllLanes();

  bool anyVehicleDetected = false;

  // Simple round-robin service: each detected lane is served in lane order.
  for (uint8_t lane = 0; lane < LANE_COUNT; lane++) {
    const uint8_t greenSeconds = greenSecondsForDistance(distanceCm[lane]);

    if (greenSeconds > 0) {
      anyVehicleDetected = true;
      showGreen(lane, greenSeconds);
    }
  }

  if (!anyVehicleDetected) {
    setAllRed();
    Serial.println("No vehicle detected within 200 cm. All lanes remain RED.");
    delay(500);
  }
}
