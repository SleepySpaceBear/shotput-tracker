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

Mat src, src_gray;
Mat dst, detected_edges;

// moo
// sharp
const int presetParamsEdgeDet[] = { 1, 81, 193 };
int blur_strength = presetParamsEdgeDet[0];
int lowThreshold = presetParamsEdgeDet[1]; // ok to use: 31
int myratio = presetParamsEdgeDet[2];

const int max_lowThreshold = 200; // ok to use: 100
const int kernel_size = 3;
const char* window_name = "Edge Map";


// sharp
static void CannyThreshold(int, void*)
{
	if (blur_strength == 0)
		blur_strength = 1;
	blur(src_gray, detected_edges, Size(blur_strength, blur_strength));
	Canny(detected_edges, detected_edges, lowThreshold, myratio, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
}

// Canny() details:
/*
@param image 8 - bit input image.
@param edges output edge map; single channels 8 - bit image, which has the same size as image .
@param threshold1 first threshold for the hysteresis procedure.
@param threshold2 second threshold for the hysteresis procedure.
@param apertureSize aperture size for the Sobel operator.
@param L2gradient a flag, indicating whether a more accurate \f$L_2\f$ norm
\f$ = \sqrt{ (dI / dx) ^ 2 + (dI / dy) ^ 2 }\f$ should be used to calculate the image gradient magnitude(
	L2gradient = true), or whether the default \f$L_1\f$ norm \f$ = | dI / dx | +| dI / dy | \f$ is enough(
		L2gradient = false).
	
	
	CV_EXPORTS_W void Canny(InputArray image, OutputArray edges,
		double threshold1, double threshold2,
		int apertureSize = 3, bool L2gradient = false);
		*/

void Analyzer::foo(int x)
{
	// cmoo ==	circle moo
	// rmoo ==	rectangle moo
	// amoo ==	all moo

	// set to 1 to use circle matching, else template matching will be used
	int use_circle_matching = 0;
	// amoo
	// location of the videos
	const char* video_loc = "C:\\users\\SammyDesktop\\videos\\vid_0-0.mp4";



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
	int frames_to_play = 50; // default value is 15
	int end_frame = start_frame + frames_to_play; 

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


		// makes a copy
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
			
			// cmoo
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


			// PRE-PROCESSING: EDGE DETECTION
			// sharp
			Mat edge_frame;
			frame.copyTo(edge_frame);


			src = edge_frame;
			dst.create(src.size(), src.type());
			cvtColor(src, src_gray, COLOR_BGR2GRAY);
			namedWindow(window_name, WINDOW_AUTOSIZE);
			createTrackbar("Blur Strength:", window_name, &blur_strength, 20, CannyThreshold);
			createTrackbar("Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
			createTrackbar("My Ratio:", window_name, &myratio, 1000, CannyThreshold);


			CannyThreshold(0, 0);
			//waitKey(0);

			dst.copyTo(frame_copy);




			normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
			for (int i = 5; i < 5; i++)
			{
				if (1 == 1)
				//if (i == 2 || i == 3)
				{




					// this is all done here so we can hotload new templates,
					// aka we can make live changes here EVEN WHILE the program is running
					const char* t0 = "C:\\users\\SammyDesktop\\videos\\edgeball0.png";
					const char* t1 = "C:\\users\\SammyDesktop\\videos\\edgeball1.png";
					const char* t2 = "C:\\users\\SammyDesktop\\videos\\edgeball2.png";
					const char* t3 = "C:\\users\\SammyDesktop\\videos\\edgeball3.png";
					const char* t4 = "C:\\users\\SammyDesktop\\videos\\edgeball4.png";
					const char* t5 = "C:\\users\\SammyDesktop\\videos\\ball5.png";
					const char* t6 = "C:\\users\\SammyDesktop\\videos\\ball6.png";
					const char* t7 = "C:\\users\\SammyDesktop\\videos\\ball7.png";
					const char* t8 = "C:\\users\\SammyDesktop\\videos\\ball8.png";
					/*
					const char* t0 = "C:\\users\\SammyDesktop\\videos\\ball0.png";
					const char* t1 = "C:\\users\\SammyDesktop\\videos\\ball1.png";
					const char* t2 = "C:\\users\\SammyDesktop\\videos\\edgeball0.png";
					//const char* t2 = "C:\\users\\SammyDesktop\\videos\\ball2.png";
					const char* t3 = "C:\\users\\SammyDesktop\\videos\\edgeball1.png";
					//const char* t3 = "C:\\users\\SammyDesktop\\videos\\ball3.png";
					const char* t4 = "C:\\users\\SammyDesktop\\videos\\ball4.png";
					const char* t5 = "C:\\users\\SammyDesktop\\videos\\ball5.png";
					const char* t6 = "C:\\users\\SammyDesktop\\videos\\ball6.png";
					const char* t7 = "C:\\users\\SammyDesktop\\videos\\ball7.png";
					const char* t8 = "C:\\users\\SammyDesktop\\videos\\ball8.png";
					*/

					// this is a picture of the ball
					// needs more images fed in and used or else it has very, very poor detection here
					const char* templates[9];
					int temp_count = 0;
					templates[temp_count++] = t0;
					templates[temp_count++] = t1;
					templates[temp_count++] = t2;
					templates[temp_count++] = t3;
					templates[temp_count++] = t4;
					templates[temp_count++] = t5;
					templates[temp_count++] = t6;
					templates[temp_count++] = t7;
					templates[temp_count++] = t8;


					Mat template_image = imread(templates[i], 1);

					// rmoo
					
					//	rankings on the right
					//		0 TM_SQDIFF			8/10
					//		1 TM_SQDIFF_NORMED	7/10
					//		2 TM_CCORR			0/5
					//		3 TM_CCORR_NORMED	9/10
					//		4 TM_COEFF			0/5
					//		5 TM_COEFF_NORMED	6/10
					
					int match_method = 3;
					//sharp
					matchTemplate(frame_copy, template_image, result, match_method);
					//standard
					//matchTemplate(frame, template_image, result, match_method);


					/// Localizing the best match with minMaxLoc
					double minVal; double maxVal; Point minLoc; Point maxLoc;
					Point matchLoc;

					minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

					if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
						matchLoc = minLoc;
					else
						matchLoc = maxLoc;

					int mult = 50;
					int c0 = 0;
					int c1 = 0;
					int c2 = 255;

					// draws a tight-fitting square around our match
					rectangle(frame_copy, matchLoc, Point(matchLoc.x + template_image.cols, matchLoc.y + template_image.rows), Scalar(c0, c1, c2), 1, 8, 0);

					// Writes a number above our match
					std::string myStr = std::to_string(i);

					int x_offset = 10 * i + 10, 
						y_offset = 10 * i + 10;

					rectangle(frame_copy, 
						Point(matchLoc.x - 0 - x_offset, matchLoc.y - 45 - y_offset),
						Point(matchLoc.x + 40 - x_offset, matchLoc.y + 5 - y_offset),
						Scalar(255, 255, 255),
						-1, 8, 0);

					cv::putText(frame_copy, myStr,
						Point(matchLoc.x - x_offset, matchLoc.y - y_offset),
						FONT_HERSHEY_SIMPLEX,
						2, 
						cv::Scalar(c0, c1, c2), 1);
				}
				// sharp
				imshow(image_window, frame_copy);
			}

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
	//waitKey(0);

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
