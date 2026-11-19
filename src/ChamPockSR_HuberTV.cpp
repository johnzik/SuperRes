#include "SR_functions.hpp"

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
    )
{
    if (noisy_imgMat.get_dim_size(2) != 3)
    {
        throw std::runtime_error("Input must be a color image (RGB).");
    }

    // Calculate High-Res dimensions
    int HR_rows = noisy_imgMat.get_dim_size(0) * s;
    int HR_cols = noisy_imgMat.get_dim_size(1) * s;
    
    // Initialize Chambolle-Pock variables
    dense::matrix<float> p = {HR_rows, HR_cols, 2, 3};
    
}