# Packages
1. gpio - interfaces with gpio pins on the raspberry pi
2. joystick drivers - interfaces with linux-supported joysticks (not currently employed)
3. led_control - toggles car LEDs based on drive commands
4. lidar - accesses data from the lidar
5. media - various images from the car's development and performance
6. navigation - defines parameters for controlling move_base
7. pathing - includes all driving algorithms and central nodes for handling sensor data and user input
8. pixy - acceses data from the pixy
9. racecar - launches all teleop files, sends drive commands to the vesc, and defines static transforms
10. serial - reads and writes data across external devices
11. slam - updates envionment map based on new lidar data
12. twist-to-ackermann - converts geomteric commands from the navigation stack into ackermann commands
13. velma - launches the entire system and sets up a default rviz environment
14. vesc - interfaces with the vesc to control the steering and wheel motors
