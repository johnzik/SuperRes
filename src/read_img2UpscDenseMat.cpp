#include "SR_functions.hpp"

dense::matrix<float> read_img2UpscDenseMat(const cv::String& img_path, int s)
{
    if (img_path.empty())
    {
        throw std::runtime_error("Error: Image path is empty");
    }

    std::cout << "OpenCV reading image... " << std::endl;

    // RGB -> flat std::vector<float> (interleaved R, G, B)
    cv::Mat bgr = cv::imread(img_path, cv::IMREAD_COLOR);
    if (bgr.empty())
    {
        throw std::runtime_error("Error: Could not open or read image at: " + std::string(img_path));
    }

    // Bicubic Upscale
    cv::resize(bgr, bgr, cv::Size(), s, s, cv::INTER_CUBIC);

    cv::Mat rgb;
    cv::cvtColor(bgr, rgb, cv::COLOR_BGR2RGB);
    std::vector<float> rgbVec(rgb.data, rgb.data + rgb.total() * rgb.elemSize());

    size_t rowSize = rgb.rows;
    size_t colSize = rgb.cols;
    size_t depthSize = 3;

    // Store the image dimensions vector
    std::vector<size_t> dimVec = {rowSize, colSize, depthSize};

    // Store the strides vector
    std::vector<int> strides = {
        static_cast<int>(colSize * depthSize),
        static_cast<int>(depthSize),
        1
    };

    dense::matrix<float> imgMat(rgbVec, dimVec, strides);

    std::cout << "Image matrix 0-dim (Rows) size: " << imgMat.get_dim_size(0) << std::endl;
    std::cout << "Image matrix 1-dim (Columns) size: " << imgMat.get_dim_size(1) << std::endl;
    std::cout << "Image matrix 2-dim (Depth) size: " << imgMat.get_dim_size(2) << std::endl;

    return imgMat;
}