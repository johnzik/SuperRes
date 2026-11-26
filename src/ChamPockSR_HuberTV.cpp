#include "SR_functions.hpp"

dense::matrix<float> ChamPockSR_HuberTV(
    dense::matrix<float> noisy_imgMat,
    dense::matrix<float> x,
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
    dense::matrix<float> q = {HR_rows, HR_cols, 3};

    dense::matrix<float> x_bar = x;

    for (size_t i=0; i < max_iter; i++)
    {
        std::cout << "Iteration: " << i << std::endl;
        
        dense::matrix<float> x_old = x;

        // Step 1: Dual Ascent for p across RGB channels
        for (size_t c=0; c<3; c++)
        {
            // Returns a {HR_rows, HR_cols, 2} matrix for channel c
            // dense::matrix<float> grad_c = opD(x_bar, c, HR_rows, HR_cols);
            for (int r = 0; r < HR_rows; ++r)
            {
                for (int col = 0; col < HR_cols; ++col)
                {
                    for (int d = 0; d < 2; ++d)
                    {
                        // p(r, col, d, c) += sgm1 * grad_c(r, col, d);
                    }
                }
            }
        }
    }
}