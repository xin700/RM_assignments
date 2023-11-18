#include <iostream>
#include <opencv2/opencv.hpp>
#include "KalmanFilter.hpp"
#include "Simulator.hpp"

using namespace std;

int main() {
    srand(114514);
    // 以一个静止滤波为例展示使用方法
    // 1. 初始化
    // 滤波器初始化
    KalmanFilter<double, 2, 2> *kf;
    kf = new KalmanFilter<double, 2, 2>();
    // 仿真器初始化
    Simulator<double, 2> *simulator;
    simulator = new Simulator<double, 2>(Eigen::Vector2d(0, 0), 5); // 输入为起始点与方差

    // 2. 设置状态转移矩阵
    kf->transition_matrix << 1, 0,
            0, 1;
    // 3. 设置测量矩阵
    kf->measurement_matrix << 1, 0,
            0, 1;
    // 4. 设置过程噪声协方差矩阵
    kf->process_noise_cov << 0.01, 0,
            0, 0.01;
    // 5. 设置测量噪声协方差矩阵
    kf->measurement_noise_cov << 5, 0,
            0, 5;
    // 6. 设置控制向量
    kf->control_vector << 0,
            0;

    // 生成随机点
    Eigen::Vector2d measurement;
    cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
    int time = 0;
    while (1) {
        measurement = simulator->getMeasurement();
        // 7. 预测
        kf->predict(measurement);
        // 8. 更新
        kf->update();
        // 9. 获取后验估计
        Eigen::Vector2d estimate = kf->posteriori_state_estimate;
        // 10. 绘制出观测点和滤波点（平移到绘图中心），亦可采用其他可视化方法（matplotlib、VOFA+、Foxglove均可）
        cv::circle(img, cv::Point((int)(measurement[0] * 10 + 250), int(measurement[1] * 10 + 250)), 2, cv::Scalar(0, 0, 255), -1);
        cv::circle(img, cv::Point((int)(estimate[0] * 10 + 250), (int)(estimate[1] * 10 + 250)), 2, cv::Scalar(0, 255, 0), -1);

        cv::imshow("img", img);
        cv::waitKey(10);
    }

    return 0;
}
