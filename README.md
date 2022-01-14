*********README*********

---------------------
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Recommended modules
 * Installation
 * Execution
 * Configuration

--------------
INTRODUCTION
--------------
* This small project takes a video of a tennis ball rolling across a small court. The output
is a video which will both outline the tennis ball within the court and display the region of
the court in which the ball is located.

--------------
REQUIREMENTS
--------------

-WINDOWS
* You will need the following to build this project with cmake:
* [OpenCV] https://opencv.org/releases/
  Select the "Windows" button under OpenCV -4.5.5
  Go to folder where you installed OpenCV.
  Add /opencv/build/x64/vc15/bin to your path variables
  Add /opencv/build/x64/vc15/lib to your path variables
* [CMake] https://cmake.org/download/
  Select the installer that matches your version of Windows.
  BE SURE TO ADD CMAKE TO PATH VARIABLES during your install.

-LINUX
* You will need to build this project with CMake.
* The following is a tutorial for installing the required packaages to build this project
  on Linux: https://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html
* This is a summary of the above tutorial:
	Run these bash commands on terminal:
	!sudo apt-get install GCC
	!sudo apt-get install build-essential
	!sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
	!sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev

--------------
RECOMMENDED
--------------
* An AVI video player to display the output file.
  [VLC] https://www.videolan.org/vlc/
* VLC is available for both Windows and Linux

--------------
INSTALLATION
--------------
-ALL USERS MUST FIRST
Clone this repository to your local device. Either:
* Run the following on CLI
  !git clone https://github.com/007Winner/CPPBallFind
* Clone the https://github.com/007Winner/CPPBallFind repository from GitHub Desktop
* Download the project as a ZIP file on your web browser at https://github.com/007Winner/BallFind

-WINDOWS (Compile with CMake)
* cd to the src folder
* run the following commands on cmd:
  !cmake -S . -B build
  !cd build
  !cmake --build .
* Running the above commands will create a .exe of the project.

-LINUX (Compile with CMake)
* cd to the src folder
* run the following commands on terminal:
  !cmake -S . -B build
  !cd build
  !cmake --build .
* Running the above commands will create a target file for CPPBallFind.

--------------
EXECUTION
--------------
-WINDOWS
* cd to the folder that contains CPPBallFind.exe
	- This will be /src/build if you compiled the source code as per above
	  instructions.
* place a video of a rolling tennis ball in this folder. There is an example
  video already conveniently placed in the build folder.
* Run the following command on cmd:
  !CPPBallFind.exe <NameOfRollingBallVideo>
* Example:
  !CPPBallFind.exe RollingTennisBall.mov
* You will now have an output file in your folder titled "out.avi".

-LINUX
* cd to /src/build, the build folder that you created with CMake
* place a video of a rolling tennis ball in this folder. There is an example
  video already conveniently placed in the build folder.
* Run the following command on terminal:
  !./CPPBallFind <NameOfRollingBallVideo>
* Example:
  !./CPPBallFind RollingTennisBall.exe
* You will now have an output file in your folder titled "out.avi".

--------------
CONFIGURATION
--------------
The project has no modifiable settings. There is no configuration.
