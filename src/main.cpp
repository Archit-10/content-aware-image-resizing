#include <iostream>
#include <opencv2/opencv.hpp>

#include "seam_carver.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat inputImage = imread("../assets/input/sample1.png");
    if (inputImage.empty())
    {
        cerr << "Could not open or find the image!" << endl;
        return -1;
    }

    int newWidth, newHeight;
    cout << "Enter the new width and height: ";
    cin >> newWidth >> newHeight;

    // Validate requested dimensions

    if (newWidth <= 0 || newWidth > inputImage.cols ||
        newHeight <= 0 || newHeight > inputImage.rows)
    {
        cerr << "Invalid dimensions!" << endl;
        return -1;
    }

    Mat resizedImage = inputImage.clone();

    removeVerticalSeams(
        resizedImage,
        newWidth);

    removeHorizontalSeams(
        resizedImage,
        newHeight);
    /*
    // Displaying the resized image
    imshow("Resized Image", resizedImage);
    waitKey(0);
    */
    imwrite("../assets/output/resized.png", resizedImage);

    cout << "Resized image saved successfully!" << endl;
    return 0;
}
