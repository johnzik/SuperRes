#include "SR_functions.hpp"

cv::Mat addGaussianNoise(const cv::Mat& rgb, double noise_variance, double mean = 0.0)
{
    if (noise_variance < 0.0) {
        throw std::invalid_argument("Error: Noise variance cannot be negative");
    }
    if (noise_variance == 0.0 && mean == 0.0) {
        return rgb.clone();
    }

    // Scale normalized [0, 1] mean and std dev to 8-bit [0, 255] range
    double mean255   = 255.0 * mean;
    double stddev255 = 255.0 * std::sqrt(noise_variance);

    // Generate noise in signed 16-bit buffer so negative values are not clipped
    cv::Mat noise(rgb.size(), CV_16SC(rgb.channels()));
    cv::randn(noise, cv::Scalar::all(mean255), cv::Scalar::all(stddev255));

    // Add noise and saturate back to [0, 255] (CV_8UC3)[cite: 2]
    cv::Mat noisyRgb;
    cv::add(rgb, noise, noisyRgb, cv::noArray(), rgb.type());
    return noisyRgb;
}