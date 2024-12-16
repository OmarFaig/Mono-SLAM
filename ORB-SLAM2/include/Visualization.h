#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <pangolin/pangolin.h>
#include <opencv2/opencv.hpp>
#include <vector>

void setupVisualization(int width, int height, const std::vector<cv::Mat>& images);

#endif // VISUALIZATION_H 