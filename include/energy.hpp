#pragma once

#include <opencv2/opencv.hpp>

double calculateEnergy(
    const cv::Mat &image,
    int x,
    int y);