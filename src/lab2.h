#ifndef LAB2_H
#define LAB2_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct {
    Mat B;
    Mat G;
    Mat R;
} image_channels_bgr;

typedef struct {
    Mat H;
    Mat S;
    Mat V;
} image_channels_hsv;

image_channels_bgr break_channels(Mat source);

void display_channels(image_channels_bgr bgr_channels);

Mat bgr_2_grayscale(Mat source);

Mat grayscale_2_binary(Mat source, int threshold);

image_channels_hsv bgr_2_hsv(image_channels_bgr bgr_channels);

void display_hsv_channels(image_channels_hsv hsv_channels);

bool IsInside(Mat img, int i, int j);

#endif
