#ifndef SR_FUNCS_HPP
#define SR_FUNCS_HPP

#include <iostream>
#include "CppProject/matrix.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include "SR_datatypes.hpp"
#include <string>
#include <stdexcept>
#include <cmath>

/**
 * @brief           Read image with openCV and convert it to a dense::matrix
 * @param img_path  A string containing the path of the image  
 */
dense::matrix<dataType> read_img2DenseMat(const cv::String& img_path);

/**
 * @brief      Convert a 3-channel RGB OpenCV Mat to a dense::matrix
 * @param rgb  An OpenCV Mat
 */
dense::matrix<dataType> CVmat2DenseMat(const cv::Mat& rgb);

/**
 * @brief                   Adds Guassian noise to an OpenCV Mat
 * @param noise_variance    Noise vairance specified on the normalized [0, 1] scale
 * @param mean              Mean specified on the normalized [0, 1] scale
 */
cv::Mat addGaussianNoise(const cv::Mat& rgb, double noise_variance, double mean = 0.0);

/**
 * @brief           Read image with openCV, upscale it with bicubic interpolation 
 *                  and convert it to a dense::matrix
 * @param img_path  A string containing the path of the image  
 * @param s         The upscaling factor
 */
dense::matrix<dataType> read_img2UpscDenseMat(const cv::String& img_path, int s);

/**
 * @brief           A function that adds Gaussian noise and downsacles
 *                  an image by a factor 's' and then saves the output to a file
 * @param img_path  A string containing the path of the image  
 * @param s         The downscaling factor 
 * @param noise_var The Gaussian noise variance
 * @param save_path A string containing the path of where to save the output image (omit this argument to skip saving)
 */
dense::matrix<dataType> degrade_image(const cv::String& img_path, int s, float noise_var, const cv::String& save_path = "");

/**
 * @brief               A function that performs Chambolle-Pock's Super-Resolution
 *                      image upscaling and denoising with Huber Total Variation
 * @param noisy_imgMat  Noisy image input matrix for denoising and upscaling
 * @param x             A bicubic interpolated initial noisy image
 * @param s             The downscaling factor
 * @param sgm1          Gradient Dual Step Size - p
 * @param sgm2          Data Dual Step Size - q
 * @param tau           Primal Step Size (tau * (8*sgm1 + sgm2/s^2) < 1)
 * @param max_iter      Adequate iterations for convergence
 * @param lamda         TV / Huber regularization weight (lamda = 0.035-0.045 for noise_var = 0.01)
 * @param alpha         Huber-TV threshold (smooths small gradients, prevents staircasing)
 * @param tol           Convergence tolerance
 */
dense::matrix<dataType> ChamPockSR_HuberTV(
    dense::matrix<dataType> noisy_imgMat,
    dense::matrix<dataType> x, 
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