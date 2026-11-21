# Project Overview

## Problem
Fixed-time traffic signals allocate the same green time regardless of detected traffic demand. This small-scale prototype explores adaptive timing using distance measurements.

## Objective
Build a four-lane educational traffic signal controlled by an ESP32, with one ultrasonic sensor per lane.

## Proposed approach
The ESP32 sequentially measures each HC-SR04 sensor. A valid distance within 200 cm is mapped to a green-time band. The selected lane receives green, then yellow, while all other lanes remain red.

## Scope
This is a tabletop/educational prototype. It is not certified for road deployment and is not an AI/ML system.
