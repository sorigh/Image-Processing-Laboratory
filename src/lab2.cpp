#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab2.h"
using namespace std;
using namespace cv;

image_channels_bgr break_channels(Mat source){

    /*
     * Create a function that will copy the R, G and B channels of a color,
     * RGB image (CV_8UC3 type) into three matrices of type CV_8UC1 (grayscale images).
     * Return the three matrices in an image_channels_bgr structure
     *
     * Inputs:
     *  source: the source image(BGR)
     * Variables:
     *  rows: number of rows of the source matrix
     *  cols: number of cols of the source matrix
     *  B, G, R: Matrices that will store each a color channel
     *  bgr_channels: structure of type image_channels_bgr that will return three channels
     */

    int rows, cols;
    Mat B, G, R;
    image_channels_bgr bgr_channels;



    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = source.rows;
    cols = source.cols;

    B = Mat(rows, cols, CV_8UC1);
    G = Mat(rows, cols, CV_8UC1);
    R = Mat(rows, cols, CV_8UC1);

    for (int i=0;i<rows; i++) {
        for (int j = 0; j<cols; j++) {
            Vec3b pixel = source.at<Vec3b>(i, j);
            B.at<uchar>(i, j) = pixel[0];// B
            G.at<uchar>(i, j) = pixel[1];// G
            R.at<uchar>(i, j) = pixel[2];// R
        }
    }
    bgr_channels.B = B;
    bgr_channels.G = G;
    bgr_channels.R = R;
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return bgr_channels;

}

void display_channels(image_channels_bgr bgr_channels){
    /*
     * Display each channel in a different window
     * Do not put here the waitKey() try to use only one at the end of the lab
     * Input:
     *  bgr_channels: structure of type image_channels_bgr that will store B, G, R channels
     *
     */
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    imshow("B channel", bgr_channels.B);
    imshow("G channel", bgr_channels.G);
    imshow("R channel", bgr_channels.R);
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

Mat bgr_2_grayscale(Mat source){
    /*
    * Create a function that will convert a color RGB image (CV_8UC3 type) to a grayscale image (CV_8UC1),
    * and return the result image
    * Inputs: source: the source matrix(BGR)
    * Variables:
    *  rows: number of rows of the source matrix
    *  cols: number of cols of the source matrix
    *  grayscale_image: The grayscale image that you will obtain and return
    */
    int rows, cols;
    Mat grayscale_image;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = source.rows;
    cols = source.cols;
    grayscale_image = Mat(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Vec3b pixel = source.at<Vec3b>(i, j);
            uchar gray_value = (pixel[0] + pixel[1] + pixel[2]) / 3;
            grayscale_image.at<uchar>(i, j) = gray_value;
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return grayscale_image;

}

Mat grayscale_2_binary(Mat source, int threshold){
    /*
    * Create a function for converting from grayscale to black and white (binary), using (2.2).
    * Test the operation on multiple images, and using multiple thresholds.
    * Inputs:
    *    source: grayscale image
    *    threshold: the threshold you are going to use to perform the binarization
    *  Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    binary: the resulted binarized image
    */

    int rows, cols;
    Mat binary;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = source.rows;
    cols = source.cols;
    binary = Mat(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uchar pixel = source.at<uchar>(i, j);
            uchar binary_value = pixel < threshold ? 0 : 255;
            binary.at<uchar>(i, j) = binary_value;
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return binary;
}

image_channels_hsv bgr_2_hsv(image_channels_bgr bgr_channels){
    /*
    * Create a function that will compute the H, S and V values from the R, G, B channels of
    * an image, using the equations from 2.6. Store each value (H, S, V) in a CV_8UC1 matrix that will be
    * stored in an image_channels_hsv struct.
    * Inputs:
    *    bgr_channels: structure that stores the B, G, R channels of an image
    * Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    H, S, V: matrices that will store the values of the 3 different channels (Pay attention to the type of elements
    *       that are stored in these matrices.
    *    hsv_channels: structure that will store the H, S, V channels
    */

    int rows, cols;
    Mat H, S, V;
    image_channels_hsv hsv_channels;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = bgr_channels.B.rows;
    cols = bgr_channels.B.cols;

    H = Mat(rows, cols, CV_32FC1);
    S = Mat(rows, cols, CV_32FC1);
    V = Mat(rows, cols, CV_32FC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            float R = (float)bgr_channels.R.at<uchar>(i, j) / 255.0f;
            float G = (float)bgr_channels.G.at<uchar>(i, j) / 255.0f;
            float B = (float)bgr_channels.B.at<uchar>(i, j) / 255.0f;

            float M = max(R, max(G, B));
            float m = min(R, min(G, B));
            float C = M - m;

            //value
            float V_val = M;

            //saturation
            float S_val = 0;
            if (V_val!= 0)
                S_val = C / V_val;

            //hue
            float H_val = 0;
            if (C != 0) {
                if (M == R)
                    H_val = 60 * (G - B) / C;
                else if (M == G)
                    H_val = 120 + 60 * (B - R) / C;
                else if (M == B)
                    H_val = 240 + 60 * (R - G) / C;
            }
            if (H_val < 0)
                H_val += 360;

            H.at<float>(i, j) = H_val;
            S.at<float>(i, j) = S_val;
            V.at<float>(i, j) = V_val;


        }
    }

    hsv_channels.H = H;
    hsv_channels.S = S;
    hsv_channels.V = V;

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return hsv_channels;
}

void display_hsv_channels(image_channels_hsv hsv_channels){

    /*
    * Display the three channels
    * Inputs:
    *    hsv_channels: structure that stores the H, S, V channels of an image.
    *      In order to display them don't forget to normalize them accordingly
    *  Variables:
    *    rows: number of rows of the source matrix
    *    cols: number of cols of the source matrix
    *    H_norm, S_norm, V_norm: Normalized matrices.
    */

    int rows, cols;
    Mat H_norm, S_norm, V_norm;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = hsv_channels.H.rows;
    cols = hsv_channels.H.cols;

    H_norm = Mat(rows, cols, CV_8UC1);
    S_norm = Mat(rows, cols, CV_8UC1);
    V_norm = Mat(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            H_norm.at<uchar>(i, j) = (int)(hsv_channels.H.at<float>(i, j) * 255.0f / 360.0f);
            S_norm.at<uchar>(i, j)= (int)(hsv_channels.S.at<float>(i, j) * 255.0f);
            V_norm.at<uchar>(i, j)  = (int)(hsv_channels.V.at<float>(i, j) * 255.0f);

        }
    }

    imshow("H channel", H_norm);
    imshow("S channel", S_norm);
    imshow("V channel", V_norm);
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

bool IsInside(Mat img, int i, int j){
    /*
    * Implement a function called isInside(img, i, j) which checks if the position indicated by
    * the pair (i,j) (row, column) is inside the image img.
    */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    int rows = img.rows;
    int cols = img.cols;

    if (i >= 0 && i < rows && j >= 0 && j < cols) {
        return true;
    }
    return false;
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}
