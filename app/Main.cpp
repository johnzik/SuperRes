#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdint>

#include "CppProject/matrix.hpp"
#include "SR_datatypes.hpp"
#include "SR_functions.hpp"


int main()
{
    // =====================================
    //      Parameters Initialization
    // =====================================
    int s = 2;                                      // Upscaling/Downscaling factor
    float sgm1 = 1/8;                               // Gradient Dual Step Size - p
    float sgm2 = 1.0;                               // Data Dual Step Size - q
    float tau = 0.99 / (sgm1 * 8 + sgm2 / (s^2));   // Primal Step Size (tau * (8*sgm1 + sgm2/s^2) < 1)
    int max_iter = 200;                             // Adequate iterations for convergence
    float lamda = 0.04;                             // TV / Huber regularization weight (lamda = 0.035-0.045 for noise_var = 0.01)
    float alpha = 0.04;                             // Huber-TV threshold (smooths small gradients, prevents staircasing)
    double tol = 1e-5;                              // Convergence Tolerance 


    // =====================================
    //      Read Image with openCV
    // =====================================

    dense::matrix<float> imgMat = read_img2DenseMat("castle.jpg");
    dense::matrix<float> Upsc_imgMat = read_img2UpscDenseMat("castle.jpg", s);

    // =====================================
    //      ChamPockSR_HuberTV
    // =====================================

    dense::matrix<float> p = {4, 4, 2, 3};
    
    std::cout << "p[0,0,0,0]: " << p.get_value_at(0) << std::endl;
    std::cout << "p[3,3,0,0]: " << p.get_value_at(90) << std::endl;
    std::cout << "p[3,3,1,0]: " << p.get_value_at(93) << std::endl;
    std::cout << "p[3,3,0,1]: " << p.get_value_at(91) << std::endl;
    return 0;
}