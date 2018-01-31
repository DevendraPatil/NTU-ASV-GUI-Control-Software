# NTU-ASV-GUI-Control-Software
This project hosts the Source Code for our [Paper](http://www.robotics.sg/xieming/robio17-103.pdf):
NTU ASV GUI CONTROL SOFTWARE:VERSION 1.0.5
SUBVERSION:WAM-V 16' NTU SINGABOAT

CORE FRAMEWORK BASED ON ROS INDIGO ON UBUNTU TRUSTY (14.04)
GUI DEVELOPED ON Qt Creator 3.1.2 (opensource) Based on Qt 5.3.1 (GCC 4.6.1, 64 bit) AND Qt Creator 4.1.0 Based on Qt 5.6.1 (GCC 4.8.4, 64bit)

## Reference
If you use this code please cite:
Sai Velamala, Devendra Patil and Ming Xie.
"Development of ROS-Based GUI for Control of an Autonomous Surface Vehicle" IEEE International Conference on Robotics and Biomemetics(IEEE-ROBIO) 2017.

## Running the Code

Steps to rebuild workspace:
1. Copy the entire folder 'pubimage1' to your catkin workspace src folder
2. Open each file in the 'src' and 'include' folders as text and replace the username in the directory 
   ex: If> #include "/home/devendra/catkin_ws/src/pubimage1/include/pubimage1/main_window.hpp"
   replace with >#include "/home/<your user>/catkin_ws/src/pubimage1/include/pubimage1/main_window.hpp"
3. Build the workspace using the 'catkin_make' command.
4. Source the workspace.
5. Open Qt Creator and open the respective project using its 'CMakeLists.txt' file.
6. Modify as per requirement.

For further help refer to:
http://wiki.ros.org/ROS/Tutorials
http://doc.qt.io/


