#include <opencv2/opencv.hpp>

void estimatePose(const std::vector<cv::KeyPoint> &keypoints1,
                  const std::vector<cv::KeyPoint> &keypoints2,
                  const std::vector<cv::DMatch> &matches,
                  const cv::Mat &K,
                  cv::Mat &R, cv::Mat &t) {
    std::vector<cv::Point2f> points1, points2;
    for (const auto &match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }

    // Compute the Essential matrix
    cv::Mat E = cv::findEssentialMat(points1, points2, K, cv::RANSAC, 0.999, 1.0);
std::cout << E <<std::endl;
    // Recover pose
    cv::recoverPose(E, points1, points2, K, R, t);
}