#pragma once
#include <glm/ext/matrix_float4x4.hpp>

class MatrixHelper {
private:
    MatrixHelper() {}
    MatrixHelper(const MatrixHelper&) = delete;
    MatrixHelper& operator=(const MatrixHelper&) = delete;    

public:
	void printMatrix(const glm::mat4& matrix);
    static MatrixHelper& getInstance();
};