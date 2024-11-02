#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "StartupManager.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <chrono>


#include "ErrorHandler.h"
#include "DrawableObject.h"
#include "SceneManager.h"
#include "SceneGenerator.h"
#include "ShaderProgramManager.h"
#include "Application.h"


int main(void)
{
    int state = Application::getInstance().startApplication(); //TODO return state  
    return state;
}
