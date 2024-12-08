#include "StartupManager.hpp"
#include <iostream>

//AUTOR BEL0130

StartupManager& StartupManager::getInstance()
{
    static StartupManager instance;
    return instance;
}

int StartupManager::initializeProgram(GLFWwindow** window, int width, int height, const char* title)
{
    InitializeGLFW();
    SetWindowHints();
    *window = CreateWindow(width, height, title);
    _window = *window;
    if (*window == nullptr) return -1;

    if (InitializeGLEW(*window) == -1)  return -1;

    PrintInfo();

    ViewPortSetup(*window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_STENCIL_TEST);
    
    glDepthFunc(GL_LESS);
    return 0;
}

void StartupManager::InitializeGLFW() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
}

int StartupManager::InitializeGLEW(GLFWwindow* window) {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not initialize GLEW\n");
        return -1;
    }
    return 0;
}

void StartupManager::SetWindowHints() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* 
        //OpenGL Legacy allowed
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); //for any profile
    */
}

GLFWwindow* StartupManager::CreateWindow(int width, int height, const char* title) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "ERROR: Could not create GLFW window\n";
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    return window;
}

void StartupManager::PrintInfo() {
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void StartupManager::ViewPortSetup(GLFWwindow* window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);
}

GLFWwindow* StartupManager::getWindow()
{
    return _window;
}



void StartupManager::DrawLegacyTriangles(){
    glBegin(GL_TRIANGLES);  // Start drawing triangles
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color
    glVertex3f(-0.5f, -0.5f, 0.0f);  // First vertex (bottom-left)

    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    glVertex3f(0.5f, -0.5f, 0.0f);  // Second vertex (bottom-right)

    glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    glVertex3f(0.0f, 0.5f, 0.0f);  // Third vertex (top)
    glEnd();  // Finish drawing triangles
}