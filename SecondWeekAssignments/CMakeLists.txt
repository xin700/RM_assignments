cmake_minimum_required(VERSION 3.0)

project(MAIN)

set(OPENCV_DIR /opt/homebrew/opt/opencv@4) # for macos

find_package(OpenCV REQUIRED)

aux_source_directory(src SOURCE_DIR)

add_executable(main ${SOURCE_DIR})

target_link_libraries(main ${OpenCV_LIBS})