#ifndef LAB7_H
#define LAB7_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct{
    int size;
    int* di;
    int* dj;
} neighborhood_structure;

Mat dilation(Mat source, neighborhood_structure neighborhood, int no_iter);

Mat erosion(Mat source, neighborhood_structure neighborhood, int no_iter);

Mat opening(Mat source, neighborhood_structure neighborhood, int no_iter);

Mat closing(Mat source, neighborhood_structure neighborhood, int no_iter);

Mat boundary_extraction(Mat source, neighborhood_structure neighborhood);

Mat region_filling(Mat source, neighborhood_structure neighborhood);

bool IsInside(int img_rows, int img_cols, int i, int j);

#endif