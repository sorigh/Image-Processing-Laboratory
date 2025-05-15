#ifndef LAB2_H
#define LAB2_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

typedef struct{
    Mat contour;
    int length;
} perimeter;

typedef struct{
    int c_min;
    int c_max;
    int r_min;
    int r_max;
} circumscribed_rectangle_coord;

typedef struct{
    Point p1;
    Point p2;
} elongation_axis;

const int y_coord_neighborhood[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int x_coord_neighborhood[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

void geom_features(int event, int x, int y, int flags, void* param);

#endif