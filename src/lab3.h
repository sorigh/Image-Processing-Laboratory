#ifndef LAB2_H
#define LAB2_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct{
    uchar* grayscale_values;
    uchar count_grayscale_values;
} grayscale_mapping;

bool IsInside(Mat img, int i, int j);

int* compute_histogram_naive(Mat source);

int* compute_histogram_custom(Mat source, int histogram_bins);

float* compute_pdf(int* histogram, Mat source);

void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height);

grayscale_mapping multi_level_thresholding(int wh, float th, float* pdf);

uchar find_closest_histogram_maximum(uchar old_pixel, grayscale_mapping gray_map);

Mat draw_multi_thresholding(Mat source, grayscale_mapping grayscale_map);

uchar update_pixel_floyd_steinberg_dithering(uchar pixel_value, int value);

Mat floyd_steinberg_dithering(Mat source, grayscale_mapping grayscale_map);


#endif
