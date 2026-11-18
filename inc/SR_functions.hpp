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

/**
 * @brief           A function that adds Gaussian noise and downsacles
 *                  an image by a factor 's'
 * @param imgMat    The input function
 * @param s         The downscaling factor
 * @param noise_var The Gaussian noise variance
 */
dense::matrix<float> degrade_image(dense::matrix<float> imgMat, int s, float noise_var);

/**
 * @brief               A function that performs Chambolle-Pock's Super-Resolution
 *                      image upscaling and denoising with Huber Total Variation
 * @param noisy_imgMat  The noisy image input for denoising and upscaling
 */
dense::matrix<float> ChamPockSR_HuberTV(
    dense::matrix<float> noisy_imgMat, 
    float sgm1,
    float sgm2,
    float tau,
    float max_iter,
    float lamda,
    float alpha,
    float tol
    );



#endif