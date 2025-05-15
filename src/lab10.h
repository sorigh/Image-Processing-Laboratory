#ifndef LAB10_H
#define LAB10_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat linear_filtering(Mat source, int kernel_size, string filter_type);

Mat compute_kernel_2D(int kernel_size);

Mat comoute_kernel_1D(int kernel_size);

Mat apply_gaussian_filtering_2D(Mat source, int kernel_size);

Mat apply_gaussian_filtering_1D(Mat source, int kernel_size);

#endif