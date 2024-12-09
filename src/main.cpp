#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include "include/feature_extraction.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    for (int i = 0; i <= 49; i++) {
        // Format the file names
        std::string img1_path = "/home/omar/TUM/05_projects/Mono-SLAM/data/input/" + 
                                (i < 10 ? "00000" + std::to_string(i) : "0000" + std::to_string(i)) + ".png";

        // Load the image
        cv::Mat img1 = cv::imread(img1_path, cv::IMREAD_GRAYSCALE);

        // Check if the image is successfully loaded
        if (img1.empty()) {
            std::cerr << "Error: Could not load image " << img1_path << std::endl;
            continue; // Skip this iteration
        }

        // Generate the output filename
        std::string output_path = "/home/omar/TUM/05_projects/Mono-SLAM/data/output/" + 
                                  (i < 10 ? "00000" + std::to_string(i) : "0000" + std::to_string(i)) + "_features.png";

        // Feature extraction
        std::vector<cv::KeyPoint> keypoints1;
        cv::Mat descriptors1;
        extractORBFeatures(img1, keypoints1, descriptors1, output_path);
    }

    std::cout << "Feature extraction completed!" << std::endl;
    return 0;
}

