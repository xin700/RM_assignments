#include "../lib/func.h"
using namespace std;
using namespace cv;

int main() {

    // T1
    /*    
    double alpha, beta, gamma;
    cout << "请输入alpha（弧度）: ";
    cin >> alpha;
    cout << "请输入beta（弧度）: ";
    cin >> beta;
    cout << "请输入gamma（弧度）: ";
    cin >> gamma;

    rotateMat(alpha,beta,gamma);
    */

   // T2.2
   /*
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    // 内参
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;
    Mat InputImage = imread("../img/distorted.png");

    if(InputImage.empty())
    {
        cout << "[ERROR]failed to open the image"<< endl;
        return -1;
    }
    Mat OutputImage = undistort(InputImage,k1,k2,p1,p2,fx,fy,cx,cy);

    imshow("inputImage",InputImage);
    imshow("outputImage",OutputImage);
    waitKey(0);
    */

   //T3 pnpSolve
   //fx:1900```,```fy:1900```,```cx:960```,```cy:540
    double fx = 1900,fy = 1900,cx = 960,cy = 540;
    vector<Point3f> objectPoints;
    objectPoints.push_back(Point3f(0, 0, 0));
    objectPoints.push_back(Point3f(0, 125, 0));
    objectPoints.push_back(Point3f(140, 0, 0));
    objectPoints.push_back(Point3f(140, 125, 0));

    vector<Point2f> imagePoints;
    imagePoints.push_back(Point2f(992, 900));
    imagePoints.push_back(Point2f(986, 820));
    imagePoints.push_back(Point2f(1074, 896));
    imagePoints.push_back(Point2f(1064, 813));

    Mat cameraMatrix = (Mat_<double>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);

    Mat distCoeffs = Mat::zeros(5, 1, CV_64F);


    Mat rvec, tvec;
    // cout<<"debug"<<endl;

    solvePnP(objectPoints, imagePoints, cameraMatrix, distCoeffs, rvec, tvec);

    cout << "Rotation Vector (rvec): " << rvec << endl;
    cout << "Translation Vector (tvec): " << tvec << endl;

    return 0;
}
