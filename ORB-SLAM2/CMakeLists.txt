cmake_minimum_required(VERSION 3.22.1)
project(ORBSLAM2)
set(CMAKE_CXX_STANDARD 17)

find_package(Pangolin REQUIRED)
find_package(OpenCV REQUIRED)
#find_package(PCL REQUIRED)

message( STATUS "Found Pangolin version ${Pangolin_VERSION}" )
message( STATUS "Found OpenCV version ${OpenCV_VERSION}" )
include_directories(${OpenCV_INCLUDE_DIRS} )
add_executable(run src/main.cpp )
target_link_libraries(run ${OpenCV_LIBS} )