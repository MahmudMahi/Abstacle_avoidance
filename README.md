# Arduino Robot Control Code

This repository contains Arduino code for controlling a robot, featuring both manual Bluetooth control and autonomous obstacle avoidance.

## Files

* **`RC_car_bluetooth.ino`**:
    * This file contains the code for manual control of the robot via Bluetooth.
    * The robot can be controlled using a smartphone app that sends commands via Bluetooth serial communication.
    * This version focuses solely on manual operation.
* **`just_autonomous.cpp`**:
    * This file contains the code for autonomous obstacle avoidance.
    * The robot uses an ultrasonic sensor (sonar) to detect obstacles and navigate around them.
    * This version focuses solely on autonomous operation.
* **`obs_avoidance.ino`**:
    * This file represents an attempt to merge the manual Bluetooth control and autonomous obstacle avoidance functionalities into a single sketch.
    * **Status:** This version is currently under development and does not function as expected.
    * **Note:** This file requires further optimization and debugging to achieve proper integration of both control modes.
