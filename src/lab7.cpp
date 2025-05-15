#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab7.h"
#include <fstream>


using namespace std;
using namespace cv;

bool IsInside(int img_rows, int img_cols, int i, int j){
    /*
    * Implement a function called isInside(img, i, j) which checks if the position indicated by
    * the pair (i,j) (row, column) is inside the image img.
    */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return (i >= 0 && i < img_rows && j >= 0 && j < img_cols);

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****
    return true;
}

Mat dilation(Mat source, neighborhood_structure neighborhood, int no_iter){

    //TODO: Implement the dilation operation for no_iter times using the structuring element defined by
    // the neighborhood argument
    Mat dst, aux;
    int rows, cols;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    dst = source.clone();
    rows = source.rows;
    cols = source.cols;
    for (int iter = 0; iter < no_iter; iter++) {
        aux = dst.clone();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (aux.at<uchar>(i, j) == 0) {
                    for (int k=0; k < neighborhood.size; k++){
                        int ni=neighborhood.di[k] + i;
                        int nj=neighborhood.dj[k] + j;

                        if (IsInside(aux.rows, aux.cols, ni, nj)) {
                            dst.at<uchar>(ni, nj) = 0;
                        }
                    }
                }
            }
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return dst;

}

Mat erosion(Mat source, neighborhood_structure neighborhood, int no_iter) {
    Mat dst, aux;
    int rows, cols;

    dst = source.clone();
    rows = source.rows;
    cols = source.cols;

    for (int iter = 0; iter < no_iter; iter++) {
        aux = dst.clone();
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool all_black = true;
                for (int k = 0; k < neighborhood.size; k++) {
                    int ni = i + neighborhood.di[k];
                    int nj = j + neighborhood.dj[k];

                    if (IsInside(rows, cols, ni, nj)) {
                        if (aux.at<uchar>(ni, nj) != 0) {
                            all_black = false;
                            break;
                        }
                    } else {
                        all_black = false;
                        break;
                    }
                }
                if (all_black && aux.at<uchar>(i, j) == 0) {
                    dst.at<uchar>(i, j) = 0;
                } else {
                    dst.at<uchar>(i, j) = 255;
                }
            }
        }
    }

    return dst;
}
Mat opening(Mat source, neighborhood_structure neighborhood, int no_iter) {

    //TODO: Implement the opening operation for no_iter times using the structuring element defined by
    // the neighborhood argument

    Mat dst, aux;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return dilation(erosion(source, neighborhood, no_iter), neighborhood, no_iter);

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****


    return dst;

}

Mat closing(Mat source, neighborhood_structure neighborhood, int no_iter) {

    //TODO: Implement the closing operation for no_iter times using the structuring element defined by
    // the neighborhood argument

    Mat dst, aux;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return erosion(dilation(source, neighborhood, no_iter), neighborhood, no_iter);


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return dst;
}

Mat boundary_extraction(Mat source, neighborhood_structure neighborhood) {

    //TODO: Implement the boundary extraction algorithm for no_iter times using the structuring element defined by
    // the neighborhood argument

    int rows, cols;
    Mat erosion_mat, dst;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    rows = source.rows;
    cols = source.cols;
    dst = Mat::zeros(source.size(), source.type());

    erosion_mat = erosion(source, neighborhood, 1);

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (source.at<uchar>(y, x) != erosion_mat.at<uchar>(y, x)) {
                dst.at<uchar>(y, x) = 255;
            } else {
                dst.at<uchar>(y, x) = 0;
            }
        }
    }


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return dst;

}

bool equal_mat(Mat A, Mat B){
    //TODO: Implement a function that returns true is all elements from A are equal to all elements in B
    // assumption that A and B has the same size

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    if (A.size() != B.size()) {
        return false;
    }
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            if (A.at<uchar>(i, j) != B.at<uchar>(i, j)) {
                return false;
            }
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return true;

}
Mat region_filling(Mat source, neighborhood_structure neighborhood) {

    //TODO: Implement the region filling algorithm for no_iter times using the structuring element defined by
    // the neighborhood argument

    Mat dst;
    int rows, cols;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = source.rows;
    cols = source.cols;
    dst = Mat::ones(source.size(), source.type()) * 255; //init bkd color
    Mat prev_dst = Mat::ones(source.size(), source.type()) * 255;

    int start_row = rows / 2;
    int start_col = cols / 2;
    dst.at<uchar>(start_row, start_col) = 0;  // obj pixel

    bool has_changes = true;
    while (has_changes) {
        prev_dst = dst.clone(); //Xk-1

        Mat dilated = dilation(dst, neighborhood, 1);
        Mat complement = ~source;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (dilated.at<uchar>(i, j) == 0 && complement.at<uchar>(i, j) == 0) {
                    dst.at<uchar>(i, j) = 0; //obj
                }
            }
        }

        // check Xk = Xk-1
        has_changes = !equal_mat(dst, prev_dst);
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return dst;

}