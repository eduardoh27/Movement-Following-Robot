# Movement-Following Robot

## Project Description
This is the final project for the Electronics course, where we've developed a robot programmed in Arduino that can track and follow movement. It's a combination of hardware interfacing and software development aimed at creating a responsive robotic system.

## Repository Structure
- `/archive`: Contains older versions of code and tests, project proposals, and references.
- `/diagrams`: Holds diagrams of the robot's design and circuitry.
- `/multimedia`: Includes various media files such as photos from the project's stages and explanatory videos.
- `/src`: The source code for the Arduino, which is the brain of the robot.

## Hardware Components
The robot utilizes standard electronics components compatible with Arduino, including motion sensors, motors, and a power supply unit.

## Software
The code for the robot is written in Arduino (C/C++). There are two main Arduino scripts:
- `car.ino`: The main script that handles the motion tracking and response.
- `sound_screen.ino`: An auxiliary script to manage additional sensor inputs and outputs.

## Getting Started
To get started with the project:
1. Assemble the hardware according to the diagrams provided.
2. Install the Arduino IDE on your computer.
3. Open the `.ino` files in the Arduino IDE.
4. Connect your Arduino to your computer and upload the code.

## Usage
Once the robot is powered on and the code is uploaded:
- The robot will automatically start scanning for movement.
- Upon detecting movement, it will activate its motors to follow the source.
