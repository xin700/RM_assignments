#include <opencv2/opencv.hpp>
#include <iostream>
#include "../lib/KalmanFilter.hpp"
#include "../lib/Simulator.hpp"
#include "../lib/ArchKalman.hpp"
#include "../lib/ArchLowFilter.hpp"

//using namespace cv;
using namespace std;
//using namespace Eigen;

namespace MAIN {
    inline signed main(){
        return 0;
    }
}
namespace TEST{
    inline signed main(){
        return 0;
    }
}

//下面这个是真正的主函数，每个任务的代码都封装成了一个namespace，直接调用这个namespace的main就行运行
signed main() { return LowFilter::main(); }