#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>

void triangulatePoints(const cv::Mat& K, 
                       const cv::Mat& R, 
                       const cv::Mat& t, 
                       const std::vector<cv::Point2f>& points1, 
                       const std::vector<cv::Point2f>& points2, 
                       std::vector<cv::Point3f>& points3D) {
    // Projection matrices
    cv::Mat P1 = K * cv::Mat::eye(3, 4, CV_64F); // [I | 0]
    cv::Mat P2 = K * (cv::Mat_<double>(3, 4) << 
                       R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2), t.at<double>(0),
                       R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2), t.at<double>(1),
                       R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2), t.at<double>(2));

    // Convert points to homogeneous coordinates
    cv::Mat points4D;
    cv::triangulatePoints(P1, P2, points1, points2, points4D);

    // Convert from homogeneous to 3D points
    for (int i = 0; i < points4D.cols; i++) {
        cv::Mat point = points4D.col(i);
        point /= point.at<float>(3); // Normalize by w to get the actual 3D point

        // Check for valid points (no NaN, Inf or zero)
        if (std::isfinite(point.at<float>(0)) && std::isfinite(point.at<float>(1)) && std::isfinite(point.at<float>(2))) {
            points3D.push_back(cv::Point3f(point.at<float>(0), point.at<float>(1), point.at<float>(2)));
        }
    }
}