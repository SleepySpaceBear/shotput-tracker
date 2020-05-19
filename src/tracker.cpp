#include "tracker.hpp"

#include <opencv2/imgproc.hpp>
#include "constants.hpp"

const static cv::Scalar g_white{ 255, 255, 255 };
const static cv::Scalar g_grey{ 128, 128, 128 };
const static cv::Scalar g_black{ 0, 0, 0 };
const static float g_threshold = 0.2;

void Tracker::processFrame(cv::Mat& frame) {
	cv::resize(frame, frame, { frame.cols / SPT_VID_SCALE_FACTOR , frame.rows / SPT_VID_SCALE_FACTOR });

	cv::Point loc = findShotput(frame);
	
	if (loc.x != -1 && loc.y != -1) {
		drawCircle(loc, frame);
	}
}



cv::Point Tracker::findShotput(cv::Mat& frame) {
	// get the greyscale frame
	//cv::Mat greyscale;
	//cv::cvtColor(frame, greyscale, cv::COLOR_BGR2GRAY);
	cv::imshow("test", frame);

	cv::Point loc{ -1, -1 };
	//return loc;

	cv::Mat result;

	all_matched_locations locs;

	const char* t0 = "templates\\0.png";
	const char* t1 = "templates\\1.png";
	const char* t2 = "templates\\2.png";
	const char* t3 = "templates\\3.png";
	const char* t4 = "templates\\4.png";
	const char* t5 = "templates\\5.png";
	const char* t6 = "templates\\6.png";
	const char* t7 = "templates\\7.png";
	const char* t8 = "templates\\8.png";
	const char* t9 = "templates\\9.png";
	const char* t10 = "templates\\10.png";
	const char* t11 = "templates\\11.png";
	const char* t12 = "templates\\12.png";
	const char* t13 = "templates\\13.png";
	const char* t14 = "templates\\14.png";
	const char* t15 = "templates\\15.png";
	const char* t16 = "templates\\16.png";
	const char* t17 = "templates\\17.png";
	const char* t18 = "templates\\18.png";
	const char* t19 = "templates\\19.png";
	const char* t20 = "templates\\20.png";
	const char* t21 = "templates\\21.png";
	const char* t22 = "templates\\22.png";
	const char* t23 = "templates\\23.png";


	const char* templates[SAMPLE_COUNTS];
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
	templates[temp_count++] = t9;
	templates[temp_count++] = t10;
	templates[temp_count++] = t11;
	templates[temp_count++] = t12;
	templates[temp_count++] = t13;
	templates[temp_count++] = t14;
	templates[temp_count++] = t15;
	templates[temp_count++] = t16;
	templates[temp_count++] = t17;
	templates[temp_count++] = t18;
	templates[temp_count++] = t19;
	templates[temp_count++] = t20;
	templates[temp_count++] = t21;
	templates[temp_count++] = t22;
	templates[temp_count++] = t23;

	for (int i = 0; i < SAMPLE_COUNTS; i++)
	{
		if (1 == 1)
			//if (i == 2 || i == 3)
		{
			//if (i == 19)
				//break;

			// loads the relevant temmplate_image
			cv::Mat template_image = cv::imread(templates[i], 1);

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
			matchTemplate(frame, template_image, result, match_method);
			//normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

			//standard
			//matchTemplate(frame, template_image, result, match_method);


			/// Localizing the best match with minMaxLoc
			double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
			cv::Point matchLoc;

			minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

			if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED)
				matchLoc = minLoc;
			else
				matchLoc = maxLoc;

			int mult = 50;
			int c0 = 0;
			int c1 = 0;
			int c2 = 255;

			// detect if we had a new center
			int new_x = matchLoc.x,
				new_y = matchLoc.y;

			int last_x = locs.location[i].prev_x_center,
				last_y = locs.location[i].prev_y_center;

			if (new_x == last_x && new_y == last_y)
				locs.location[i].has_changed = 0;
			else
				locs.location[i].has_changed = 1;

			// update center
			locs.location[i].prev_x_center = locs.location[i].prev_x_center;
			locs.location[i].prev_y_center = locs.location[i].prev_y_center;
			locs.location[i].x_center = matchLoc.x;
			locs.location[i].y_center = matchLoc.y;

			// get size
			locs.location[i].detected_size = template_image.cols * template_image.rows;

			// get average color in the detected region
			const int approximation_factor = 1; // anything above 0 adds an extra skip
			long avg_b = 0, avg_g = 0, avg_r = 0;
			for (int i = 0; i < template_image.cols; i++)
			{
				for (int j = 0; j < template_image.rows; j++)
				{
					int x_loc = matchLoc.x - template_image.cols + i,
						y_loc = matchLoc.y - template_image.rows + j;
					cv::Vec3b color = frame.at<cv::Vec3b>(cv::Point(x_loc, y_loc));
					avg_b += color[0];
					avg_g += color[1];
					avg_r += color[2];
					j += approximation_factor;
				}
				i += approximation_factor;
			}
			avg_b /= template_image.cols * template_image.rows;
			avg_g /= template_image.cols * template_image.rows;
			avg_r /= template_image.cols * template_image.rows;
			locs.location[i].average_center_color[0] = avg_b;
			locs.location[i].average_center_color[1] = avg_g;
			locs.location[i].average_center_color[2] = avg_r;



			// draws a tight-fitting square around our match
			//rectangle(frame, matchLoc, Point(matchLoc.x + template_image.cols, matchLoc.y + template_image.rows), Scalar(c0, c1, c2), 1, 8, 0);

			// Writes our number above our match
			std::string myStr = std::to_string(i);

			int x_offset = 10,// 10 * i + 10,
				y_offset = 25;// 10 * i + 10;



			int draw_box_width = 40;
			if (i > 9)
				draw_box_width *= 2;

			rectangle(frame,
				cv::Point(matchLoc.x - 0 - x_offset, matchLoc.y - 45 - y_offset),
				cv::Point(matchLoc.x + draw_box_width - x_offset, matchLoc.y + 5 - y_offset),
				cv::Scalar(255, 255, 255),
				-1, 8, 0);


			cv::putText(frame, myStr,
				cv::Point(matchLoc.x - x_offset, matchLoc.y - y_offset),
				cv::HersheyFonts::FONT_HERSHEY_SIMPLEX,
				2,
				cv::Scalar(c0, c1, c2), 1);


		}
		imshow("'frame' output", frame);
		// debug windows created on a per template image basis
		//imshow(std::to_string(i), frame);
	}

	// WE DONT NEED ANY LOCKS HERE IF EACH THREAD ONLY WRITES TO ITS OWN ARRAY LOCATION (i)


	for (int i = 0; i < SAMPLE_COUNTS; i++)
	{

	}

	// sees who has the most agree-ers
	const int agree_boundary = 10; // in px, compares centers of detections

	for (int i = 0; i < SAMPLE_COUNTS; i++)
	{
		int ourX = locs.location[i].x_center,
			ourY = locs.location[i].y_center;

		for (int j = 0; j < SAMPLE_COUNTS; j++)
		{
			// doesn't compare itself
			if (j != i)
			{
				int compX = locs.location[j].x_center,
					compY = locs.location[j].y_center;

				if (abs(compX - ourX) < agree_boundary && abs(compY - ourY) < agree_boundary)
				{
					locs.location[j].agree_score += 1;
				}

			}
		}
	}


	return loc;
}

void Tracker::drawCircle(const cv::Point& loc, cv::Mat& frame) {
	cv::circle(frame, { loc.x + s_shotputSize / 2, loc.y + s_shotputSize / 2 }, s_shotputSize + 2, g_white, 2);
}
