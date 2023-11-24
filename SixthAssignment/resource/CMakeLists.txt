cmake_minimum_required(VERSION 3.24)
project(SerialPortIO)

find_package(Boost COMPONENTS system REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
#find_package(OpenCV REQUIRED)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
set(PUBLIC_PTHREAD PUBLIC pthread)
endif()

aux_source_directory(Sources sc_program_source)
add_executable(${PROJECT_NAME} ${sc_program_source})
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE Includes)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME} ${PUBLIC_PTHREAD} PRIVATE Boost::system PRIVATE spdlog::spdlog PRIVATE fmt::fmt)

aux_source_directory(Testers sc_sources)
foreach (file ${sc_sources})
	get_filename_component(file_name ${file} NAME_WE)
	add_executable(${file_name} ${file})
	set_target_properties(${file_name} PROPERTIES CXX_STANDARD 20)
endforeach()
