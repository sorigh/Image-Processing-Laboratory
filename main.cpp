#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab7.h"
using namespace std;
using namespace cv;


int main() {
    Mat source = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/1_Dilate/balloons_bw.bmp",
                        IMREAD_GRAYSCALE);
    Mat source_boundary = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/5_BoundaryExtraction/reg1neg1_bw.bmp",
                                 IMREAD_GRAYSCALE);

    imshow("Original Image", source);

    int n8_dx[8] = {0,-1,-1,-1,0,1,1,1};
    int n8_dy[8] = {1,1,0,-1,-1,-1,0,1};
    neighborhood_structure n8 = {8, n8_dx, n8_dy};

    int n4_dx[4] = { 0,-1, 0, 1};
    int n4_dy[4] = { 1, 0,-1, 0};
    neighborhood_structure n4 = {4, n4_dx, n4_dy};

    Mat dilation_4n = dilation(source, n4, 1);
    imshow("Dilation 4n", dilation_4n);

    Mat dilation_8n = dilation(source, n8, 1);
    imshow("Dilation 8n", dilation_8n);

    Mat erosion_4n = erosion(source, n4, 1);
    imshow("Erosion 4n", erosion_4n);

    Mat erosion_8n = erosion(source, n8, 1);
    imshow("Erosion 8n", erosion_8n);

    Mat opening_4n = opening(source, n4, 2);
    imshow("Opening 4n", opening_4n);

    Mat opening_8n = opening(source, n8, 2);
    imshow("Opening 8n", opening_8n);

    Mat closing_4n = closing(source, n4, 2);
    imshow("Closing 4n", closing_4n);

    Mat closing_8n = closing(source, n8, 2);
    imshow("Closing 8n", closing_8n);



    Mat boundary_extraction_mat = boundary_extraction(source_boundary, n8);
    imshow("Boundary extraction", boundary_extraction_mat);

    Mat region_filling_mat = region_filling(source_boundary, n8);
    imshow("Region filling", region_filling_mat);

    waitKey();

    return 0;
}