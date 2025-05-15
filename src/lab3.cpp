#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab3.h"

using namespace std;
using namespace cv;


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

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****
    return false;

}

int* compute_histogram_naive(Mat source){

    /*
    * Compute  the  histogram  for  a  given  grayscale  image (in  an  array  of  integers  having dimension 256)
    */

    int rows = source.rows;
    int cols = source.cols;
    int* histogram = (int*)calloc(256, sizeof(int));


    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            histogram[source.at<uchar>(i, j)]++;
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return histogram;

}

int* compute_histogram_custom(Mat source, int histogram_bins){

    /*
     * Compute the histogram for a given number of bins m≤ 256.
     */

    int rows = source.rows;
    int cols = source.cols;
    int* histogram = (int*)calloc(histogram_bins, sizeof(int));

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    int bin_size = 256 / histogram_bins;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int bin_index = source.at<uchar>(i, j) / bin_size;
            histogram[bin_index]++;
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return histogram;

}

float* compute_pdf(int* histogram, Mat source){
    /*
     *Compute the PDF (in an array of floats of dimension 256)
     */

    int rows = source.rows;
    int cols = source.cols;
    int no_grayscale_values = 256;
    float* pdf = (float*)calloc(no_grayscale_values, sizeof(float));

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    int total_pixels = rows * cols;
    for(int i = 0; i < 256; i++){
        pdf[i] = (float)histogram[i] / total_pixels;
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return pdf;

}

void showHistogram(const string& name, int* hist, const int  hist_cols, const int hist_height){


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
        line(imgHist, p1, p2, CV_RGB(255, 0, 255));
    }
    imshow(name, imgHist);

}

grayscale_mapping multi_level_thresholding(int wh, float th, float* pdf){
    /*
     * Implement the multilevel thresholding algorithm from section 3.3.
     * Return a grayscale_mapping structure:
     *        grayscale_values: an array padded with 0 and 255 and containing the grayscale values obtained after
     *                          applying the algorithm
     *        count_grayscale_values: the number of new grayscale values, don't forgot 0 and 255(size of grayscale_values)
     *
     */

    grayscale_mapping map;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    vector<uchar> max_val;

    for (int k = wh; k <= 255 - wh; ++k) {
        float medie_v = 0.0f;
        for (int j = k - wh; j <= k + wh; ++j) {
            medie_v += pdf[j];
        }
        medie_v /= (2 * wh + 1);

        if (pdf[k] > medie_v + th) {
            bool is_max = true;
            for (int j = k - wh; j <= k + wh; ++j) {
                if (pdf[k] < pdf[j]) {
                    is_max = false;
                    break;
                }
            }
            if (is_max) max_val.push_back((uchar)k);
        }
    }

    max_val.insert(max_val.begin(), 0);
    max_val.push_back(255);


    map.count_grayscale_values = (uchar)max_val.size();
    map.grayscale_values = new uchar[map.count_grayscale_values];

    for (int i = 0; i < map.count_grayscale_values; ++i) {
        map.grayscale_values[i] = max_val[i];

    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return map;

}

uchar find_closest_histogram_maximum(uchar old_pixel, grayscale_mapping gray_map){

    /*
     * Find the corresponding quantized value to map a pixel
     * Hint: Look in the gray_map and find out the value that resides at index argmin of the distance between old_pixel
     *      and the values in gray_map
     */

    uchar new_grayscale_value;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    new_grayscale_value = gray_map.grayscale_values[0];
    int min_dist = abs(old_pixel - new_grayscale_value);

    for(int i = 1; i < gray_map.count_grayscale_values; i++){
        int dist = abs(old_pixel - gray_map.grayscale_values[i]);
        if(dist < min_dist){
            min_dist = dist;
            new_grayscale_value = gray_map.grayscale_values[i];
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return new_grayscale_value;
}

Mat draw_multi_thresholding(Mat source, grayscale_mapping grayscale_map){

    /*
     * Draw the new multi level threshold image by mapping each pixel to the corresponding quantized values
     * Hint: Look in the grayscale_map structure for all the obtained grayscale values and for each pixel in the
     *      source image assign the correct value. You may use the find_closest_histogram_maximum function
     */

    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    result = source.clone();
    for(int i = 0; i < source.rows; i++){
        for(int j = 0; j < source.cols; j++){
            result.at<uchar>(i, j) = find_closest_histogram_maximum(source.at<uchar>(i, j), grayscale_map);
        }
    }
    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****


    return result;
}

uchar update_pixel_floyd_steinberg_dithering(uchar pixel_value, int value){
    /*
     * Update the value of a pixel in the floyd_steinberg alg.
     * Take care of the values bellow 0 or above 255. Clamp them.
     */

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****


    int new_value = pixel_value + value;
    return (uchar)max(0, min(255, new_value));


    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

}

Mat floyd_steinberg_dithering(Mat source, grayscale_mapping grayscale_map){

    /*
     * Enhance  the  multilevel  thresholding  algorithm  using  the  Floyd-Steinberg  dithering from section 3.4.
     * Hint: Use the update_pixel_floyd_steinberg_dithering when spreading the error
     */

    int rows, cols;
    Mat result;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = source.rows;
    cols = source.cols;
    result = source.clone();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            const uchar old_pixel = result.at<uchar>(i, j);
            const uchar new_pixel = find_closest_histogram_maximum(old_pixel, grayscale_map);
            result.at<uchar>(i, j) = new_pixel;
            const int error = old_pixel - new_pixel;
            if(IsInside(source, i, j+1)) result.at<uchar>(i, j+1) = update_pixel_floyd_steinberg_dithering(result.at<uchar>(i, j+1), error * 7 / 16);
            if(IsInside(source, i+1, j-1)) result.at<uchar>(i+1, j-1) = update_pixel_floyd_steinberg_dithering(result.at<uchar>(i+1, j-1), error * 3 / 16);
            if(IsInside(source, i+1, j)) result.at<uchar>(i+1, j) = update_pixel_floyd_steinberg_dithering(result.at<uchar>(i+1, j), error * 5 / 16);
            if(IsInside(source, i+1, j+1)) result.at<uchar>(i+1, j+1) = update_pixel_floyd_steinberg_dithering(result.at<uchar>(i+1, j+1), error / 16);
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;
}