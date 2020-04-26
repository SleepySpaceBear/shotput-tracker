#include "app.hpp"

#include "ui.hpp"

#include <opencv2/opencv.hpp
#include <iostream>
#include <string>

VideoWriter loadedVideo;

bool App::OnInit() {
	UI *frame = new UI("Shotput Tracker", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);
	return true;
}

int App::OnExit() {
	return 0;
}

bool App::LoadVideo(std::string pathVideo) {
	//open the video file for reading
    VideoCapture cap(pathVideo);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return false;
    }

    int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
    int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

    Size frame_size(frame_width, frame_height);
    //get the frames rate of the video
    double fps = cap.get(CAP_PROP_FPS);
    cout << "Frames per seconds : " << fps << endl;
    //int frames_per_second = 10;

    //Create and initialize the VideoWriter object 
    VideoWriter lVideo(pathVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                                                           fps, frame_size, true); 
    //If the VideoWriter object is not initialized successfully, exit the program                                                    
    if (lVideo.isOpened() == false) 
    {
        cout << "Cannot save the video to a file" << endl;
        cin.get(); //wait for any key press
        return false;
    }
    loadedVideo = lVideo;
    String window_name = "Shotput-tracker";

    namedWindow(window_name, WINDOW_NORMAL); //create a window

    return true;
}

wxIMPLEMENT_APP(App);
