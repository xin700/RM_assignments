//
// Created by xin on 2023/11/18.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include "KalmanFilter.hpp"
#include "Simulator.hpp"

//using namespace cv;
using namespace std;
//using namespace Eigen;

namespace Kalman2 {
    inline signed main() {
        srand(114514);

        KalmanFilter<double, 2, 2> *kf;
        kf = new KalmanFilter<double, 2, 2>();
        Simulator<double, 2> *simulator;
        simulator = new Simulator<double, 2>(Eigen::Vector2d(0, 0), 5);

        kf->transition_matrix << 1, 0,
                0, 1;
        kf->measurement_matrix << 1, 0,
                0, 1;
        kf->process_noise_cov << 0.01, 0,
                0, 0.01;
        kf->measurement_noise_cov << 5, 0,
                0, 5;
        kf->control_vector << 0,
                0;


        //修改simulator中的v为(2,1)向量，增加速度变量
        int time = 0;
        cv::Mat backGround(cv::Size(1000,2000),CV_8UC3,cv::Scalar(0,0,0));
        while (true) {
            Eigen::Vector2d measurement = simulator->getMeasurement(time++);
            kf->predict(measurement);
            kf->update();
            Eigen::Vector2d estimate = kf->posteriori_state_estimate;
            cv::circle(backGround, cv::Point((int)(measurement[0] ), int(measurement[1] )), 5, cv::Scalar(0, 0, 255), -1);
            cv::circle(backGround, cv::Point((int)(estimate[0] ), (int)(estimate[1] )), 5, cv::Scalar(0, 255, 0), -1);

            cv::imshow("backGround", backGround);
//            cout << measurement << endl << endl;
            char input = cv::waitKey(10);
            if(input == 'q') break;
        }
        return 0;
    }
}
namespace Kalman1 {

    inline signed main() {
        srand(114514);

        KalmanFilter<double, 2, 2> *kf;
        kf = new KalmanFilter<double, 2, 2>();
        Simulator<double, 2> *simulator;
        simulator = new Simulator<double, 2>(Eigen::Vector2d(0, 0), 5);

        kf->transition_matrix << 1, 0,
                0, 1;
        kf->measurement_matrix << 1, 0,
                0, 1;
        kf->process_noise_cov << 0.01, 0,
                0, 0.01;
        kf->measurement_noise_cov << 5, 0,
                0, 5;
        kf->control_vector << 0,
                0;


        //修改simulator中的v为(2,1)向量，增加速度变量
        int time = 0;
        cv::Mat backGround(cv::Size(1000,2000),CV_8UC3,cv::Scalar(0,0,0));
        while (true) {
            Eigen::Vector2d measurement = simulator->getMeasurement(time++);
            measurement(1,0) = 0;
            kf->predict(measurement);
            kf->update();
            Eigen::Vector2d estimate = kf->posteriori_state_estimate;
            cv::circle(backGround, cv::Point((int)(measurement[0]), int(measurement[1] + 1000)), 5, cv::Scalar(0, 0, 255), -1);
            cv::circle(backGround, cv::Point((int)(estimate[0]), (int)(estimate[1] + 1000)), 5, cv::Scalar(0, 255, 0), -1);

            cv::imshow("backGround", backGround);
//            cout << measurement << endl << endl;
            char input = cv::waitKey(10);
            if(input == 'q') break;
        }
        return 0;
    }
}
