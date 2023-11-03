#include<opencv2/opencv.hpp>
#include<iostream>
#include"../lib/func.h"

using namespace std;
using namespace cv;

signed main()
{

    // Mat BGRImage = imread("../img/3.png");
    Mat BGRImage = imread("../img/2.jpeg");

    if(BGRImage.empty())
    {
        cerr << "[ERROR] Can\'t open the image!" << endl;
        return -1;
    }

    // 第三题
    /*    
    vector<Mat> Licence = getCarLicense(BGRImage);

    for(auto img :Licence)
    {
        imshow("123",img);
        waitKey(0);
        destroyAllWindows();
    }*/

    //第二题
    /*   
    Mat OutputImage;

    ResizeScale(BGRImage,OutputImage,0.2);

    imshow("Bigger",OutputImage);
*/

    //第一题
    /*    
    Mat HSVImage = Mat::zeros(BGRImage.rows,BGRImage.cols,CV_32FC3);
    Mat GREAYImage = Mat::zeros(BGRImage.rows,BGRImage.cols,CV_8UC1);
    imshow("original",BGRImage);

    cvtColor(BGRImage,HSVImage,COLOR_BGR2HSV);
    cvtColor(HSVImage,BGRImage,COLOR_HSV2BGR);

    bgr2hsv(BGRImage,HSVImage);
    bgr2gray(BGRImage,GREAYImage);
    imshow("HSV",HSVImage);
    imshow("gray",GREAYImage);
    imshow("BGR",BGRImage);
    */

    return 0;
}