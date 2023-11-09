cmake_minimum_required(VERSION 3.2.0)

project(Fourth)

aux_source_directory(src SOURCE_FILES)

add_executable(main ${SOURCE_FILES})