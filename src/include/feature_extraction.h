#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

void extractORBFeatures(const cv::Mat &img, std::vector<cv::KeyPoint> &keypoints,
                        cv::Mat &descriptors, const std::string &output_filename);