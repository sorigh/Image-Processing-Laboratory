#ifndef LAB6_H
#define LAB6_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

const int n8_di[8] = {0,-1,-1, -1, 0, 1, 1, 1};
const int n8_dj[8] = {1, 1, 0, -1, -1,-1, 0, 1};

typedef struct{
    vector<Point> border;
    vector<int> dir_vector;
} contour;

Point find_P_0(Mat source);

contour extract_contour(Mat source, Point P_0);

Mat draw_contour(contour cnt, Mat source);

void print_AC_DC_chain_codes(contour cnt);

Mat contour_reconstruction(FILE *pf, Mat background);

#endif