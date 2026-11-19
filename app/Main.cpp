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

    dense::matrix<float> p = {4, 4, 2, 3};
    
    std::cout << "p[0,0,0,0]: " << p.get_value_at(0) << std::endl;
    std::cout << "p[3,3,0,0]: " << p.get_value_at(90) << std::endl;
    std::cout << "p[3,3,1,0]: " << p.get_value_at(93) << std::endl;
    std::cout << "p[3,3,0,1]: " << p.get_value_at(91) << std::endl;
    return 0;
}