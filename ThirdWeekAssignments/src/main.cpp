#include "../lib/func.h"
using namespace std;

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
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    // 内参
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;
    cv::Mat InputImage = cv::imread("../img/distorted.png");

    if(InputImage.empty())
    {
        cout << "[ERROR]failed to open the image"<< endl;
        return -1;
    }
    cv::Mat OutputImage = undistort(InputImage,k1,k2,p1,p2,fx,fy,cx,cy);

    cv::imshow("inputImage",InputImage);
    cv::imshow("outputImage",OutputImage);
    cv::waitKey(0);

    return 0;
}
