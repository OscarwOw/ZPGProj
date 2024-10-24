#include "ErrorHandler.h"
#include <iostream>
#include <string>

void ErrorHandler::GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool ErrorHandler::GLCheckError() {
	while (GLenum error = glGetError()) {
        
        std::string streerr;
        switch (error) {
        case GL_NO_ERROR:
            streerr = "No error";
            break;
        case GL_INVALID_ENUM:
            streerr = "GL_INVALID_ENUM: An unacceptable value has been specified for an enumerated argument.";
            break;
        case GL_INVALID_VALUE:
            streerr = "GL_INVALID_VALUE: A numeric argument is out of range.";
            break;
        case GL_INVALID_OPERATION:
            streerr = "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
            break;
        case GL_STACK_OVERFLOW:
            streerr = "GL_STACK_OVERFLOW: This command would cause a stack overflow.";
            break;
        case GL_STACK_UNDERFLOW:
            streerr = "GL_STACK_UNDERFLOW: This command would cause a stack underflow.";
            break;
        case GL_OUT_OF_MEMORY:
            streerr = "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            streerr = "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
            break;
        default:
            streerr = "Unknown error";
        }
		std::cout << "error: " << streerr << std::endl;
        return false;
	}
    return true;
}