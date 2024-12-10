#include <opencv2/opencv.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
void build2DMap (const std::vector<cv::KeyPoint>& keypoints,
                const cv::Mat& img)
{
    cv::Mat map = img.clone();
    for(const auto& kp : keypoints){
        cv::circle(map, kp.pt, 3, cv::Scalar(0,255,0), -1);
    }
    cv::imwrite("/home/omar/TUM/05_projects/Mono-SLAM/data/output/map2D.png", map);
}
void build3DMap(const std::vector<cv::Point3f>& points3D) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    for (const auto& point : points3D) {
        cloud->points.push_back(pcl::PointXYZ(point.x, point.y, point.z));
    }

    cloud->width = cloud->points.size();
    cloud->height = 1;
    cloud->is_dense = false;

    pcl::io::savePCDFileASCII("map3D.pcd", *cloud);
    std::cout << "Saved 3D map with " << cloud->points.size() << " points." << std::endl;
   pcl::visualization::PCLVisualizer viewer("3D Viewer");
   viewer.addPointCloud(cloud, "cloud");
   viewer.spin();
}
