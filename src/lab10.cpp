#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab10.h"
#include <fstream>
using namespace std;
using namespace cv;

Mat linear_filtering(Mat source, int kernel_size, string filter_type){
    // Implement the median, minimum and maximum filtering algorithm, using a kernel of size kernel_size and the corresponding filter_type.
    // The function should return the filtered image
    // Implementation Hint: You can use a vector to store the pixel values and sort them using sort.


    Mat result;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    result = source.clone();
    // distanta centrul ferestrei pana la margine
    int offset = kernel_size / 2; // cat de departe se extinde kernelul

    // incepem de la offset -> evitam nr de pixeli ptr kernel sa ne punem direct
    // in centrul kernelului
    for(int i = offset; i < source.rows - offset; i++) {
        for(int j = offset; j < source.cols - offset; j++) {
            vector<uchar> values;

            // parcurgem kernel
            for(int ki = -offset; ki <= offset; ki++){
                for(int kj = -offset; kj <= offset; kj++){
                    values.push_back(source.at<uchar>(i + ki, j + kj));
                }
            }

            //sortare valori
            sort(values.begin(), values.end());

            if(filter_type == "median"){
                //media
                result.at<uchar>(i, j) = values[values.size() / 2];
            } else if(filter_type == "minimum"){
                //minim
                result.at<uchar>(i, j) = values[0];
            } else if(filter_type == "maximum"){
                //maxim
                result.at<uchar>(i, j) = values[values.size() - 1];
            }

        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}

Mat compute_kernel_2D(int kernel_size){
    // This function should return a Gaussian kernel of size (kernel_size, kernel_size)
    // The std should be kernel_size/6.0
    Mat kernel;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //G(x, y) = (1 / (2 * π * sigma^2)) * exp( - ((x - x0)^2 + (y - y0)^2) / (2 * sigma^2) )
    // x0 y0 centru. x,y in kernel.

    float sigma = kernel_size / 6.0;
    int center = kernel_size / 2;
    kernel = Mat(kernel_size, kernel_size, CV_32F);
    float sum = 0.0;

    for(int i = 0; i < kernel_size; i++){
        for(int j = 0; j < kernel_size; j++){
            int x = i - center; // coordonate relative la centru
            int y = j - center; // coordonate relative la centru
            float value = exp(-(x*x + y*y) / (2 * sigma * sigma)) / (2 * CV_PI * sigma * sigma);
            kernel.at<float>(i, j) = value;
            // toate val din kernel
            sum += value;
        }
    }
    //normalizare -> suma tuturor val = 1
    kernel /= sum;


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return kernel;

}

Mat apply_gaussian_filtering_2D(Mat source, int kernel_size){
    // This function should apply a Gaussian filter to the source image using the kernel computed in compute_kernel function
    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    result = Mat::zeros(source.size(), source.type());
    Mat kernel = compute_kernel_2D(kernel_size);
    int offset = kernel_size / 2;

    for (int i = offset; i < source.rows - offset; i++) {
        for (int j = offset; j < source.cols - offset; j++) {
            float sum = 0.0;

            // kernel centrat in i j si parcurgere vecini
            for (int ki = -offset; ki <= offset; ki++) {
                for (int kj = -offset; kj <= offset; kj++) {
                    uchar pixel = source.at<uchar>(i + ki, j + kj);
                    //valoarea din kernel ptr pixel
                    float weight = kernel.at<float>(ki + offset, kj + offset);
                    // calc valoare in functie de importanta lui (apropiere)
                    sum += pixel * weight;
                }
            }
            // kernel deja normalizat
            result.at<uchar>(i, j) = static_cast<uchar>(sum);
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;

}

vector<float> compute_kernel_1D(int kernel_size){
    // This function should return a Gaussian kernel of size (kernel_size, 1)
    // The std should be kernel_size/6.0
    vector<float> kernel;


    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    float sigma = kernel_size / 6.0;
    int offset = kernel_size / 2;

    kernel.resize(kernel_size);
    float sum = 0.0;

    for (int x = -offset; x <= offset; x++) {
        float value = exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * CV_PI) * sigma);
        // vector de la 0
        kernel[x + offset] = value;
        // add all values
        sum += value;
    }

    // normalizare
    for(int i = 0; i < kernel_size; i++){
        kernel[i] /= sum;
    }


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return kernel;
}

Mat apply_gaussian_filtering_1D(Mat source, int kernel_size){

    // This function should apply a Gaussian filter to the source image using the kernel computed in compute_kernel_1D
    // by applying successive 1D convolutions in the x and y directions.

    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    result = source.clone();
    vector<float> kernel = compute_kernel_1D(kernel_size);
    int offset = kernel_size / 2;
    // Apply 1D convolution in the x direction

    // fiecare rand complet, fara restrictii (nu merge in sus sau in jos)
    // avem si j+k unde k e si -offset -> j=0
    // avem si i+k unde k incepe de la -offset -> i = 0
    for (int i = offset; i < source.rows - offset; i++) {
        for (int j = offset; j < source.cols - offset; j++) {
            // pe x
            float sum = 0.0f;

            for (int k = -offset; k <= offset; k++) {
                uchar pixel = source.at<uchar>(i, j + k);
                float weight = kernel[k + offset];
                sum += pixel * weight;
            }
            result.at<uchar>(i, j) = static_cast<uchar>(sum);

            // pe y
            float sum2 = 0.0f;

            for (int k = -offset; k <= offset; k++) {
                uchar pixel = result.at<uchar>(i + k, j);
                float weight = kernel[k + offset];
                sum2 += pixel * weight;
            }
            result.at<uchar>(i, j) = static_cast<uchar>(sum2);


        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;

}
