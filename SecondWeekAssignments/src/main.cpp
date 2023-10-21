#include<opencv2/opencv.hpp>
#include<iostream>
#include"../lib/func.h"

using namespace std;
using namespace cv;

// float max(float a,float b,float c);
// float min(float a,float b,float c);

signed main()
{
    Mat BGRImage = imread("../img/test.jpg");

    Mat HSVImage = Mat::zeros(BGRImage.rows,BGRImage.cols,CV_32FC3);
    // imshow("original",BGRImage);

    // cvtColor(BGRImage,HSVImage,COLOR_BGR2HSV);

    // cvtColor(HSVImage,BGRImage,COLOR_HSV2BGR);

    bgr2hsv(BGRImage,HSVImage);
    imshow("HSV",HSVImage);
    // imshow("BGR",BGRImage);
    waitKey(0);
    
    return 0;
}