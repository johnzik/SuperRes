#include "SR_functions.hpp"

dense::matrix<dataType> degrade_image(const cv::String& img_path, int s, float noise_var)
{
    if (img_path.empty())
    {
        throw std::runtime_error("Error: Image path is empty!");
    }

    if (s <=0)
    {
        throw std::runtime_error("Error: Downscale factor 's' must be positive!");
    }

    cv::Mat bgr = cv::imread(img_path, cv::IMREAD_COLOR);

    if (bgr.empty())
    {
        throw std::runtime_error("Error: Could not open or read image at: " + std::string(img_path));
    }

    cv::Mat rgb;
    cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);
    
    // Downscale if s>1
    if (s > 1)
    {
        double invScaleFactor = (1.0 / static_cast<double>(s));
        cv::resize(rgb, rgb, cv::Size(), invScaleFactor, invScaleFactor, cv::INTER_AREA);
    }
    
    // Add Guassian noise
    rgb = addGaussianNoise(rgb, noise_var);

    // Convert cv::Mat to dense::matrix
    return CVmat2DenseMat(rgb);
}   