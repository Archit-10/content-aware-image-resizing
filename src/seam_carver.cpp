#include "seam_carver.hpp"
#include "energy.hpp"

#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

// Function to find the seam with the lowest energy
vector<int> findLowestEnergySeam(
    const Mat &image,
    int height,
    int width)
{
    vector<vector<double>> energy(
        height,
        vector<double>(width));

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            energy[y][x] = calculateEnergy(image, x, y);
        }
    }

    vector<vector<double>> dp(
        height,
        vector<double>(width));

    for (int x = 0; x < width; ++x)
    {
        dp[0][x] = energy[0][x];
    }

    for (int y = 1; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            dp[y][x] = energy[y][x] +
                       min({dp[y - 1][max(x - 1, 0)],
                            dp[y - 1][x],
                            dp[y - 1][min(x + 1, width - 1)]});
        }
    }

    int minIndex = 0;

    for (int x = 1; x < width; ++x)
    {
        if (dp[height - 1][x] < dp[height - 1][minIndex])
        {
            minIndex = x;
        }
    }

    vector<int> seam(height);

    seam[height - 1] = minIndex;

    for (int y = height - 2; y >= 0; --y)
    {
        int x = seam[y + 1];
        int bestX = x;
        double bestVal = dp[y][x];

        if (x > 0 && dp[y][x - 1] < bestVal)
        {
            bestVal = dp[y][x - 1];
            bestX = x - 1;
        }

        if (x < width - 1 && dp[y][x + 1] < bestVal)
        {
            bestVal = dp[y][x + 1];
            bestX = x + 1;
        }

        seam[y] = bestX;
    }

    return seam;
}

// Function to remove a single vertical seam from the image
void removeSeam(
    Mat &image,
    const vector<int> &seam)
{
    int height = image.rows;

    for (int y = 0; y < height; ++y)
    {
        int x = seam[y];

        for (int i = x; i < image.cols - 1; ++i)
        {
            image.at<Vec3b>(y, i) =
                image.at<Vec3b>(y, i + 1);
        }
    }

    image = image(
        Rect(0, 0, image.cols - 1, image.rows));
}

void removeVerticalSeams(
    Mat &image,
    int targetWidth)
{
    while (image.cols > targetWidth)
    {
        vector<int> seam = findLowestEnergySeam(
            image,
            image.rows,
            image.cols);

        removeSeam(image, seam);
    }
}

void removeHorizontalSeams(
    Mat &image,
    int targetHeight)
{
    transpose(image, image);

    while (image.cols > targetHeight)
    {
        vector<int> seam = findLowestEnergySeam(
            image,
            image.rows,
            image.cols);

        removeSeam(image, seam);
    }

    transpose(image, image);
}