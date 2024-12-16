#include <iostream>
#include <fstream>
#include <pangolin/pangolin.h>
#include <opencv2/opencv.hpp>
#include "Visualization.h"
#include <vector>
#include <string>

std::vector<cv::Mat> load_images(const std::string& pathToImages, 
                                const std::string& pathToCalibration,
                                const std::string& timestampsPath)
{
    std::vector<cv::Mat> images;
    std::ifstream times(timestampsPath);
    
    if (!times.is_open()) {
        std::cerr << "Failed to open timestamps file" << std::endl;
        return images;
    }

    std::string line;
    while (std::getline(times, line)) {
        if (line.empty()) continue;
        
        // Construct image path - assuming timestamps contain filename or timestamp
        std::string imagePath = pathToImages + "/" + line + ".png";  // Adjust extension if needed
        
        cv::Mat image = cv::imread(imagePath);
        if (image.empty()) {
            std::cerr << "Failed to load image: " << imagePath << std::endl;
            continue;
        }
        
        images.push_back(image);
    }
    
    return images;
}

int main(int argc, char **argv)
{
    std::cout << "Starting ORB-SLAM2..." << std::endl;
    
    // Load images first
    std::vector<cv::Mat> images = load_images(
        "/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb",
        "/home/omar/TUM/05_projects/Mono-SLAM/ORB-SLAM2/data/rgbd_dataset_freiburg1_desk/rgb.txt",
        "/home/omar/TUM/Robust-Odometry-Estimation-for-RGB-D-Cameras-/Data/rgbd_dataset_freiburg1_xyz/rgb_timestampts.txt"
    );
    
    // Start visualization with the loaded images
    setupVisualization(1024, 768, images);
    
    return 0;
}
