#include <iostream>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Function to calculate energy of a pixel based on gradient
double calculateEnergy(const Mat& image, int x, int y) {
    // Calculate gradient in both X and Y directions
    Vec3b leftPixel = image.at<Vec3b>(y, max(x - 1, 0));
    Vec3b rightPixel = image.at<Vec3b>(y, min(x + 1, image.cols - 1));
    Vec3b topPixel = image.at<Vec3b>(max(y - 1, 0), x);
    Vec3b bottomPixel = image.at<Vec3b>(min(y + 1, image.rows - 1), x);

    double gradientX = abs(rightPixel[0] - leftPixel[0]) + abs(rightPixel[1] - leftPixel[1]) + abs(rightPixel[2] - leftPixel[2]);
    double gradientY = abs(bottomPixel[0] - topPixel[0]) + abs(bottomPixel[1] - topPixel[1]) + abs(bottomPixel[2] - topPixel[2]);

    return gradientX + gradientY;
}

// Function to find the seam with the lowest energy
int* findLowestEnergySeam(const Mat& image, int height, int width) {
    double** energy = new double*[height];
    for (int y = 0; y < height; ++y) {
        energy[y] = new double[width];
        for (int x = 0; x < width; ++x) {
            energy[y][x] = calculateEnergy(image, x, y);
        }
    }


    double** dp = new double*[height];
    for (int y = 0; y < height; ++y) {
        dp[y] = new double[width];
    }

    for (int x = 0; x < width; ++x) {
        dp[0][x] = energy[0][x];
    }

    for (int y = 1; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            dp[y][x] = energy[y][x] + min({dp[y - 1][max(x - 1, 0)], dp[y - 1][x], dp[y - 1][min(x + 1, width - 1)]});
        }
    }

    int minIndex = 0;
    for (int x = 1; x < width; ++x) {
        if (dp[height - 1][x] < dp[height - 1][minIndex]) {
            minIndex = x;
        }
    }

    int* seam = new int[height];
    seam[height - 1] = minIndex;
    for (int y = height - 2; y >= 0; --y) {
        int x = seam[y + 1];
        if (x > 0 && dp[y][x - 1] < dp[y][x]) {
            seam[y] = x - 1;
        } else if (x < width - 1 && dp[y][x + 1] < dp[y][x]) {
            seam[y] = x + 1;
        } else {
            seam[y] = x;
        }
    }

    // Cleaning up dynamic arrays
    for (int y = 0; y < height; ++y) {
        delete[] energy[y];
        delete[] dp[y];
    }
    delete[] energy;
    delete[] dp;

    return seam;
}

// Function to remove a seam from the image
void removeSeam(Mat& image, int* seam) {
    int height = image.rows;
    for (int y = 0; y < height; ++y) {
        int x = seam[y];
        for (int i = x; i < image.cols - 1; ++i) {
            image.at<Vec3b>(y, i) = image.at<Vec3b>(y, i + 1);
        }
    }
    image = image(Rect(0, 0, image.cols - 1, image.rows));
    delete[] seam;
}

int main() {
    // Reading the input image
    Mat inputImage = imread("/home/archp/Downloads/sample_input/sample1.jpeg");
    if (inputImage.empty()) {
        cerr << "Could not open or find the image!" << endl;
        return -1;
    }

    int newWidth, newHeight;
    cout << "Enter the new width and height: ";
    cin >> newWidth >> newHeight;

    Mat resizedImage = inputImage.clone();

    while (resizedImage.cols > newWidth && resizedImage.rows > newHeight) {
        int* seam = findLowestEnergySeam(resizedImage, resizedImage.rows, resizedImage.cols);
        removeSeam(resizedImage, seam);
    }

    // Displaying the resized image
    imshow("Resized Image", resizedImage);
    waitKey(0);

    return 0;
}
