#include "SR_functions.hpp"

dense::matrix<float> CVmat2DenseMat(const cv::Mat& rgb)
{
    if (rgb.empty() || rgb.channels() != 3) {
        throw std::invalid_argument("Error: Expected a non-empty 3-channel RGB cv::Mat");
    }

    cv::Mat continuousRgb = rgb.isContinuous() ? rgb : rgb.clone();

    std::vector<float> rgbVec(
        continuousRgb.data,
        continuousRgb.data + continuousRgb.total() * continuousRgb.elemSize()
    );

    size_t rowSize   = static_cast<size_t>(continuousRgb.rows);
    size_t colSize   = static_cast<size_t>(continuousRgb.cols);
    size_t depthSize = 3;

    std::vector<size_t> dimVec = {rowSize, colSize, depthSize};

    // Interleaved (HWC) strides matching rgbVec layout
    std::vector<int> strides = {
        static_cast<int>(colSize * depthSize),
        static_cast<int>(depthSize),
        1
    };
    
    return dense::matrix<float>(rgbVec, dimVec, strides);
}