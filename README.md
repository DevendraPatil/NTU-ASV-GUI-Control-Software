# NTU-ASV-GUI-Control-Software
This project hosts the Source Code for our [Paper](http://www.robotics.sg/xieming/robio17-103.pdf).<br />
<br />
NTU ASV GUI CONTROL SOFTWARE:VERSION 1.0.5<br />
SUBVERSION:WAM-V 16' NTU SINGABOAT<br />
<br />
CORE FRAMEWORK BASED ON ROS INDIGO ON UBUNTU TRUSTY (14.04)<br />
GUI DEVELOPED ON Qt Creator 3.1.2 (opensource) Based on Qt 5.3.1 (GCC 4.6.1, 64 bit) AND Qt Creator 4.1.0 Based on Qt 5.6.1 (GCC 4.8.4, 64bit)

## Reference
If you use this code please cite:
Sai Velamala, Devendra Patil and Ming Xie.
"Development of ROS-Based GUI for Control of an Autonomous Surface Vehicle" IEEE International Conference on Robotics and Biomemetics(IEEE-ROBIO) 2017.

## Running the Code

Steps to rebuild workspace:
1. Copy the entire folder 'pubimage1' to your catkin workspace src folder.<br />
2. Open each file in the 'src' and 'include' folders as text and replace the username in the directory.<br /> 
   ex: If> #include "/home/devendra/catkin_ws/src/pubimage1/include/pubimage1/main_window.hpp".<br />
   replace with >#include "/home/<your user>/catkin_ws/src/pubimage1/include/pubimage1/main_window.hpp".<br />
3. Build the workspace using the 'catkin_make' command.<br />
4. Source the workspace.<br />
5. Open Qt Creator and open the respective project using its 'CMakeLists.txt' file.<br />
6. Modify as per requirement.<br />

For further help refer to:<br />
http://wiki.ros.org/ROS/Tutorials<br />
http://doc.qt.io/<br />


