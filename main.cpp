#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab4.h"
using namespace std;
using namespace cv;

int main() {
    Mat image = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/geometrical_features.bmp",
                       IMREAD_COLOR);

    namedWindow("My Window", 1);

    //set the callback function for any mouse event
    setMouseCallback("My Window", geom_features, &image);

    //show the image
    imshow("My Window", image);

    waitKey(0);
    return 0;
}