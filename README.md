# F1TENTH VELMA

source code written by the 2022-2023 ucsb f1tenth capstone team

written for ros noetic on ubuntu 20.04.

## Required packages
```
ros-noetic-slam-toolbox
ros-noetic-navigation
ros-noetic-tf2-geometry-msgs
ros-noetic-ackermann-msgs
ros-noetic-map-server
python-is-python3
git libusb-1.0-0-dev g++ build-essential
```

## Usage
```
roslaunch velma velma.launch
```
## Driving Modes
1. Manual Control - 'k'
3. Wall Follow - 'p'
4. Gap Follow - 'g'
5. Return to starting point - 'h'
6. Navigate to selected point on RVIZ map - 'n'
7. Begin to log waypoints of car's path - 'l'
8. Recall and navigate to logged waypoints in sequential order indefinitely - 'r'
9. Explore unknown areas of the environment - 'e'
10. Search for an object of a certain color in the environment (color specified by pixy settings) - 's'

## Required Hardware
1. Raspberry Pi 4
2. RP Lidar S2
3. VESC 6 MK V
4. RC car
