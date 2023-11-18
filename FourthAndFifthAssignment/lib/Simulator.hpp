//
// Created by MicDZ on 2023/11/4.
//

#ifndef KALMANFILTER_SIMULATOR_HPP
#define KALMANFILTER_SIMULATOR_HPP

#include "Eigen/Dense"
#include <Eigen/Core>
#include <vector>
#include <iostream>

template<typename T, int x>
class Simulator {
private:
// 生成高斯高斯分布噪声，均值为mean，方差为variance
    double gaussianRandom(double mean, double _variance) {
        static double V1, V2, S;
        static int phase = 0;
        double X;

        if (phase == 0) {
            do {
                double U1 = (double) random() / RAND_MAX;
                double U2 = (double) random() / RAND_MAX;

                V1 = 2 * U1 - 1;
                V2 = 2 * U2 - 1;
                S = V1 * V1 + V2 * V2;
            } while (S >= 1 || S == 0);

            X = V1 * sqrt(-2 * log(S) / S);
        } else {
            X = V2 * sqrt(-2 * log(S) / S);
        }

        phase = 1 - phase;

        return X * _variance + mean;
    }

    Eigen::Matrix<T, x, 1> x0;
    double variance;

public:

    // Eigen::Matrix<T, x, 1> velocity;

    Eigen::Matrix<T, x, 1> getMeasurement(double t = 0) {
        Eigen::Matrix<T, x, 1> theoretical;
        Eigen::Matrix<T, x, 1> measurement;
        Eigen::Matrix<T, x, 1> noise;

        // 若变为匀速模型需要修改此处，请自行设定v和t，theoretical=x0+v*t
        /***************/
        Eigen::Matrix<T, x, 1> v;
        v << 1.0, 2.0;
        theoretical = x0 + v * t;
        /*************/

        noise = Eigen::Matrix<T, x, 1>::Zero();
        for (int i = 0; i < x; i++) {
            noise(i, 0) = gaussianRandom(0, this->variance);
        }
        measurement = theoretical + noise;
        return measurement;
    }

    explicit Simulator(Eigen::Matrix<T, x, 1> x0, double variance,
                       Eigen::Matrix<T, x, 1> velocity = Eigen::Matrix<T, x, 1>::Zero()) {
        this->x0 = x0;
        this->variance = variance;
        //thie->velocity = velocity;
    }
};

#endif //KALMANFILTER_SIMULATOR_HPP
