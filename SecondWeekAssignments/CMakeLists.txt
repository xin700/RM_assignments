cmake_minimum_required(VERSION 3.20)

project(test)

set(OPENCV_DIR /opt/homebrew/opt/opencv@4) # for macos

find_package(OpenCV REQUIRED)

aux_source_directory(src SOURCE_FILES)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main ${OpenCV_LIBS})