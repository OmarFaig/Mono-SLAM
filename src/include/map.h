#include <opencv2/opencv.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

void build2DMap(const std::vector<cv::KeyPoint> &keypoints,
                const cv::Mat &img);
void build3DMap(const std::vector<cv::Point3f>& points);