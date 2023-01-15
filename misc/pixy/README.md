
# pixy2_ros

## Dependencies
* libpixyusb is included as a git submodule and will be build during installation
* libusb-1.0.0 is required
* something like `sudo apt install libusb-1.0-0-dev` installs the header files

## Installation
```
cd ~/catkin_ws/src
git clone --recurse-submodules https://github.com/zhiquanyeo/pixy2_ros.git
cd ~/catkin_ws
catkin_make
```

## udev rules for non-root user
To use pixy2 over USB as a non-root user, udev rules must be configured.  
The 'pixy.rules' file must be copied to '/etc/udev/rules.d'

```
cd ~/catkin_ws/src/pixy2_ros/pixy2_node/pixy2/src/host/linux
sudo cp pixy.rules /etc/udev/rules.d/
```

## Run
```
rosrun pixy2_node pixy2_node
```
Must be run as `root` if udev rules have not been installed.

## Parameters
`~frame_id` (string, default: pixy_frame)  
`~rate` (float, default: 50.0)  
`~use_servos` (bool, default: true)  
`~maxRetries` (int, default: 10)  
`~retryWaitTime` (float, default: 10.0)  
`~enable_lamp`(bool, default: false)  
`~queue_size` (int, default: 50)  
