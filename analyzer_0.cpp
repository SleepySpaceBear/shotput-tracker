// lots of unused things in this code

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
//#include <analyzer_0.h>

#include<iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <stdio.h>
#include "..\include\analyzer_0.h"


static int count_0 = 0;
static Mat image_with_count = Mat::zeros(1000, 50, CV_8UC3);

void debug_work()
{
	count_0++;
}

void Analyzer::debug_work()
{
	count_0++;
	refresh_screen();
	for (double i = 0; i < 999999999999; i++)
		;

}

void Analyzer::refresh_screen()
{
	// clears img1 to be the background again
	img1 = img0;

	// converts the counter to a string
	std::string t0 = std::to_string(count_0);

	cv::putText(img1, t0, Point(5, 40 + (count_0 * 40)), FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 0, 255), 1);
	imshow("count_0 value", image_with_count);

}

void Analyzer::foo(int x)
{
	// moo
	// set to 1 to use circle matching, else template matching will be used
	int use_circle_matching = 1;
	// moo
	// location of the videos
	const char* video_loc = "C:\\users\\SammyDesktop\\videos\\vid_0-0.mp4";
	const char* template_loc = "C:\\users\\SammyDesktop\\videos\\ball_0.png";

	// this is a picture of the ball
	// needs more images fed in and used or else it has very, very poor detection here
	Mat template_image = imread(template_loc, 1);


	// tut code starts here
	// https://www.learnopencv.com/read-write-and-display-a-video-using-opencv-cpp-python/
	// https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/template_matching/template_matching.html

	// loads the video
	VideoCapture video_feed(video_loc);
	const char* image_window;
	const char* result_window;

	image_window = "image_window";
	result_window = "result_window";

	// moo
	// the frames you want to play
	int start_frame = 5;
	int end_frame = 10; 

	// skips ahead to the desired frames
	for (int i = 0; i < start_frame; i++)
	{
		Mat unused_mat_0000;
		video_feed >> unused_mat_0000;
	}

	while (1)
	{
		if (start_frame++ > end_frame)
		{
			start_frame = 0;
			//break;
			video_feed.release();
			video_feed.open(video_loc);
		}
		Mat result, frame;

		// loads the next video frame from video_feed into Mat frame
		video_feed >> frame;
		if (frame.empty())
			break;


		/// make copy
		Mat frame_copy;
		frame.copyTo(frame_copy);


		if (use_circle_matching)
		{
			// this is circle matching
			// https://docs.opencv.org/3.4/d4/d70/tutorial_hough_circle.html
			// https://www.pyimagesearch.com/2014/07/21/detecting-circles-images-using-opencv-hough-circles/
			Mat gray;
			double dp;

			int min_dist_between_circles, 
				canny_edge_detector_upper_threshold, center_detection_threshold, 
				min_circle_radius, max_circle_radius, 
				blur_strength;
			
			// moo
			// PARAMETERS for circle detection
			blur_strength = 5;
			min_dist_between_circles = 50; // minimum pixel distance between circles

			canny_edge_detector_upper_threshold = 200; // a key filter to play with
			center_detection_threshold = 10; // another key filter to play with
			
			dp = 1.0; // a crazy thing

			// size of circles to detect
			min_circle_radius = 10; 
			max_circle_radius = 20; 

			// end PARAMETERS

			// sanity checks for valid values
			if (blur_strength > 5)
				blur_strength = 5;

			if (blur_strength < 1)
				blur_strength = 1;

			if (dp <= 0)
				dp = 1;




			cvtColor(frame, gray, COLOR_BGR2GRAY);
			medianBlur(gray, gray, blur_strength);


			vector<Vec3f> circles;


			HoughCircles
			(
				gray,
				circles,
				HOUGH_GRADIENT,
				dp,
				min_dist_between_circles,
				canny_edge_detector_upper_threshold,
				center_detection_threshold,
				min_circle_radius,
				max_circle_radius
			);

			for (size_t i = 0; i < circles.size(); i++)
			{
				Vec3i c = circles[i];
				Point center = Point(c[0], c[1]);
				// circle center
				circle(frame, center, 1, Scalar(255, 255, 255), 3, LINE_AA);
				// circle outline
				int radius = c[2];
				circle(frame, center, radius, Scalar(0, 0, 255), 3, LINE_AA);
			}
			imshow("detected circles", frame);

		} // end circle matching

		else // if (use_circle_matching == 0)
		{
			// below is template matching

			// moo
			/*
			I don't know which of these is best to use in our case
				0 TM_SQDIFF
				1 TM_SQDIFF_NORMED
				2 TM_CCORR
				3 TM_CCORR_NORMED
				4 TM_COEFF
				5 TM_COEFF_NORMED
			*/
			int match_method = 0;
			matchTemplate(frame, template_image, result, TM_SQDIFF_NORMED);
			normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

			/// Localizing the best match with minMaxLoc
			double minVal; double maxVal; Point minLoc; Point maxLoc;
			Point matchLoc;

			minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

			if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
				matchLoc = minLoc;
			else
				matchLoc = maxLoc;


			/// Draws a rectangle around the results 
			rectangle(frame_copy, matchLoc, Point(matchLoc.x + template_image.cols, matchLoc.y + template_image.rows), Scalar::all(0), 2, 8, 0);
			imshow(image_window, frame_copy);

			//rectangle(result, matchLoc, Point(matchLoc.x + template_image.cols, matchLoc.y + template_image.rows), Scalar::all(0), 2, 8, 0);
			//imshow(result_window, result);






			// raw video output without any overlays
			//imshow("Raw Video", frame);

		} // end template matching
		
		// hold ESC to quit
		char c = (char)waitKey(1); // 1 ms delay
		if (c == 27)
			break;
	}

	// I believe this may unlock the video in the file system
	video_feed.release();
	// tut code ends here

	// waits for the user to hit any key to proceed from herer
	waitKey(0);

	// dangerously restarts this method and thus, the video
	//foo(x);

	// this should never happen
	return;

	// code that draws up another window for stats and debug
	//namedWindow(img_w, 1);
	cv::Mat sam = cv::Mat::zeros(500, 500, CV_8UC3);
	unsigned int y = x;
	while (1 == 1)
	{
		img1 = img0;
		img1 = cv::Mat::zeros(500, 500, CV_8UC3);
		sam = cv::Mat::zeros(500, 500, CV_8UC3);


		// converts the counter to a string
		std::string t0 = std::to_string(y);

		cv::putText(sam, t0, Point(5, 40), FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(255, 255, 255), 1);

		circle(sam, Point(250, 150), 100, Scalar(0, 255, 128), -100);
		imshow("A Display Window", sam);
		cv::waitKey(1);


		//y++;
		y = y++ % UINT_MAX;
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	
	return;
}

int Analyzer::done_debugging()
{
	t1.join();
	return 0;
}

int Analyzer::analyze()
{
	for (int i = 0; i < 10; i++)
	{
		values[i] = 0;
	}
	img0 = cv::Mat::zeros(300, 600, CV_8UC3);
	img1 = cv::Mat::zeros(300, 600, CV_8UC3);


	
	circle(img0, Point(250, 150), 100, Scalar(0, 255, 128), -100);
	circle(img0, Point(350, 150), 100, Scalar(255, 255, 255), -100);
	//imshow("Display Window", img0);

	//std::thread hello();
	//void* x = &foo;
	//std::thread hey(foo, 1);
	//t1 = std::thread(task1, "Hello");
	//t1.join();


	//m_debug_alive.store(true);
	//m_debugprintWorker = std::thread([this] { this->debug_work(); });;
	//m_debug_alive.store(false);


	return 0;
}

int Analyzer::increment_count()
{
	// clears img1 to be the background again
	img1 = img0;

	// converts the counter to a string
	std::string t0 = std::to_string(count_0);

	cv::putText(img1, t0, Point(5, 40 + (count_0 * 40)), FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 0, 255), 1);
	imshow("count_0 value", image_with_count);
	//Sleep(100);

	return count_0++; // 0 for error-free return
	
}
