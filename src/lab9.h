#ifndef LAB7_H
#define LAB7_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

const int di[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int dj[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

const int mean_weights[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
const int gaussian_weights[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
const int laplace_1_weights[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
const int laplace_2_weights[9] = {-1, -1, -1, -1, 8, -1, -1, -1, -1};
const int high_pass_filter_1_weights[9] = {0, -1, 0, -1, 5, -1, 0, -1, 0};
const int high_pass_filter_2_weights[9] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};

Mat apply_convolution(Mat source, const int* conv_weights, float additional_conv_term, bool normalization);

void centering_transform(Mat img);

Mat generic_frequency_domain_filter(Mat src, string type, float cutoff);


#endif