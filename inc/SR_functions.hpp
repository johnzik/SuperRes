#ifndef SR_FUNCS_HPP
#define SR_FUNCS_HPP

#include <iostream>
#include "CppProject/matrix.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include "SR_datatypes.hpp"
#include <string>

/**
 * @brief           Read image with openCV and convert it to a matrix
 * @param img_path  A string containing the path of the image  
 */
dense::matrix<float> read_img2DenseMat(const cv::String& img_path);

#endif