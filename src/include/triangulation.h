#include <opencv2/opencv.hpp>
#include <vector>

// Function to triangulate points
void triangulatePoints(const cv::Mat& K, 
                       const cv::Mat& R, 
                       const cv::Mat& t, 
                       const std::vector<cv::Point2f>& points1, 
                       const std::vector<cv::Point2f>& points2, 
                       std::vector<cv::Point3f>& points3D);

