# Tracker for Shotput Footage

## Requirements:
* OpenCV 4.2.0  
  Installation steps:
    1. Go to https://opencv.org/releases/
	2. Download Windows release
    3. Extract it to a location of your choice
	4. Set the [OpenCV directory]/build as the environment variable "OPENCV_PATH"
* WxWidgets  
  Installation steps:
    1. Go to https://www.wxwidgets.org/downloads/
	2. Download the Windows installer
	3. Run the installer
	4. Go to the [install directory]/build/msw and open the .sln file corresponding to your version of Visual Studio (make sure you build in Release x64)
	5. Build everything in the solution
	6. Set the install directory as the environment variable "WXWIDGETS_PATH"

## Solution:
 *  'opencv_world420.dll not found'
 	1. Go to your OS search engine.
	2. Search for opencv_world420.dll.
	3. Copy the file to the release/debug folder under x64 folder inside the shotput-tracker folder.
