#ifndef LAB7_H
#define LAB7_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct{
    int min_value;
    int max_value;
} edge_image_values;

void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height);

int* convert_function2display(float* func);

float compute_mean(int* histogram);

float compute_std(float* pdf, float mean);

int* compute_histogram_naive(Mat source);

float* compute_pdf(int* histogram, Mat source);

float* compute_cpdf(float* pdf);

edge_image_values compute_edge_values(Mat source);

int compute_bimodal_threshold(edge_image_values img_values, int* histogram, float err);

Mat apply_bimodal_thresholding(Mat source, int th);

int compute_new_value_histogram_st_sh(int g_in, int g_in_min, int g_in_max, int g_out_min, int g_out_max);

Mat apply_histogram_st_sh(Mat source, int g_out_min, int g_out_max);

Mat apply_gamma_correction(Mat source, float gamma);

Mat apply_histogram_equalization(Mat source, int* histogram);

#endif