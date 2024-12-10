#include <iostream>
#include <fstream> 
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

#include <vector>
#include <filesystem>
#include "include/feature_extraction.h"
#include "include/feature_matching.h"
#include "include/pose_estimation.h"
#include "include/map.h"
#include "include/triangulation.h"

// Function to load images from a folder
std::vector<cv::Mat> loadImagesFromFolder(const std::string& folderPath) {
    std::vector<cv::Mat> images;
    
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        std::string filename = entry.path().string();
        if (filename.find(".png") != std::string::npos || filename.find(".jpg") != std::string::npos) {
            images.push_back(cv::imread(filename, cv::IMREAD_GRAYSCALE)); // Load image in grayscale
        }
    }
    
    return images;
}

// Function to save 3D points to a PCD file
void savePointCloudToPCD(const std::vector<cv::Point3f>& points3D, const std::string& filename) {
    std::ofstream file(filename);
    
    file << "# .PCD v0.7 - Point Cloud Data file format" << std::endl;
    file << "VERSION 0.7" << std::endl;
    file << "FIELDS x y z" << std::endl;
    file << "SIZE 4 4 4" << std::endl;
    file << "TYPE F F F" << std::endl;
    file << "COUNT 1 1 1" << std::endl;
    file << "WIDTH " << points3D.size() << std::endl;
    file << "HEIGHT 1" << std::endl;
    file << "VIEWPOINT 0 0 0 1 0 0 0" << std::endl;
    file << "POINTS " << points3D.size() << std::endl;
    file << "DATA ascii" << std::endl;
    
    // Write the points
    for (const auto& point : points3D) {
        file << point.x << " " << point.y << " " << point.z << std::endl;
    }
    
    file.close();
}

int main() {
    // Intrinsic camera matrix
    cv::Mat K = (cv::Mat_<double>(3, 3) << 517.3, 0, 318.6, 0, 516.5, 255.3, 0, 0, 1);
    
    // Load images from folder
    std::string folderPath = "/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb/";
    std::vector<cv::Mat> images = loadImagesFromFolder(folderPath);
    
    if (images.size() < 2) {
        std::cerr << "Not enough images to process." << std::endl;
        return -1;
    }

    // Feature extraction and matching
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;

    // Vector to accumulate 3D points
    std::vector<cv::Point3f> allPoints3D;

    for (size_t i = 0; i < images.size() - 1; ++i) {
        // Get the current pair of images
        cv::Mat img1 = images[i];
        cv::Mat img2 = images[i + 1];

        // Detect ORB keypoints and compute descriptors
        orb->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
        orb->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);

        // Match keypoints
        cv::BFMatcher matcher(cv::NORM_HAMMING);
        std::vector<cv::DMatch> matches;
        matcher.match(descriptors1, descriptors2, matches);

        // Check if there are enough matches
        if (matches.size() < 5) {
            std::cerr << "Not enough matches for essential matrix estimation." << std::endl;
            continue; // Skip to the next pair
        }

        // Extract matched points
        std::vector<cv::Point2f> points1, points2;
        for (const auto& match : matches) {
            points1.push_back(keypoints1[match.queryIdx].pt);
            points2.push_back(keypoints2[match.trainIdx].pt);
        }

        // Find the essential matrix
        cv::Mat E = cv::findEssentialMat(points1, points2, K, cv::RANSAC, 0.999, 1.0);
        if (E.empty()) {
            std::cerr << "Failed to compute the essential matrix." << std::endl;
            continue; // Skip to the next pair
        }

        // Recover pose
        cv::Mat R, t;
        int inliers = cv::recoverPose(E, points1, points2, K, R, t);
        std::cout << "Pose recovered with " << inliers << " inliers." << std::endl;

        // Triangulate points
        std::vector<cv::Point3f> points3D;
        triangulatePoints(K, R, t, points1, points2, points3D);

        // Accumulate 3D points
        allPoints3D.insert(allPoints3D.end(), points3D.begin(), points3D.end());
 
        std::cout << "Processed image pair " << i << " and " << i + 1 << std::endl;
    }

    // Save the accumulated 3D points to a PCD file
    savePointCloudToPCD(allPoints3D, "3D_map.pcd");
  //pcl::visualization::PCLVisualizer viewer("3D Viewer");
  // viewer.addPointCloud(allPoints3D, "cloud");
  // viewer.spin();
    std::cout << "Saved 3D map with " << allPoints3D.size() << " points." << std::endl;

    return 0;
}
