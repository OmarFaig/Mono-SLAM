cmake_minimum_required(VERSION 3.22.1)
project(MonoSLAM)
set(CMAKE_CXX_STANDARD 17)

find_package(Pangolin REQUIRED)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)

message( STATUS "Found Pangolin version ${Pangolin_VERSION}" )
message( STATUS "Found OpenCV version ${OpenCV_VERSION}" )
include_directories(${OpenCV_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} )
add_executable(run src/main.cpp src/feature_extraction.cpp src/feature_matching.cpp src/pose_estimation.cpp src/map.cpp src/triangulation.cpp)
target_link_libraries(run ${OpenCV_LIBS} ${PCL_LIBRARIES})