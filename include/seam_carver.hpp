#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

std::vector<int> findLowestEnergySeam(
    const cv::Mat &image,
    int height,
    int width);

void removeSeam(
    cv::Mat &image,
    const std::vector<int> &seam);

void removeVerticalSeams(
    cv::Mat &image,
    int targetWidth);

void removeHorizontalSeams(
    cv::Mat &image,
    int targetHeight);