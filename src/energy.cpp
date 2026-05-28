#include "energy.hpp"

#include <cmath>
#include <algorithm>

using namespace cv;
using namespace std;

// Function to calculate energy of a pixel based on gradient
double calculateEnergy(const Mat &image, int x, int y)
{
    Vec3b leftPixel = image.at<Vec3b>(y, max(x - 1, 0));
    Vec3b rightPixel = image.at<Vec3b>(y, min(x + 1, image.cols - 1));
    Vec3b topPixel = image.at<Vec3b>(max(y - 1, 0), x);
    Vec3b bottomPixel = image.at<Vec3b>(min(y + 1, image.rows - 1), x);

    double gradientX = abs(rightPixel[0] - leftPixel[0]) + abs(rightPixel[1] - leftPixel[1]) + abs(rightPixel[2] - leftPixel[2]);
    double gradientY = abs(bottomPixel[0] - topPixel[0]) + abs(bottomPixel[1] - topPixel[1]) + abs(bottomPixel[2] - topPixel[2]);

    return gradientX + gradientY;
}
