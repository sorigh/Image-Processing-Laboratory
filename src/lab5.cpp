#include <iostream>
#include <opencv2/opencv.hpp>
#include "lab5.h"

using namespace std;
using namespace cv;



Mat color_labels(labels labels_str){

    /*
     * This method will generate a number of no_labels colors and
     * generate a color image containing each label displayed in a different color
     */

    int rows, cols, no_labels;
    Mat labels;
    Vec3b* colors;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    labels = labels_str.labels;
    no_labels = labels_str.no_labels;
    rows = labels.rows;
    cols = labels.cols;


    if (labels.empty()) return Mat();


    Mat result(labels.size(), CV_8UC3, Scalar(255, 255, 255));

    colors = new Vec3b[no_labels + 1];

    srand(time(NULL));
    for (int i = 1; i <= no_labels; i++) {
        colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int label = labels.at<int>(r, c);
            if (label > 0) {
                result.at<Vec3b>(r, c) = colors[label];
            }
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return result;

}

labels BFS_labeling(Mat source){

    /*
     * This method will implement the BFS labeling algorithm
     * Hint:
     *  Use the Point structure(or a similar one) to store the coordinates in a queue
     *  You can use queue from C++ with its specific actions (push, pop, empty, front)
     */
    Mat labels;
    int rows, cols, no_labels;

    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****
    rows = source.rows;
    cols = source.cols;
    labels = Mat::zeros(rows, cols, CV_32SC1);
    no_labels = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (source.at<uchar>(r, c) == 0 && labels.at<int>(r, c) == 0) {
                no_labels++;
                queue<Point> q;
                q.push(Point(c, r));
                labels.at<int>(r, c) = no_labels;

                while (!q.empty()) {
                    Point p = q.front();
                    q.pop();

                    for (int i = 0; i < 8; i++) {
                        int newX = p.x + n8_dj[i];
                        int newY = p.y + n8_di[i];

                        if (newX >= 0 && newX < cols && newY >= 0 &&
                            newY < rows && source.at<uchar>(newY, newX) == 0 && labels.at<int>(newY, newX) == 0) {
                            labels.at<int>(newY, newX) = no_labels;
                            q.push(Point(newX, newY));
                            }
                    }
                }
            }
        }
    }

    //*****END OF YOUR CODE(DO NOT DELETE / MODIFY THIS LINE) *****

    return {labels, no_labels};
}

labels Two_pass_labeling(Mat source){
    Mat labels;
    int rows, cols, no_newlabels;

    /*
     * This method will implement the two pass labeling algorithm
     * Hint:
     *  Use the vector structure from C++(actually you need a vector of vectors and a simple one check out the lab works)
     *  You can use queue from C++ with its specific actions (push, pop, empty, front)
     */

    rows = source.rows;
    cols = source.cols;
    //*****START OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    labels = Mat::zeros(rows, cols, CV_32SC1);
    no_newlabels = 0;

    vector<vector<int>> edges(1000); //comp conexe

    // first pass
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (source.at<uchar>(r, c) == 0 && labels.at<int>(r, c) == 0) {
                vector<int> neighbours;

                // check neighbours
                for (int k = 0; k < 4; k++) {
                    int nr = r + np_di[k];
                    int nc = c + np_dj[k];

                    if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && labels.at<int>(nr, nc) > 0) {
                        neighbours.push_back(labels.at<int>(nr, nc));
                    }
                }

                if (neighbours.empty()) {
                    //new label
                    no_newlabels++;
                    labels.at<int>(r, c) = no_newlabels;
                } else {
                    int minLabel = *min_element(neighbours.begin(), neighbours.end());
                    labels.at<int>(r, c) = minLabel;

                    // merge
                    for (int lbl : neighbours) {
                        if (lbl != minLabel) {
                            edges[minLabel].push_back(lbl);
                            edges[lbl].push_back(minLabel);
                        }
                    }
                }
            }
        }
    }

    // second pass
    vector<int> finalLabels(no_newlabels + 1, 0);
    int newlabel = 0;
    queue<int> Q;

    for (int i = 1; i <= no_newlabels; i++) {
        if (finalLabels[i] == 0) {
            newlabel++;
            finalLabels[i] = newlabel;
            Q.push(i);

            while (!Q.empty()) {
                int currentLabel = Q.front();
                Q.pop();

                for (int neighbour : edges[currentLabel]) {
                    if (finalLabels[neighbour] == 0) {
                        finalLabels[neighbour] = newlabel;
                        Q.push(neighbour);
                    }
                }
            }
        }
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (labels.at<int>(r, c) > 0) {
                labels.at<int>(r, c) = finalLabels[labels.at<int>(r, c)];
            }
        }
    }

    //*****END OF YOUR CODE (DO NOT DELETE/MODIFY THIS LINE)*****

    return {labels, no_newlabels};
}
