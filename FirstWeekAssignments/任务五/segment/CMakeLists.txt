cmake_minimum_required(VERSION 2.8)
project(segmention)
set(CMAKE_CXX_STANDARD 11)

set(OPENCV_DIR /opt/homebrew/opt/opencv@4)
# 在 macos 下设置，并且在 arm 的 macos 下需要 -DCMAKE_SYSTEM_PROCESSOR=arm64 -DCMAKE_OSX_ARCHITECTURES=arm64
# linux下使用默认 OPENCV_DIR 即可
find_package(OpenCV REQUIRED)
include_directories(./include)

# aux_source_directory(src SOURCE_FILES)
set(SOURCE_FILES src/main.cpp src/segment.cpp )

add_executable(main ${SOURCE_FILES})

target_link_libraries(main ${OpenCV_LIBS})