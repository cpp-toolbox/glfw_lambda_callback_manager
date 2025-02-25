#include "glfw_lambda_callback_manager.hpp"
#include <GLFW/glfw3.h>

GLFWLambdaCallbackManager::GLFWLambdaCallbackManager(GLFWwindow *window, CharCallback char_callback,
                                                     KeyCallback key_callback, CursorPosCallback cursor_pos_callback,
                                                     MouseButtonCallback mouse_button_callback,
                                                     FrameBufferSizeCallback frame_buffer_size_callback)
    : window_(window), char_callback_(char_callback), key_callback_(key_callback),
      cursor_pos_callback_(cursor_pos_callback), mouse_button_callback_(mouse_button_callback),
      frame_buffer_size_callback_(frame_buffer_size_callback) {
    // we store this object into the user pointer so then we can call the right callback during any callback
    glfwSetWindowUserPointer(window, this);
    glfwSetCharCallback(window, GLFWLambdaCallbackManager::char_callback_wrapper);
    glfwSetKeyCallback(window, GLFWLambdaCallbackManager::key_callback_wrapper);
    glfwSetCursorPosCallback(window, GLFWLambdaCallbackManager::cursor_pos_callback_wrapper);
    glfwSetMouseButtonCallback(window, GLFWLambdaCallbackManager::mouse_button_callback_wrapper);
    glfwSetFramebufferSizeCallback(window, GLFWLambdaCallbackManager::frame_buffer_size_callback_wrapper);
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

void GLFWLambdaCallbackManager::frame_buffer_size_callback_wrapper(GLFWwindow *window, int width, int height) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->frame_buffer_size_callback_) {
        manager->frame_buffer_size_callback_(width, height);
    }
}
