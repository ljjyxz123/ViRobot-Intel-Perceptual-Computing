intel_ros
=========

Intel_ros project in Windows

##1. Scope

Our application is designed in *ROS(Robot Operating System)* framework, include two part of code:  
[intel_ros](https://github.com/yuanboshe/intel_ros.git) (get from https://github.com/yuanboshe/intel_ros.git)  
[intel_ros_vm](https://github.com/yuanboshe/intel_ros_vm.git) (get from https://github.com/yuanboshe/intel_ros_vm.git)  

###1.1. intel_ros

*intel_ros* runs in Windows. It will work with **Perceptual Computing SDK**, to ...

- Get RGB image and Depth image.
- Do voice recognition, translate user's voice into command string.
- Do voice synthesis, translate robot's response into voice.
- Do gesture recognition, translate user's gesture into command string.
- Do face detection. (not finish currently)
- Do face recognition. (not finish currently)

###1.2. intel_ros_vm

*intel_ros_vm* runs in Ubuntu (installed in virtual machine). It will ...

- Recive and send data from *intel_ros*.
- Run the our app's core algorithms to finish the tasks defined in proposals.
- Control the robot.

##2. Pre-Requisites

Two methods to run our application, **Simulated Robot** and **Real Robot**. That means you no need to buy a real robot, but the simulated robot can not reflect the effect of our application. I recommend you use the real robot to test our application.

###2.1. Simulated Robot

- Intel Interactive Gesture Camera and SDK
- One PC with Windows 7 and .net framwork 4
- A virtual mechine (recommend *VMWare Workstation 9*) installed in Windows 7
- Ubuntu 12.04 (or 12.10) installed in VMWare

###2.2. Real Robot

- Intel Interactive Gesture Camera and SDK
- One notebook (put it on the robot) with Windows 7 and .net framwork 4
- A virtual mechine (recommend *VMWare Workstation 9*) installed in Windows 7
- Ubuntu 12.04 (or 12.10) installed in VMWare
- A TurtleBot 1 mobile robot platform [TurtleBot](http://turtlebot.com/distributors.html) (easy to buy)

##3. Instructions

###3.1. Install win_ros in your windows system

*win_ros* is the ROS environment working in Windows system.

You can follow all the steps from [win_rosMsvc SDK - Fuerte](http://www.ros.org/wiki/win_ros/Msvc%20SDK%20-%20Fuerte) (http://www.ros.org/wiki/win_ros/Msvc%20SDK%20-%20Fuerte) to set up the win_ros environment.

###3.2. Install and config ROS Groovy in your Ubuntu system

Open your virtual mechine and login your Ubuntu system.

You can follow all the steps from [Ubuntu install of ROS Groovy](http://ros.org/wiki/groovy/Installation/Ubuntu) (http://ros.org/wiki/groovy/Installation/Ubuntu) to set up the ros groovy environment.

###3.3. Config the networking between Windows and Ubuntu

In this step, our goal is to make sure Windows and Ubuntu can see (ping) each other.
The virtual machine I used is VMWare.

####3.3.1. Ping each other

1. In Windows, *cmd->ipconfig*, to view your IPv4 address. 
2. In Ubuntu, *system setting->Network*, select the right network adapther, and view the IP address.
3. In Windows, *cmd->ping xxx.xxx.xxx.xxx(Ubuntu's IP)*. If failed, try my solution below.
4. In Ubuntu, open a terminal, *ping xxx.xxx.xxx.xxx(Windows's IP)*. If fialed, try my solution below.

In step 1 and 2, do not select the wrong network adapter's IP address, many people make mistake here.

####3.3.2. Try "Bridged" connection

1. In your VMWare, *VM->Setting->Network Adapter*, select "Bridged" as your network connection method.

Try to ping each other, if failed, try another solution below.

####3.3.3. Try "NAT" + "Host-only" two adapters

1. In your VMWare, *VM->Setting->Network Adapter*, select "NAT" as your network connection method.
2. *VM->Setting*, click "Add" to add a new hardware. currently, we add a "Network Adapter" named "Network Adapter 2", change the "Network connection" to "Host-only"
3. In Ubuntu, *system setting->Network*, you'll view two network adapters, select the host-only network adapter and view the IP. (Which one is host-only network adapter? In VMWare, *Edit->Virtual Network Editor* will show you the host-only adapter's subnet address. Refer to this subnet address to select the right IP in Ubuntu)

Try to ping each other, if failed, check step by step. I have no more solutions.

###3.4. Put our *intel_ros* package into win_ros folder

1. If you did not chage the path of win_ros, *"C:\opt\ros\fuerte\x86\share"* should exist. Put our *intel_ros* package in it. (It should look like *"C:\opt\ros\fuerte\x86\share\intel_ros"*)
2. Access *"C:\opt\ros\fuerte\x86"*, click "env.bat" to run the win_ros environment loaded console. Input "roscore" to start the ros master.
3. Open another console by "env.bat". Input "roslaunch intel_ros intel_ros.launch" to start our application in Windows.

If success, no error message display, and our application will ask you to select the voice input device.

If you want to compile our code, you must select "Release" config to compile it. (I developped it in Visual Studio 2012 and v100)

###3.5. Config ROS developing environment for Ubuntu

####3.5.1. Create ROS Workspaces

You may refer to [4. Create a ROS Workspace](http://www.ros.org/wiki/ROS/Tutorials/InstallingandConfiguringROSEnvironment) (http://www.ros.org/wiki/ROS/Tutorials/InstallingandConfiguringROSEnvironment) to create catkin workspace and rosbuild workspace. (two workspaces are needed)

####3.5.2. Overlaying

You may refer to [Overlaying with catkin workspaces](http://www.ros.org/wiki/catkin/Tutorials/workspace_overlaying) (http://www.ros.org/wiki/catkin/Tutorials/workspace_overlaying) to overly the rosbuild workspace to catkin workspace.

####3.5.3. Config ROS networking

In Ubuntu, open a terminal, `gedit ~/.bashrc` to edit .bashrc file, add `export ROS_MASTER_URI=http://YOUR_WINDOWS_IP:11311/` and `export ROS_IP=YOUR_UBUNTU_IP`. (Note: replace YOUR_WINDOWS_IP and 
YOUR_UBUNTU_IP by the two IPs I mentioned above in 3.3.1.)

###3.6. Compile our intel_ros_vm packages

Put our intel_ros_vm packages into catkin workspace ("~/catkin_ws/src/" you created it in 3.5.1.), and compile it with:

> cd ~/catkin_ws/  
> catkin_make

###3.7. Install the prerequisites packages for intel_ros_vm 

Standard ros packages

> sudo apt-get install ros-groovy-turtlebot* ros-groovy-control \  
> ros-groovy-openni-camera ros-groovy-openni-launch \  
> ros-groovy-openni-tracker ros-groovy-laser-drivers \  
> ros-groovy-audio-common ros-groovy-joystick-drivers \  
> ros-groovy-orocos-kinematics-dynamics \  
> ros-groovy-dynamixel-motor gstreamer0.10-pocketsphinx \    
> python-setuptools ros-groovy-opencv2 ros-groovy-vision-opencv \  
> ros-groovy-depthimage-to-laserscan ros-groovy-arbotix \  
> git subversion mercurial

Rbx robot package

> cd ~/fuerte_workspace/sandbox  
> git clone https://github.com/pirobot/rbx1.git  
> cd rbx1  
> rosmake  

###3.8. Run our applications in simulated robot

In Windows, go to "C:\opt\ros\fuerte\x86" folder, click "env.bat" to start a winRosed console, input "roscore" to start the rosmaster.

Wait the rosmaster stated (It will display "started core service [/rosout]"), then...

In Windows, open another "env.bat" console, input "roslaunch intel_ros intel_ros.launch" to start our apps.
Our apps will ask you to select a voice input device, when we use real robot to test our code, we need use blutooth to input our voice, for reduce the noise interference from the the robot.

In Ubuntu, open a terminal, and input ```roslaunch rbx1_bringup fake_turtlebot.launch & rosrun rviz rviz -d `rospack find rbx1_nav`/sim.rviz``` to start the simulated robot.

In Ubuntu, open another terminal, and input "roslaunch intel_ros_vm intel_ros_vm.launch" to start our apps.

Then, you'll view a simulated robot, and you can use voice and gesture to control the robot. The voice command list can be viewed in "intel_ros/common/commands.csv"

###3.9. Run our applications in real robot

The steps are quit similar with the simulated robot steps.

But, you need not input ```roslaunch rbx1_bringup fake_turtlebot.launch & rosrun rviz rviz -d `rospack find rbx1_nav`/sim.rviz``` to start a simulated robot. Instead, you should:

Connect with the real robot with usb-ttl cable, and then, in Ubuntu, input "roslaunch rbx1_bringup turtlebot_minimal_create.launch" to drive the real robot.

Then, enjoy the real robot with intel depth camera.