#F1TENTH

source code used by the ucsb f1tenth capstone team to control their car.

written for the intended use of ros noetic on ubuntu 20.04.

this repo contains three separate projects.

first, the "basic" directory contains the full code that was used to control the f1tenth car in 2018 by UPenn. we will not be using this structure, but we will draw from the layout and source code.

second, the 'simulator' directory contains the full code that was used to launch our first prototype demo. this is the structure we will use, but we need to adjust the code since it is only a simulator.

third, the 'velma' directory contains the full code that will be used for our final project. it is a work in progress.

the misc directory contains any extra files and the source code for each of the hardware drivers.

#Typical Setup From Scratch

Install Raspberry Pi Imager
Dowload “ubuntu-20.04.4-preinstalled-server-arm64+raspi.img.xz” from here
Write file to SD card using the Imager
If you cannot write, erase the data on the sd card and format it anew
Hook up pi to monitor
Insert SD card to pi and turn on
Username and password are both “ubuntu” originally.
Edit file /etc/netplan/50-cloud-init.yaml and paste the following:
wifis:
  wlan0:
    dhcp4: true
    optional: true
    access-points:
      "network SSID":
        password: "wifi password"
Reboot. Should have wifi now
Update. Upgrade. Do not upgrade to ubuntu 22.04 if prompted
Install ubuntu-desktop and reboot
Configure user settings if you want
Pin terminal to taskbar as you’ll be using it a lot
In terminal, install ROS noetic:
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt install ros-noetic-desktop-full
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo rosdep init
rosdep update
 Install VNC Server on the pi
sudo dpkg --add-architecture armhf && sudo apt update
Open this link in firefox on the pi https://github.com/raspberrypi/firmware/tree/master/opt/vc/lib
Click on each of the following titles and hit the “Download” button for each one
libbcm_host.so
libvcos.so
libmmal.so
libmmal_core.so
libmmal_components.so
libmmal_util.so
libmmal_vc_client.so
libvchiq_arm.so
libvcsm.so
Libcontainers.so
cd into the Downloads directory
Move each of these 10 downloaded files into /usr/lib 
sudo mv ~/Downloads/{file_name} /usr/lib
Open this link in firefox on the pi to download the server https://www.realvnc.com/download/file/vnc.files/VNC-Server-6.7.2-Linux-ARM.deb
cd into the directory containing the above link (probably Downloads)
sudo dpkg -i VNC-Server-6.7.2-Linux-ARM.deb
Start and enable VNC Server (enabling allows vnc server to start automatically in the future when the pu turns on)
sudo systemctl start vncserver-x11-serviced.service
sudo systemctl enable vncserver-x11-serviced.service
Install Real VNC Viewer on your laptop
On pi, enter VNC credentials
sudo vnclicensewiz
Open VNC Viewer on laptop and type in pi ip address to connect. Use ubuntu as username when prompted (and whatever password you set up before installing the desktop)
Configure VNC to work without a monitor
sudo apt-get install xserver-xorg-video-dummy
sudo nano /usr/share/X11/xorg.conf.d/xorg.conf
Section "Device"
    Identifier  "Configured Video Device"
    Driver      "dummy"
EndSection

Section "Monitor"
    Identifier  "Configured Monitor"
    HorizSync 31.5-48.5
    VertRefresh 50-70
EndSection

Section "Screen"
    Identifier  "Default Screen"
    Monitor     "Configured Monitor"
    Device      "Configured Video Device"
    DefaultDepth 24
    SubSection "Display"
    Depth 24
    Modes "1920x1080"
    EndSubSection
EndSection
sudo reboot
Should be able to vnc into the pi a minute or two after you turn it on
Get the code
mkdir f1tenth
cd f1tenth
mkdir src
cd src
git clone https://github.com/Tyler-Hattori/capstone.git
Update github credentials so that you can push and pull
Option 1:
Create personal access token in github if you don’t have one
On laptop, update github credentials to reflect the PAT (keyring for mac, credentials manager for windows). Once you do this you should be able to push and pull.
Option 2:
For Mac, in terminal “brew install gh”
For Windows, in terminal “scoop install gh”
For Linux, in terminal 
type -p curl >/dev/null || sudo apt install curl -y
curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | sudo dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg \
&& sudo chmod go+r /usr/share/keyrings/githubcli-archive-keyring.gpg \
&& echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | sudo tee /etc/apt/sources.list.d/github-cli.list > /dev/null \
&& sudo apt update \
&& sudo apt install gh -y
gh auth login
Select HTTPS and authenticate on the web
Get pigpio package for controlling gpio pins on the pi
wget https://github.com/joan2937/pigpio/archive/master.zip
unzip master.zip
cd pigpio-master
make
sudo make install
sudo apt install python-setuptools python3-setuptools
Configure and build pixy libraries and dependencies
sudo apt-get install git libusb-1.0-0-dev g++ build-essential
cd ~/f1tenth/src/pixy/pixy2_node/pixy2/src/host/linux
sudo cp pixy.rules /etc/udev/rules.d/
cd ~/f1tenth/src/pixy/pixy2_node/pixy2/scripts && ./build_libpixyusb2.sh
Install slam toolbox and navigation stack
sudo apt install ros-noetic-slam-toolbox
sudo apt install ros-noetic-navigation
cd ~/f1tenth
catkin_make




CLI
Task
Command
General CLI Tools


Update github repository
cd {repository}
git add .
git commit -m ‘message for team’
git push
Update files to match github repository
git pull
Update
sudo apt update
Upgrade
sudo apt upgrade
Change into directory
cd {directory_name}
List available directories
ls
Make directory
mkdir {directory_name}
Move back a directory
cd ..
Remove file
Rm (file}
Run next command as superuser
sudo
Edit file
sudo nano {file}
Kill process
Ctrl+C
List USB connections
lsusb
Get ip address
hostname -I
General ROS Tools


Install package
sudo apt install {package}
List active nodes/topics
rosnode/rostopic list
Get info about a node/topic
rosnode/rostopic info {node/topic}
See data getting passed through a topic
rostopic echo {topic}
See active nodes and topics graphically
rqt_graph
Launch all nodes
roslaunch velma velma.launch
Launch lidar driver
roslaunch rplidar_ros view_rplidar_s2.launch
Launch pixy driver
roslaunch pixy2_node pixy2.launch
Launch simulator driver
roslaunch f1tenth_simulator simulator.launch
Run gpio input driver
rosrun gpio_control gpio_control --device pi --input {pin_num} 
Run gpio output driver
rosrun gpio_control gpio_control --device pi --output {pin_num} 
Run gpio driver for multiple pins
rosrun gpio_control gpio_control_node --device pi --output {pin} {pin} {pin} --input {pin} {pin} {pin}
Launch vesc driver








Install
Task
Process
f110 2018 code


packages


git add .
git commit -m ‘message for team’
git push
Update files to match github repository
git pull
Update
sudo apt update
Upgrade
sudo apt upgrade
Change into directory
cd {directory_name}
List available directories
ls
Make directory
mkdir {directory_name}
Move back a directory
cd ..
Remove file
Rm (file}
Run next command as superuser
sudo
Edit file
sudo nano {file}
Kill process
Ctrl+C
List USB connections
lsusb
Get ip address
hostname -I
General ROS Tools


Install package
sudo apt install {package}
List active nodes/topics
rosnode/rostopic list
Get info about a node/topic
rosnode/rostopic info {node/topic}
See data getting passed through a topic
rostopic echo {topic}
See active nodes and topics graphically
rqt_graph
Launch all nodes
roslaunch velma velma.launch
Launch lidar driver
roslaunch rplidar_ros view_rplidar_s2.launch
Launch pixy driver
roslaunch pixy2_node pixy2.launch
Launch simulator driver
roslaunch f1tenth_simulator simulator.launch
Run gpio input driver
rosrun gpio_control gpio_control --device pi --input {pin_num} 
Run gpio output driver
rosrun gpio_control gpio_control --device pi --output {pin_num} 
Run gpio driver for multiple pins
rosrun gpio_control gpio_control_node --device pi --output {pin} {pin} {pin} --input {pin} {pin} {pin}
Launch vesc driver







