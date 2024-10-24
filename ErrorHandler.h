#pragma once
#include <GL/glew.h>

class ErrorHandler {
public:
    ErrorHandler();
    static void GLClearError();
    static bool GLCheckError();
};