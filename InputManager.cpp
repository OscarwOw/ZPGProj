#include "InputManager.h"
#include "Application.h"

//Application& _application = Application::getInstance();

void InputManager::handleMovement(float time) {

    if (_forwardMovement) {
        Camera::getInstance().processKeyboard(CameraMovement::FORWARD, time);
    }
    if (_leftMovement) {
        Camera::getInstance().processKeyboard(CameraMovement::LEFT, time);
    }
    if (_backwardMovement) {
        Camera::getInstance().processKeyboard(CameraMovement::BACKWARD, time);
    }
    if (_rightMovement) {
        Camera::getInstance().processKeyboard(CameraMovement::RIGHT, time);
    }
    if (_upMovement) {
        Camera::getInstance().processKeyboard(CameraMovement::UP, time);
    }
    if (_downMovement) {
        Camera::getInstance().processKeyboard(CameraMovement::DOWN, time);
    }

    
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager& inputManager = InputManager::getInstance();
    if (key == GLFW_KEY_W && (action == GLFW_PRESS)) {
        inputManager._forwardMovement = true;
    }
    if (key == GLFW_KEY_W && (action == GLFW_RELEASE)) { 
        inputManager._forwardMovement = false;
    }

    if (key == GLFW_KEY_A && (action == GLFW_PRESS)) { 
        inputManager._leftMovement = true;
    }
    if (key == GLFW_KEY_A && (action == GLFW_RELEASE)) {  
        inputManager._leftMovement = false;
    }

    if (key == GLFW_KEY_S && (action == GLFW_PRESS)) { 
        inputManager._backwardMovement = true;
    }
    if (key == GLFW_KEY_S && (action == GLFW_RELEASE)) { 
        inputManager._backwardMovement = false;
    }

    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS)) {
        inputManager._upMovement = true;
    }
    if (key == GLFW_KEY_SPACE && (action == GLFW_RELEASE)) {
        inputManager._upMovement = false;
    }

    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_PRESS)) {
        inputManager._downMovement = true;
    }
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_RELEASE)) {
        inputManager._downMovement = false;
    }



    if (key == GLFW_KEY_D && (action == GLFW_PRESS)) {  
        inputManager._rightMovement = true;
    }
    if (key == GLFW_KEY_D && (action == GLFW_RELEASE)) { 
        inputManager._rightMovement = false;
    }

    if (key == GLFW_KEY_N && (action == GLFW_PRESS)) {
        SceneManager::getInstance().switchToNextScene();
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void InputManager::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    InputManager& inputManager = InputManager::getInstance();
    if (inputManager._mousePressed) {
        Camera::getInstance().processMouseMovement(mouseX - inputManager._lastMouseX, mouseY - inputManager._lastMouseY, false);
    }
    inputManager._lastMouseX = mouseX;
    inputManager._lastMouseY = mouseY;
}

void InputManager::mouse_button_pressed_callback(GLFWwindow* window, int button, int action, int mods) {
    InputManager& inputManager = InputManager::getInstance();
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        inputManager._mousePressed = true;
        printf("mouse pressed\n");
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        printf("mouse released\n");
        inputManager._mousePressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int x = inputManager._lastMouseX;
        int y = inputManager._lastMouseY;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        GLbyte color[4];
        GLfloat depth;
        GLuint index; // identifikace tìlesa
        int newy = height - y - 10;


        glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

        if (index > 0 && index <= 254) {

            float nx = (2.0f * x) / width - 1.0f;
            float ny = 1.0f - (2.0f * y) / height;
            float nz = 2.0f * depth - 1.0f; 

            printf("something\n");
            glm::mat4 view = Camera::getInstance().getViewMatrix();
            glm::mat4 perspective = Camera::getInstance().getPerspectiveMatrix();

            glm::mat4 invProj = glm::inverse(perspective);
            glm::vec4 clipPos = glm::vec4(nx, ny, nz, 1.0f);
            glm::vec4 viewPos = invProj * clipPos;

            viewPos /= viewPos.w;

            glm::mat4 invView = glm::inverse(view);
            glm::vec4 worldPos = invView * viewPos;
            
            printf("world coor = X: %f\n Y: %f\n Z:%f\n", worldPos.x, worldPos.y, worldPos.z);

            TransformationData tdata;
            MaterialProperties material;
            material.ambientReflectivity = glm::vec3(0.4f);
            material.diffuseReflectivity = glm::vec3(0.8f);
            material.specularReflectivity = glm::vec3(0.5f);
            material.shininess = 4;

            DrawableObject* tree = new DrawableObject(tdata, ShaderType::Develop, ModelType::TREE, glm::vec3(0.0f, 0.0f, 1.0f), material);            

            NewTransformationTranslate* translate = new NewTransformationTranslate(glm::vec3(worldPos.x, worldPos.y, worldPos.z));
            NewTransformationScale* scale = new NewTransformationScale(glm::vec3(1.0f));

            tree->transformationComposite.addTransformation(translate);
            tree->transformationComposite.addTransformation(scale);

            SceneManager::getInstance().getCurrentScene()->addObject(tree);
            Camera::getInstance().attachObserver(tree->getSaherProgram());
        }
    }
}

int InputManager::initializeEvents() {

    glfwSetCursorPosCallback(StartupManager::getInstance().getWindow(), cursor_pos_callback);
    glfwSetMouseButtonCallback(StartupManager::getInstance().getWindow(), mouse_button_pressed_callback);
    glfwSetKeyCallback(StartupManager::getInstance().getWindow(), key_callback);
    return 0;
}

