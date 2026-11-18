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
    //      Read Image with openCV
    // =====================================

    dense::matrix<float> imgMat = read_img2DenseMat("castle.jpg");

    // =====================================
    //      ChamPockSR_HuberTV
    // =====================================

    
    
    return 0;
}