#include "glfw_lambda_callback_manager.hpp"

GLFWLambdaCallbackManager::GLFWLambdaCallbackManager(GLFWwindow *window, CharCallback char_callback,
                                                     KeyCallback key_callback, CursorPosCallback cursor_pos_callback,
                                                     MouseButtonCallback mouse_button_callback)
    : window_(window), char_callback_(char_callback), key_callback_(key_callback),
      cursor_pos_callback_(cursor_pos_callback), mouse_button_callback_(mouse_button_callback) {
    glfwSetWindowUserPointer(window, this);
    glfwSetCharCallback(window, GLFWLambdaCallbackManager::char_callback_wrapper);
    glfwSetKeyCallback(window, GLFWLambdaCallbackManager::key_callback_wrapper);
    glfwSetCursorPosCallback(window, GLFWLambdaCallbackManager::cursor_pos_callback_wrapper);
    glfwSetMouseButtonCallback(window, GLFWLambdaCallbackManager::mouse_button_callback_wrapper);
}

void GLFWLambdaCallbackManager::char_callback_wrapper(GLFWwindow *window, unsigned int codepoint) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->char_callback_) {
        manager->char_callback_(codepoint);
    }
}

void GLFWLambdaCallbackManager::key_callback_wrapper(GLFWwindow *window, int key, int scancode, int action, int mods) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->key_callback_) {
        manager->key_callback_(key, scancode, action, mods);
    }
}

void GLFWLambdaCallbackManager::cursor_pos_callback_wrapper(GLFWwindow *window, double mouse_position_x,
                                                            double mouse_position_y) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->cursor_pos_callback_) {
        manager->cursor_pos_callback_(mouse_position_x, mouse_position_y);
    }
}

void GLFWLambdaCallbackManager::mouse_button_callback_wrapper(GLFWwindow *window, int button, int action, int mods) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->mouse_button_callback_) {
        manager->mouse_button_callback_(button, action, mods);
    }
}
