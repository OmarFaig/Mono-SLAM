#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <string>

void extractORBFeatures(const cv::Mat &img, std::vector<cv::KeyPoint> &keypoints,
                        cv::Mat &descriptors, const std::string &output_filename)
{
    cv::Ptr<cv::ORB> orb = cv::ORB::create();
    orb->detectAndCompute(img, cv::noArray(), keypoints, descriptors);

    // Visualize keypoints
    cv::Mat keypointImage;
    cv::drawKeypoints(img, keypoints, keypointImage, cv::Scalar(0, 255, 0), cv::DrawMatchesFlags::DEFAULT);

    // Save the image with keypoints
    cv::imwrite(output_filename, keypointImage);
}
