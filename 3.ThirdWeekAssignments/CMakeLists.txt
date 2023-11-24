cmake_minimum_required(VERSION 3.20)

project(Third)

add_compile_options(-std=c++17 -O2)

#set(OPENCV_DIR /opt/homebrew/opt/opencv@4) # for macos
include_directories(/opt/homebrew/Cellar/opencv@3/3.4.16_10/include)
include_directories(/opt/homebrew/Cellar/eigen/3.4.0_1/include)
# include_directories(/opt/homebrew/Cellar/vtk/9.2.6_5/include/)
find_package(OpenCV REQUIRED)
# include_directories( "/usr/include/opencv4")
include_directories( "/usr/include/eigen3" )

aux_source_directory(src SOURCE_FILES)

add_executable(main ${SOURCE_FILES})

#target_link_libraries(main ${OpenCV_LIBS})
