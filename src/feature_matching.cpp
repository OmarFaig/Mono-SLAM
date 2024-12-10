#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

void matchFeatures(const cv::Mat &descriptors1, const cv::Mat &descriptors2,
                   const std::vector<cv::KeyPoint> &keypoints1,
                   const std::vector<cv::KeyPoint> &keypoints2,
                   std::vector<cv::DMatch> &matches,
                   const cv::Mat &img1, const cv::Mat &img2 ,const std::string &output_filename)
{
    cv::BFMatcher matcher(cv::NORM_HAMMING, true);
    matcher.match(descriptors1, descriptors2, matches);

    // Sort matches by distance
    std::sort(matches.begin(), matches.end(),
              [](const cv::DMatch &a, const cv::DMatch &b)
              { return a.distance < b.distance; });

   // cv::Mat imgMatches;
    //cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, imgMatches, cv::Scalar(0, 255, 0),
                   // cv::Scalar(255, 0, 0), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    // Save the image with matches
    //cv::imwrite(output_filename, imgMatches);

   // cv::imshow("Feature Mathces", imgMatches);
   // cv::waitKey(0);
}