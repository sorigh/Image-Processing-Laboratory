#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab8.h"
#include <fstream>
using namespace std;
using namespace cv;

void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height){

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    Mat imgHist(hist_height, hist_cols, CV_8UC3, CV_RGB(255, 255, 255));// constructs a white image
    //computes histogram maximum
    int max_hist = 0;
    for(int i = 0; i<hist_cols; i++)
        if(hist[i]> max_hist)
            max_hist = hist[i];
    double scale = 1.0;
    scale = (double)hist_height / max_hist;
    int baseline = hist_height - 1;
    for(int x = 0; x < hist_cols; x++){
        Point p1 = Point(x, baseline);
        Point p2 = Point(x, baseline - cvRound(hist[x]* scale));
        line(imgHist, p1, p2, CV_RGB(255, 0, 255));// histogram bins
        // colored in magenta
    }
    imshow(name, imgHist);

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

int* convert_function2display(float* func){

    int* func_display = (int*) calloc(256, sizeof(int));

    for(int i=0; i<256; i++){
        func_display[i] = int(func[i] * 1000);
    }
    return func_display;
}

int* compute_histogram_naive(Mat source){

    // TODO: Compute the naive histogram of an image

    int* histogram = (int*)calloc(256, sizeof(int));

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    for(int i = 0; i < source.rows; i++) {
        for(int j = 0; j < source.cols; j++) {
            int val = source.at<uchar>(i, j);
            histogram[val]++;
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return histogram;

}

float* compute_pdf(int* histogram, Mat source){

    // TODO: Compute the normalized histogram (pdf)

    float* pdf = (float*)calloc(256, sizeof(float));

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    int all = source.rows * source.cols;
    for(int i = 0; i < 256; i++){
        pdf[i] = (float)histogram[i] / all;
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return pdf;

}

float* compute_cpdf(float* pdf){
    // TODO: Compute the cumulative probability density function (cpdf)


    float* cpdf = (float*)calloc(256, sizeof(float));

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    cpdf[0] = pdf[0];
    for(int i = 1; i < 256; i++){
        cpdf[i] = cpdf[i - 1] + pdf[i];
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return cpdf;
}

float compute_mean(int* histogram){

    // TODO: compute the mean given the histogram of the image
    float mean;
    int total_pixels;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    // mean =  1/total_pixels * (g * h(g)), g is 0 to 256
    mean = 0;
    total_pixels = 0;
    for(int g = 0; g < 256; g++) {
        mean += g * histogram[g];
        total_pixels += histogram[g];
    }
    if(total_pixels > 0)
        mean /= total_pixels;

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return mean;
}

float compute_std(float* pdf, float mean){

    // TODO: compute standard deviation given the pdf and mean
    float std;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    //std = sqrt( sum ((g - mean)^2 * p(g) ), , g is 0 to 256
    std = 0.0;
    for(int g = 0; g < 256; g++) {
        std += (g - mean) * (g - mean) * pdf[g];
    }
    std = sqrt(std);


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return std;
}

edge_image_values compute_edge_values(Mat source){

    // TODO: compute minimum and maximum value in an image and return in accordingly
    int min, max;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    min = 255;
    max = 0;

    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            int val = source.at<uchar>(i, j);
            if (val < min) min = val;
            if (val > max) max = val;
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return {min, max};
}

int compute_bimodal_threshold(edge_image_values img_values, int* histogram, float err){

    // TODO : compute the bimodal threshold using the histogram of the image, return only the threshold value
    int min, max;
    float Tk, Tk_1;
    float mean_1, mean_2, no_pixels_mean_1, no_pixels_mean_2;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    min = img_values.min_value;
    max = img_values.max_value;
    Tk = (min + max) / 2.0;

    do {
        float mean1 = 0, mean2 = 0;
        int count1 = 0, count2 = 0;

        // mean 1
        for(int i = min; i <= Tk; i++) {
            mean1 += i * histogram[i];
            count1 += histogram[i];
        }
        // mean 2
        for(int i = Tk + 1; i <= max; i++) {
            mean2 += i * histogram[i];
            count2 += histogram[i];
        }

        mean1 = (count1 > 0) ? mean1 / count1 : 0;
        mean2 = (count2 > 0) ? mean2 / count2 : 0;

        Tk_1 = Tk;
        Tk = (mean1 + mean2) / 2;

    } while(fabs(Tk - Tk_1) >= err);


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return Tk;

}

Mat apply_bimodal_thresholding(Mat source, int th){

    // TODO: apply the bimodal thresholding to the image, given the threshold value previously computed

    Mat dst;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    dst = source.clone();
    for(int i = 0; i < dst.rows; i++) {
        for(int j = 0; j < dst.cols; j++) {
            dst.at<uchar>(i, j) = (source.at<uchar>(i, j) > th) ? 255 : 0;
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return dst;
}

int compute_new_value_histogram_st_sh(int g_in, int g_in_min, int g_in_max, int g_out_min, int g_out_max){

    // TODO: compute the new value of the pixel using histogram stretching/shrinking returning the new value

    float g_out;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    g_out = (float)(g_in - g_in_min) * (g_out_max - g_out_min) / (g_in_max - g_in_min) + g_out_min;

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return int(g_out);
}

Mat apply_histogram_st_sh(Mat source, int g_out_min, int g_out_max){

    //TODO: apply histogram stretching/shrinking to the image using the function compute_new_value_histogram_st_sh and compute_edge_values

    Mat result;
    int g_in_min, g_in_max;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    edge_image_values edges = compute_edge_values(source);
    g_in_min = edges.min_value;
    g_in_max = edges.max_value;

    result = source.clone();
    for(int i = 0; i < result.rows; i++) {
        for(int j = 0; j < result.cols; j++) {
            int g_in = source.at<uchar>(i, j);
            result.at<uchar>(i, j) = compute_new_value_histogram_st_sh(g_in, g_in_min, g_in_max, g_out_min, g_out_max);
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}

Mat apply_gamma_correction(Mat source, float gamma){

    // TODO: apply gamma correction to the image

    Mat result;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    result = source.clone();
    for(int i = 0; i < source.rows; i++) {
        for(int j = 0; j < source.cols; j++) {
            float normalized = (float)source.at<uchar>(i, j) / 255.0;
            float corrected = pow(normalized, gamma);
            result.at<uchar>(i, j) = cv::saturate_cast<uchar>(corrected * 255);
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}

Mat apply_histogram_equalization(Mat source, int* histogram){

    // TODO: apply histogram equalization

    Mat result;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    int M = source.rows * source.cols;

    //1 calc cdf
    int* cdf = (int*)calloc(256, sizeof(int));
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    //2 8.11 & 8.12
    uchar tab[256];
    for (int k = 0; k < 256; k++) {
        tab[k] = cv::saturate_cast<uchar>((255.0 * cdf[k]) / M);
    }

    //3 8.14
    result = source.clone();
    for (int i = 0; i < source.rows; i++) {
        for (int j = 0; j < source.cols; j++) {
            int g_in = source.at<uchar>(i, j);
            result.at<uchar>(i, j) = tab[g_in];
        }
    }


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}
