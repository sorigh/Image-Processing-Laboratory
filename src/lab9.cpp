#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab9.h"
using namespace std;
using namespace cv;

Mat apply_convolution(Mat source,const int* conv_weights, float additional_conv_term, bool normalization){

    // Given a source image and a convolution kernel, this function applies the convolution to the image.
    // The convolution kernel is represented as a 1D array of weights, and the additional_conv_term is added(multiplied) to the result of
    // the convolution is necessary.
    // Hint: Start from the second row and column of the image and iterate through the image, applying the convolution kernel to each pixel.
    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //convert to float
    Mat float_source;
    source.convertTo(float_source, CV_32FC1);

    result = Mat::zeros(source.size(), CV_32FC1);

    // First pass: apply convolution and store float results
    for (int i = 1; i < source.rows - 1; ++i) {
        for (int j = 1; j < source.cols - 1; ++j) {
            float sum = 0.0f;

            //iterate throgh kernel
            for (int k = 0; k < 9; ++k) {
                int ni = i + di[k];
                int nj = j + dj[k];
                float pixel = float_source.at<float>(ni, nj);
                //using kernel weight for that pixel
                sum += pixel * conv_weights[k];
            }

            // additional term
            result.at<float>(i, j) = sum * additional_conv_term;
        }
    }


    // Second pass: normalize if needed and store into final result
    if (normalization) {
        normalize(result, result, 0, 255, NORM_MINMAX);
    }

    // convert back to unsigned char so we can view img
    result.convertTo(result, CV_8UC1);
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}

void centering_transform(Mat img){
    //expects floating point image
    for (int i = 0; i < img.rows; i++){
        for (int j = 0; j < img.cols; j++){
            img.at<float>(i, j) = ((i + j) & 1) ? -img.at<float>(i, j) : img.at<float>(i, j);
        }
    }
}

Mat generic_frequency_domain_filter(Mat src, string type, float cutoff){
    //convert input image to float image
    Mat srcf;
    src.convertTo(srcf, CV_32FC1);

    //centering transformation
    centering_transform(srcf);

    //perform forward transform with complex image output
    Mat fourier;
    dft(srcf, fourier, DFT_COMPLEX_OUTPUT);

    //split into real and imaginary channels
    Mat channels[] = { Mat::zeros(src.size(), CV_32F), Mat::zeros(src.size(), CV_32F) };
    split(fourier, channels); // channels[0] = Re(DFT(I)), channels[1] = Im(DFT(I))

    //calculate magnitude and phase in floating point images mag and phi
    Mat mag, mag_norm, phi;
    magnitude(channels[0], channels[1], mag);
    phase(channels[0], channels[1], phi);
    //display the phase and magnitude images here

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    Mat mag_log;
    mag += 1;
    log(mag, mag_log);
    normalize(mag_log, mag_log, 0, 255, NORM_MINMAX);
    mag_log.convertTo(mag_log, CV_8UC1);
    imshow("Magnitude (log)", mag_log);

    normalize(phi, phi, 0, 255, NORM_MINMAX);
    phi.convertTo(phi, CV_8UC1);
    imshow("Phase", phi);


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****


    //insert filtering operations on Fourier coefficients here

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    int rows = src.rows, cols = src.cols;
    Point center = Point(cols / 2, rows / 2);
    float D0 = cutoff;

    for (int u = 0; u < rows; ++u) {
        for (int v = 0; v < cols; ++v) {
            float dx = center.x - u;
            float dy = center.y - v;
            float D = sqrt(dx * dx + dy * dy);
            float H = 1.0f;

            if (type == "ideal_low_pass") {
                H = (D <= D0) ? 1.0f : 0.0f;
            } else if (type == "ideal_high_pass") {
                H = (D > D0) ? 1.0f : 0.0f;
            } else if (type == "gaussian_low_pass") {
                H = exp(-(D * D) / (D0 * D0));
            } else if (type == "gaussian_high_pass") {
                H = 1.0f - exp(-(D * D) / (D0 * D0));
            }

            channels[0].at<float>(u, v) *= H;
            channels[1].at<float>(u, v) *= H;
        }
    }


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    //perform inverse transform and put results in dstf
    Mat dst, dstf;
    merge(channels, 2, fourier);
    dft(fourier, dstf, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);

    //inverse centering transformation
    centering_transform(dstf);

    //normalize the result and put in the destination image
    normalize(dstf, dst, 0, 255, NORM_MINMAX, CV_8UC1);
    //Note: normalizing distorts the resut while enhancing the image display in the range [0,255].
    //For exact results (see Practical work 3) the normalization should be replaced with convertion:
    //dstf.convertTo(dst, CV_8UC1);
    return dst;
}

