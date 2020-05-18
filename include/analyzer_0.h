#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <atomic>
#include <thread>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include "..\include\analyzer_0.h"

#define DEBUG_VALUE_COUNT 10


class Analyzer {

public:
    double values[DEBUG_VALUE_COUNT];
    int done_debugging();
    int analyze();
    int increment_count();
    void foo(int x);
    Analyzer()
    {
        for (int i = 0; i < DEBUG_VALUE_COUNT; i++)
        {
            values[i] = 0;
        }
        img0 = cv::Mat::zeros(300, 600, CV_8UC3);
        img1 = cv::Mat::zeros(300, 600, CV_8UC3);
    }
private:
    std::thread t1;
    // base background
    cv::Mat img0;
    // background to write on
    cv::Mat img1;


    // worker thread
    std::thread m_debugprintWorker;
    // signal for m_threadWorker to remain alive
    std::atomic<bool> m_debug_alive;

    // function for m_threadWorker
    void debug_work();
    void refresh_screen();
};


#endif

#pragma once
