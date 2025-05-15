#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab9.h"
using namespace std;
using namespace cv;


int main() {

    Mat source = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/cameraman.bmp", IMREAD_GRAYSCALE);
    imshow("Original", source);
//    Test mean filter
    Mat median_result = apply_convolution(source, mean_weights, 1.0f / 9.0f, false);
    imshow("Mean Filter", median_result);

//    Test gaussian filter
    Mat gaussian_result = apply_convolution(source, gaussian_weights, 1.0f / 16.0f, false);
    imshow("Gaussian Filter", gaussian_result);

//    Test laplace filter
    Mat laplace_1_result = apply_convolution(source, laplace_1_weights, 1.0f, true);
    imshow("Laplace Filter 1", laplace_1_result);
    Mat laplace_2_result = apply_convolution(source, laplace_2_weights, 1.0f, true);
    imshow("Laplace Filter 2", laplace_2_result);
//    Test high pass filter

    Mat high_pass_filter_1_result = apply_convolution(source, high_pass_filter_1_weights, 1.0f, true);
    imshow("High Pass Filter 1", high_pass_filter_1_result);

    Mat high_pass_filter_2_result = apply_convolution(source, high_pass_filter_2_weights, 1.0f, true);
    imshow("High Pass Filter 2", high_pass_filter_2_result);

    // Ideal low pass filter
    Mat ideal_low_pass_result = generic_frequency_domain_filter(source, "ideal_low_pass", 50.0f);

    imshow("Ideal Low Pass Filter", ideal_low_pass_result);

    // Ideal high pass filter

    Mat ideal_high_pass_result = generic_frequency_domain_filter(source, "ideal_high_pass", 50.0f);

    imshow("Ideal High Pass Filter", ideal_high_pass_result);

    // Gaussian low pass filter

    Mat gaussian_low_pass_result = generic_frequency_domain_filter(source, "gaussian_low_pass", 50.0f);

    imshow("Gaussian Low Pass Filter", gaussian_low_pass_result);

    // Gaussian high pass filter

    Mat gaussian_high_pass_result = generic_frequency_domain_filter(source, "gaussian_high_pass", 50.0f);

    imshow("Gaussian High Pass Filter", gaussian_high_pass_result);

    waitKey();

    return 0;
}