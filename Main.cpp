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

#include "plain.h"
#include "tree.h"
#include "Mesh.h"
#include "ErrorHandler.h"
#include "DrawableObject.h"


static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    //printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY);
}



//vertex buffer
float points[] = {
	 -0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,	
	 0.5f, 0.5f, 0.0f,
    - 0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};


int main(void)
{
    glfwSetErrorCallback(error_callback);

    StartupManager::InitializeGLFW();
    StartupManager::SetWindowHints();
    GLFWwindow* window = StartupManager::CreateWindow(1500, 1200, "My OpenGL Window");

    if (StartupManager::InitializeGLEW(window) == -1)  return -1;

    StartupManager::PrintInfo();

    StartupManager::ViewPortSetup(window);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)-> void {cursor_pos_callback(window, mouseXPos, mouseYPos); });

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //todo initialize
    ShaderProgram *shaderProgram = new ShaderProgram();

    ShaderProgramSourceStrings source = shaderProgram->parseShaders("ColorShader.shader");
    unsigned int shader = shaderProgram->attachShader(source.VertexSource, source.FragmentSource);

    //Mesh basicMesh(points, sizeof(points)/sizeof(float) , indices, sizeof(indices) / sizeof(unsigned int), GL_TRIANGLES);

    DrawableObject treeObject;
    treeObject.setShaderProgram(shaderProgram);
    treeObject.loadFromRawData(tree, 92814, 6);

    /*GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VertexBuffer vertexBuffer(points, sizeof(points));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL);

    IndexBuffer indexBuffer(indices, sizeof(indices) / sizeof(unsigned int));




    glBindVertexArray(0);*/

    //VertexBuffer treeVBO(plain, sizeof(plain));
    //treeVBO.Bind();

    float scale = 0.05;
    float rotationAngle = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        treeObject.transformationComposite.removeTransformations();

        rotationAngle += 0.05f;
        if (rotationAngle >= 360.0f) rotationAngle = 0.0f;

        // Apply the rotation to the object (around Y-axis)
        treeObject.rotate(rotationAngle, 0.0f, 1.0f, 0.0f);

        if (scale > 0.3) {
            scale = 0.05;
        }
        scale = scale * 1.0001000;
        treeObject.scale(scale);
        treeObject.Draw();

        /*glBindVertexArray(VAO);
        indexBuffer.Bind();*/

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        //basicMesh.DrawMesh();
        
        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    shaderProgram->~ShaderProgram();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
