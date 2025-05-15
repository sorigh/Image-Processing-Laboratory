#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab10.h"
using namespace std;
using namespace cv;


int main() {
    Mat source_linear = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/balloons_Salt&Pepper.bmp",
                               IMREAD_GRAYSCALE);

    imshow("Original Image Linear", source_linear);

    // Apply median filtering
    Mat median_filtered = linear_filtering(source_linear, 5, "median");
    imshow("Median Filtered", median_filtered);
    // Apply minimum filtering
    Mat minimum_filtered = linear_filtering(source_linear, 5, "minimum");
    imshow("Minimum Filtered", minimum_filtered);

    // Apply maximum filtering
    Mat maximum_filtered = linear_filtering(source_linear, 5, "maximum");
    imshow("Maximum Filtered", maximum_filtered);

    // Apply Gaussian filtering
    Mat source_gaussian = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/portrait_Gauss2.bmp",
                                 IMREAD_GRAYSCALE);

    imshow("Original Image Gaussian", source_gaussian);

    double t = (double)getTickCount();
    Mat gaussian_filtered_2D = apply_gaussian_filtering_2D(source_gaussian, 5);
    t = ((double)getTickCount() - t) / getTickFrequency();
    printf("Time for 2D Gaussian= %.3f [ms]\n", t * 1000);
    imshow("Gaussian Filtered 2D", gaussian_filtered_2D);

    t = (double)getTickCount();
    Mat gaussian_filtered_1D = apply_gaussian_filtering_1D(source_gaussian, 5);
    t = ((double)getTickCount() - t) / getTickFrequency();
    printf("Time for 1D Gaussian= %.3f [ms]\n", t * 1000);

    imshow("Gaussian Filtered 1D", gaussian_filtered_1D);
    waitKey();

    return 0;
}