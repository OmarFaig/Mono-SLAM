#include <pangolin/pangolin.h>
#include <opencv2/opencv.hpp>
#include "Visualization.h"

void setupVisualization(int width, int height, const std::vector<cv::Mat>& images) {
    pangolin::CreateWindowAndBind("ORB-SLAM2", width, height);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(width, height, 420, 420, width/2, height/2, 0.2, 100),
        pangolin::ModelViewLookAt(0, -10, -0.1, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    // Create Interactive View in window
    const int UI_WIDTH = 180;
    
    // Create a Panel
    pangolin::CreatePanel("menu").SetBounds(0.0, 1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));

    // Add menu items
    pangolin::Var<bool> menuFollow("menu.Follow Camera", true, true);
    pangolin::Var<bool> menuShowPoints("menu.Show Points", true, true);
    pangolin::Var<bool> menuShowKeyframes("menu.Show KeyFrames", true, true);
    pangolin::Var<bool> menuShowGraph("menu.Show Graph", true, true);
    pangolin::Var<bool> menuLocalizationMode("menu.Localization Mode", false, true);
    pangolin::Var<bool> menuReset("menu.Reset", false, false);

    // Create three views for our visualization
    pangolin::View& d_cam = pangolin::CreateDisplay()
        .SetBounds(0.5, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0)
        .SetHandler(new pangolin::Handler3D(s_cam));

    // Create two views for the stereo images, each taking half of the bottom space
    pangolin::View& d_image1 = pangolin::CreateDisplay()
        .SetBounds(0.0, 0.5, pangolin::Attach::Pix(UI_WIDTH), 0.5);
    
    pangolin::View& d_image2 = pangolin::CreateDisplay()
        .SetBounds(0.0, 0.5, 0.5, 1.0);

    size_t currentImageIdx = 0;

    // Main display loop
    while(!pangolin::ShouldQuit()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        // Draw coordinate frame
        glLineWidth(3);
        pangolin::glDrawAxis(1.0);
        
        // Display images if available
        if(!images.empty() && currentImageIdx < images.size()) {
            cv::Mat img_to_display = images[currentImageIdx];
            
            d_image1.Activate();
            glColor3f(1.0, 1.0, 1.0);
            pangolin::GlTexture imageTexture(img_to_display.cols, img_to_display.rows, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);
            imageTexture.Upload(img_to_display.data, GL_BGR, GL_UNSIGNED_BYTE);
            imageTexture.RenderToViewport();
            
            // For demonstration, show the same image in both views
            d_image2.Activate();
            imageTexture.RenderToViewport();
            
            // Move to next image every few frames
            if(currentImageIdx < images.size() - 1) {
                currentImageIdx++;
            }
        }

        pangolin::FinishFrame();
        
        // Add a small delay to control visualization speed
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}