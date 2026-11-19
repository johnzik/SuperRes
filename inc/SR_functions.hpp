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
 * @brief           Read image with openCV, upscale it with bicubic interpolation 
 *                  and convert it to a matrix
 * @param img_path  A string containing the path of the image  
 * @param s         The upscaling factor
 */
dense::matrix<float> read_img2UpscDenseMat(const cv::String& img_path, int s);

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
 * @param noisy_imgMat  Noisy image input matrix for denoising and upscaling
 * @param s             The downscaling factor
 * @param sgm1          Gradient Dual Step Size - p
 * @param sgm2          Data Dual Step Size - q
 * @param tau           Primal Step Size (tau * (8*sgm1 + sgm2/s^2) < 1)
 * @param max_iter      Adequate iterations for convergence
 * @param lamda         TV / Huber regularization weight (lamda = 0.035-0.045 for noise_var = 0.01)
 * @param alpha         Huber-TV threshold (smooths small gradients, prevents staircasing)
 * @param tol           Convergence tolerance
 */
dense::matrix<float> ChamPockSR_HuberTV(
    dense::matrix<float> noisy_imgMat, 
    int s, 
    float sgm1,
    float sgm2,
    float tau,
    float max_iter,
    float lamda,
    float alpha,
    float tol
    );



#endif