#include <iostream>
#include <opencv2/opencv.hpp>
#include "src/lab6.h"
using namespace std;
using namespace cv;

int main() {

    Mat source = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/star_R90.bmp",
                        IMREAD_GRAYSCALE);

    imshow("Original Image", source);

    Point P_0 = find_P_0(source);
    contour cnt = extract_contour(source, P_0);
    Mat mat_cnt = draw_contour(cnt, source);

    imshow("Contour", mat_cnt);

    print_AC_DC_chain_codes(cnt);

    FILE *pf;
    pf = fopen("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/reconstruct.txt", "r");
    Mat background = imread("/Users/Sorana/Desktop/Image_Processing_Laboratory/images/gray_background.bmp", IMREAD_GRAYSCALE);

    Mat reconstruction = contour_reconstruction(pf, background);

    imshow("Reconstruction", reconstruction);

    waitKey();

    return 0;
}