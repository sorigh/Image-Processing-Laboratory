#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab3.h"
using namespace std;
using namespace cv;

int main(){


    Mat cameraman = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/cameraman.bmp", IMREAD_GRAYSCALE);
    Mat saturn = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/saturn.bmp", IMREAD_GRAYSCALE);

    imshow("Cameraman original", cameraman);
    imshow("Saturn original", saturn);

    int* histogram_cameraman = compute_histogram_naive(cameraman);
    float* pdf_cameraman = compute_pdf(histogram_cameraman, cameraman);

    int* histogram_saturn = compute_histogram_naive(saturn);
    float* pdf_saturn = compute_pdf(histogram_saturn, saturn);

    printf("Some histogram values are: ");
    for(int i=50; i < 56; i++){
        printf("%d ", histogram_cameraman[i]);
    }
    printf("\n");

    printf("Some pdf values are: ");
    for(int i=50; i < 56; i++){
        printf("%f ", pdf_cameraman[i]);
    }

    showHistogram("Histogram", histogram_cameraman, 256, 100);

    int* histogram_custom = compute_histogram_custom(cameraman, 40);
    showHistogram("Histogram reduced bins", histogram_custom, 40, 100);


    grayscale_mapping grayscale_map_saturn = multi_level_thresholding(5, 0.0003, pdf_saturn);

    grayscale_mapping grayscale_map_cameraman = multi_level_thresholding(5, 0.0003, pdf_cameraman);
    Mat image_multi_threshold_cameraman = draw_multi_thresholding(cameraman, grayscale_map_cameraman);
    imshow("Multi level threshold cameraman", image_multi_threshold_cameraman);
    Mat fsd_cameraman = floyd_steinberg_dithering(cameraman, grayscale_map_cameraman);
    imshow("Floyd Steinberg Dithering cameraman", fsd_cameraman);

    Mat image_multi_threshold_saturn = draw_multi_thresholding(saturn, grayscale_map_saturn);
    imshow("Multi level threshold saturn", image_multi_threshold_saturn);
    Mat fsd_saturn = floyd_steinberg_dithering(saturn, grayscale_map_saturn);
    imshow("Floyd Steinberg Dithering saturn", fsd_saturn);

    waitKey(0);
    return 0;
}
