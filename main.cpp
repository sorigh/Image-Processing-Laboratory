#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab2.h"
using namespace std;
using namespace cv;

int main() {
    // Load an example image
    Mat source = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/flowers_24bits.bmp");
    if (source.empty()) {
        cerr << "Error: Could not load the image!" << endl;
        return -1;
    }

    // Test: break_channels
    image_channels_bgr bgr_channels = break_channels(source);
    display_channels(bgr_channels);

    // Test: BGR to Grayscale
    Mat grayscale = bgr_2_grayscale(source);
    imshow("Grayscale", grayscale);

    // Test: Grayscale to Binary
    int threshold = 128;
    Mat binary = grayscale_2_binary(grayscale, threshold);
    imshow("Binary", binary);

    // Test: BGR to HSV conversion
    image_channels_hsv hsv_channels = bgr_2_hsv(bgr_channels);
    display_hsv_channels(hsv_channels);

    // Test: isInside
    cout << "Is (50, 50) inside the image? " << (IsInside(source, 50, 50) ? "Yes" : "No") << endl;
    cout << "Is (-1, 50) inside the image? " << (IsInside(source, -1, 50) ? "Yes" : "No") << endl;

    waitKey(0);
    return 0;
}
