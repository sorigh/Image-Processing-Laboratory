#ifndef LAB5_H
#define LAB5_H
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

const int n8_di[8] = {0,-1,-1, -1, 0, 1, 1, 1};
const int n8_dj[8] = {1, 1, 0, -1, -1,-1, 0, 1};

const int np_di[4] = { 0,-1,-1, -1};
const int np_dj[4] = { -1,-1, 0, 1};

typedef struct {
    Mat labels;
    int no_labels;
}labels;

Mat color_labels(labels labels_str);

labels BFS_labeling(Mat source);

labels Two_pass_labeling(Mat source);

#endif