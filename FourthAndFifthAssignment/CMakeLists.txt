cmake_minimum_required(VERSION 3.2.0)

project(Fourth)


include_directories(./lib/)

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(
        ${EIGEN3_INCLUDE_DIR}
        ${OpenCV_INCLUDE_DIRS}
)

aux_source_directory(src SOURCE_FILES)
aux_source_directory(lib LIB_FILES)

add_executable(main ${SOURCE_FILES} ${LIB_FILES}
        lib/ArchKalman.hpp
        lib/ArchLowFilter.hpp)

target_link_libraries(main
        ${EIGEN3_LIBRARIES}
        ${OpenCV_LIBRARIES}
)