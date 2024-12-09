#include <opencv2/opencv.hpp>

void estimatePose(const std::vector<cv::KeyPoint> &keypoints1,
                  const std::vector<cv::KeyPoint> &keypoints2,
                  const std::vector<cv::DMatch> &matches,
                  const cv::Mat &K,
                  cv::Mat &R, cv::Mat &t);