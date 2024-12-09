#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

void matchFeatures(const cv::Mat &descriptors1, const cv::Mat &descriptors2,
                   const std::vector<cv::KeyPoint> &keypoints1,
                   const std::vector<cv::KeyPoint> &keypoints2,
                   std::vector<cv::DMatch> &matches,
                   const cv::Mat &img1, const cv::Mat &img2, const std::string &output_filename);
