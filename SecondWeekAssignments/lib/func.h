#ifndef FUNC_H
#define FUNC_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace cv;
using namespace std;
void bgr2hsv (Mat &InputImage,Mat &OutputImage);
void bgr2gray(Mat &InputImage,Mat &OutputImage);
void ResizeScale(Mat &InputImage,Mat &OutputImage,double scale);
vector<Mat> getCarLicense(Mat &InputImage);
bool equal(float a,float b);

#endif