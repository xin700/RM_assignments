//
// Created by xin on 2023/11/18.
//
namespace LowFilter {


    inline signed main(){
        Simulator<double, 2> *simulator;
        simulator = new Simulator<double, 2>(Eigen::Vector2d(0, 0), 5);

        int time = 0;
        int preX = 0,nowX = 0;
        cv::Mat backGround(cv::Size(1000,200),CV_8UC3,cv::Scalar(0,0,0));
        while(true){
            Eigen::Vector2d measurement = simulator ->getMeasurement(time ++);
            measurement(1,0) = 0; //强制变成一维，我真是个天才
            nowX = measurement(0,0); //作为测量值

            int predicX = 0.1 * nowX + 0.9 * preX;

            cv::circle(backGround, cv::Point((int)(measurement[0]), int(measurement[1]) + 100), 5, cv::Scalar(0, 0, 255), -1);
            cv::circle(backGround, cv::Point((int)(predicX ), 100), 5, cv::Scalar(0, 255, 0), -1);

            preX = nowX;

            imshow("background",backGround);
            char input = cv::waitKey(2);
            if(input == 'q') break;

        }

        return 0;
    }
}