#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab5.h"
using namespace std;
using namespace cv;

int main() {
    Mat source = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/letters.bmp",
                        IMREAD_GRAYSCALE);

    imshow("Original Image", source);

    labels bfsLabels = BFS_labeling(source);
    Mat result_bfs = color_labels(bfsLabels);
    imshow("BFS", result_bfs);

    labels two_pass_label = Two_pass_labeling(source);
    Mat result_two_pass = color_labels(two_pass_label);
    imshow("Two pass", result_two_pass);

    waitKey();

    return 0;
}