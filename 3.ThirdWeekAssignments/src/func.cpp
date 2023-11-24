#include "../lib/func.h"
using namespace Eigen;
using namespace cv;
using namespace std;

void rotateMat(double alpha,double beta,double gamma)
{
    Matrix3d Rz, Ry, Rx;
    Rz << cos(gamma), -sin(gamma), 0,
          sin(gamma), cos(gamma), 0,
          0, 0, 1;
    Ry << cos(beta), 0, sin(beta),
          0, 1, 0,
         -sin(beta), 0, cos(beta);
    Rx << 1, 0, 0,
          0, cos(alpha), -sin(alpha),
          0, sin(alpha), cos(alpha);

    Matrix3d R = Rz * Ry * Rx;

    cv::Affine3d pose;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pose.rotation()(i, j) = R(i, j);
        }
    }

    viz::Viz3d window("Coordinate System");
    viz::WCoordinateSystem coord(0.5);
    coord.setPose(pose);
    window.showWidget("base", coord);

    window.spin();

}

cv::Mat undistort(Mat &originalImage,double k1,double k2,double p1,double p2,double fx,double fy,double cx,double cy)
{

    cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
    cv::Mat distCoeffs = (cv::Mat_<double>(5,1) << k1, k2, p1, p2, 0);


    cv::Mat undistortedImage;
    cv::undistort(originalImage, undistortedImage, cameraMatrix, distCoeffs);

    return undistortedImage;

}