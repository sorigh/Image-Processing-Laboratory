#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab8.h"
using namespace std;
using namespace cv;


int main() {
    Mat source = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/Hawkes_Bay_NZ.bmp",
                        IMREAD_GRAYSCALE);

    imshow("Original Image", source);

    int* image_histogram = compute_histogram_naive(source);
    showHistogram("Original Histogram", image_histogram, 256, 100);

    float* pdf = compute_pdf(image_histogram, source);
    int* display_pdf = convert_function2display(pdf);
    showHistogram("pdf", display_pdf, 256, 100);

    float* cpdf = compute_cpdf(pdf);
    int* display_cpdf = convert_function2display(cpdf);
    showHistogram("cpdf", display_cpdf, 256, 100);

    float mean = compute_mean(image_histogram);
    float std = compute_std(pdf, mean);

    printf("The mean of the image is %f and the standard deviation is %f", mean, std);

    Mat img_bin_th = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/eight.bmp",
                            IMREAD_GRAYSCALE);

    edge_image_values values_img = compute_edge_values(img_bin_th);
    int* histogram = compute_histogram_naive(img_bin_th);
    int th = compute_bimodal_threshold(values_img, histogram, 0.1);
    Mat th_img = apply_bimodal_thresholding(img_bin_th, th);
    imshow("Bimodal Th Binary Img", th_img);

    Mat img_histogram_stretching = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/Hawkes_Bay_NZ.bmp",
                                          IMREAD_GRAYSCALE);

    imshow("Image before stretching", img_histogram_stretching);

    int* initial_histogram_stretching = compute_histogram_naive(img_histogram_stretching);
    showHistogram("Histogram initial stretching", initial_histogram_stretching, 256, 100);

    Mat stretched_image = apply_histogram_st_sh(img_histogram_stretching, 10, 250);
    imshow("Image after stretching", stretched_image);

    int* histogram_stretching = compute_histogram_naive(stretched_image);
    showHistogram("Histogram after stretching", histogram_stretching, 256, 100);



    Mat img_histogram_shrink = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/wheel.bmp",
                                      IMREAD_GRAYSCALE);

    imshow("Image before shrink", img_histogram_shrink);

    int* initial_histogram_shrinking = compute_histogram_naive(img_histogram_shrink);
    showHistogram("Histogram initial shrink", initial_histogram_shrinking, 256, 100);

    Mat shrinking_image = apply_histogram_st_sh(img_histogram_shrink, 50, 150);
    imshow("Image after shrinking", shrinking_image);

    int* histogram_shrinking = compute_histogram_naive(shrinking_image);
    showHistogram("Histogram after shrinking", histogram_shrinking, 256, 100);

    Mat img_gamma_correction = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/wilderness.bmp",
                                      IMREAD_GRAYSCALE);
    imshow("Gamma correction original", img_gamma_correction);

    int* initial_histogram_gamma = compute_histogram_naive(img_gamma_correction);
    showHistogram("Histogram initial gamma", initial_histogram_gamma, 256, 100);

    Mat img_gamma_correction_decoding= apply_gamma_correction(img_gamma_correction, 1.4);
    imshow("Gamma correction decoding", img_gamma_correction_decoding);

    int* initial_histogram_gamma_decoding = compute_histogram_naive(img_gamma_correction_decoding);
    showHistogram("Histogram gamma correction decoding", initial_histogram_gamma_decoding, 256, 100);

    Mat img_gamma_correction_encoding= apply_gamma_correction(img_gamma_correction, 0.5);
    imshow("Gamma correction encoding", img_gamma_correction_encoding);

    int* initial_histogram_gamma_encoding = compute_histogram_naive(img_gamma_correction_encoding);
    showHistogram("Histogram gamma correction encoding", initial_histogram_gamma_encoding, 256, 100);

    Mat histogram_eq_1_image = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/Hawkes_Bay_NZ.bmp", IMREAD_GRAYSCALE);
    Mat histogram_eq_2_image = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/wheel.bmp", IMREAD_GRAYSCALE);
    imshow("Histogram equalization 1 original image ", histogram_eq_1_image);
    imshow("Histogram equalization 2 original image", histogram_eq_2_image);

    int* histogram_eq_1_original = compute_histogram_naive(histogram_eq_1_image);
    int* histogram_eq_2_original = compute_histogram_naive(histogram_eq_2_image);
    showHistogram("Histogram equalization 1 original", histogram_eq_1_original, 256, 100);
    showHistogram("Histogram equalization 2 original", histogram_eq_1_original, 256, 100);

    Mat equalized_image_1 = apply_histogram_equalization(histogram_eq_1_image, histogram_eq_1_original);
    Mat equalized_image_2 = apply_histogram_equalization(histogram_eq_2_image, histogram_eq_2_original);
    imshow("Histogram equalized 1 image ", equalized_image_1);
    imshow("Histogram equalized 2 image", equalized_image_2);

    int* histogram_eq_1 = compute_histogram_naive(equalized_image_1);
    int* histogram_eq_2 = compute_histogram_naive(equalized_image_2);
    showHistogram("Histogram equalization 1", histogram_eq_1, 256, 100);
    showHistogram("Histogram equalization 2", histogram_eq_2, 256, 100);

    waitKey();

    return 0;
}