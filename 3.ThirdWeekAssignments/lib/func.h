#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <opencv2/viz.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

void rotateMat(double alpha,double beta,double gamma);

cv::Mat undistort(cv::Mat &originalImage,double k1,double k2,double p1,double p2,double fx,double fy,double cx,double cy);



#endif