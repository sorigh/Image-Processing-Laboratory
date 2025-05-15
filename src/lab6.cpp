#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include "lab6.h"

using namespace std;
using namespace cv;

Point find_P_0(Mat source){
    /*
     * Find the initial point of the contour and return it
     */
    Point P_0;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    P_0 = Point(0, 0);
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            if (source.at<uchar>(i, j) == 0) {
                P_0.x = j;
                P_0.y = i;
                break;
            }
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return P_0;
}

contour extract_contour(Mat source, Point P_0){

    /*Extract the contour for a neighborhood of 8. You should return a contour structure with a vector
     * containing the point and a vector containing the directions. */

    int dir;
    Point P_current;
    vector<Point> border;
    vector<int> dir_vector;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    dir = 7;
    int n = 0;
    P_current = P_0;
    border.push_back(P_current);

    do {
        n++;
        if (dir % 2 == 0)
            dir = (dir + 7) % 8;
        else
            dir = (dir + 6) % 8;


        while (source.at<uchar>(P_current.y + n8_di[dir], P_current.x + n8_dj[dir]) != 0) {
            dir = (dir + 1) % 8;
        }

        P_current.x += n8_dj[dir];
        P_current.y += n8_di[dir];

        border.push_back(P_current);
        dir_vector.push_back(dir);

    } while (!(border[n] == border[1] && border[n - 1] == P_0 && n >= 2));



    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return {border, dir_vector};
}

Mat draw_contour(contour cnt, Mat source){

    /*
     * Draw the contour using the border variable from cnt structure
     */

    Mat dst;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    dst = Mat(source.rows, source.cols, CV_8UC1,255);
    for(Point b : cnt.border)
    {
        dst.at<uchar>(b.y,b.x)=0;
    }


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****


    return dst;
}

void print_AC_DC_chain_codes(contour cnt){
    /*
     * Print the AC and DC chain codes
     * You have to compute the DC one. The AC is already computed :)
     */

    printf("The AC vector is: ");

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    for (int d : cnt.dir_vector) {
        printf("%d ", d);
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    printf("\nThe DC vector is: ");

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    vector<int> dc;

    for(int i=0;i<cnt.dir_vector.size()-1;i++) {
        dc.push_back((cnt.dir_vector[i + 1] - cnt.dir_vector[i] + 8) % 8);
        printf("%d ",dc[i]);
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

Mat contour_reconstruction(FILE *pf, Mat background) {

    /*
     * from the file read the chain code and reconstruct the image
     */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****


    int row, col, chainSize;
    fscanf(pf, "%d %d", &row, &col);
    fscanf(pf, "%d", &chainSize);

    for (int i = 0; i < background.rows; ++i)
        for (int j = 0; j < background.cols; ++j)
            background.at<uchar>(i, j) = 255;

    background.at<uchar>(row, col) = 0;
    for (int i = 0; i < chainSize; ++i) {
        int dir;
        fscanf(pf, "%d", &dir);
        row += n8_di[dir];
        col += n8_dj[dir];
        background.at<uchar>(row, col) = 0;
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return background;

}