cmake_minimum_required(VERSION 3.0)
project(KalmanFilter)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 17)

add_executable(KalmanFilter main.cpp)
target_link_libraries(KalmanFilter
        ${EIGEN3_LIBRARIES}
        ${OpenCV_LIBRARIES}
)