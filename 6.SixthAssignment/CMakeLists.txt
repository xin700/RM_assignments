cmake_minimum_required(VERSION 3.22.0)

project(SerialPort)

add_compile_options(-std=c++17 -Ofast)

#find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
aux_source_directory(src SOURCE_FILES)

add_executable(main ${SOURCE_FILES})

target_include_directories(main BEFORE PUBLIC include)

target_link_libraries(main Boost::system pthread)