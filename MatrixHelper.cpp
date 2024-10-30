#include "MatrixHelper.h"
#include <iostream>


void MatrixHelper::printMatrix(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[j][i] << "\t\t\t"; 
        }
        std::cout << std::endl;
    }
}

MatrixHelper& MatrixHelper::getInstance()
{
    static MatrixHelper instance;
    return instance;   
}

