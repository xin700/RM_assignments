#ifndef FUNC_H
#define FUNC_H

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void bgr2hsv(Mat &InputImage,Mat &OutputImage);
bool equal(float a,float b);

#endif