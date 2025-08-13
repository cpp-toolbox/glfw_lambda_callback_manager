#include "glfw_lambda_callback_manager.hpp"
#include <GLFW/glfw3.h>
#include <ostream>
#include <iostream>

void GLFWLambdaCallbackManager::register_all_callbacks_with_glfw() {
    glfwSetCharCallback(window_, GLFWLambdaCallbackManager::char_callback_wrapper);
    glfwSetKeyCallback(window_, GLFWLambdaCallbackManager::key_callback_wrapper);
    glfwSetCursorPosCallback(window_, GLFWLambdaCallbackManager::cursor_pos_callback_wrapper);
    glfwSetMouseButtonCallback(window_, GLFWLambdaCallbackManager::mouse_button_callback_wrapper);
    glfwSetScrollCallback(window_, GLFWLambdaCallbackManager::scroll_callback_wrapper);
    glfwSetFramebufferSizeCallback(window_, GLFWLambdaCallbackManager::frame_buffer_size_callback_wrapper);
}

GLFWLambdaCallbackManager::GLFWLambdaCallbackManager(GLFWwindow *window) : window_(window) {
    // NOTE: we store this object into the user pointer so then we can call the right callback during any callback
    // this can become a problem for example if you construct this in an initializer list then "this" will point
    // to the temporary and not the one you're trying to save as a member attribute (A)
    glfwSetWindowUserPointer(window, this);
    register_all_callbacks_with_glfw();
}

GLFWLambdaCallbackManager::GLFWLambdaCallbackManager(GLFWwindow *window, CharCallback char_callback,
                                                     KeyCallback key_callback, CursorPosCallback cursor_pos_callback,
                                                     MouseButtonCallback mouse_button_callback,
                                                     ScrollCallback scroll_callback,
                                                     FrameBufferSizeCallback frame_buffer_size_callback)
    : window_(window), char_callback_(char_callback), key_callback_(key_callback),
      cursor_pos_callback_(cursor_pos_callback), mouse_button_callback_(mouse_button_callback),
      scroll_callback_(scroll_callback), frame_buffer_size_callback_(frame_buffer_size_callback) {
    glfwSetWindowUserPointer(window, this);
    register_all_callbacks_with_glfw();
}

void GLFWLambdaCallbackManager::set_char_callback(CharCallback char_callback) { char_callback_ = char_callback; }
void GLFWLambdaCallbackManager::set_key_callback(KeyCallback key_callback) { key_callback_ = key_callback; }
void GLFWLambdaCallbackManager::set_cursor_pos_callback(CursorPosCallback cursor_pos_callback) {
    cursor_pos_callback_ = cursor_pos_callback;
}
void GLFWLambdaCallbackManager::set_mouse_button_callback(MouseButtonCallback mouse_button_callback) {
    mouse_button_callback_ = mouse_button_callback;
}

void GLFWLambdaCallbackManager::set_scroll_callback(ScrollCallback scroll_callback) {
    scroll_callback_ = scroll_callback;
}

void GLFWLambdaCallbackManager::set_frame_buffer_size_callback(FrameBufferSizeCallback frame_buffer_size_callback) {
    frame_buffer_size_callback_ = frame_buffer_size_callback;
}

void GLFWLambdaCallbackManager::set_all_callbacks(AllGLFWLambdaCallbacks all_callbacks) {
    set_char_callback(all_callbacks.char_callback);
    set_key_callback(all_callbacks.key_callback);
    set_cursor_pos_callback(all_callbacks.cursor_pos_callback);
    set_mouse_button_callback(all_callbacks.mouse_button_callback);
    set_scroll_callback(all_callbacks.scroll_callback);
    set_frame_buffer_size_callback(all_callbacks.frame_buffer_size_callback);
}

// NOTE: callback wrappers are defined without an issue even if the internal callbacks are not defined due to the if
// statements

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

void GLFWLambdaCallbackManager::scroll_callback_wrapper(GLFWwindow *window, double x_offset, double y_offset) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->mouse_button_callback_) {
        manager->scroll_callback_(x_offset, y_offset);
    }
}

void GLFWLambdaCallbackManager::frame_buffer_size_callback_wrapper(GLFWwindow *window, int width, int height) {
    GLFWLambdaCallbackManager *manager = static_cast<GLFWLambdaCallbackManager *>(glfwGetWindowUserPointer(window));
    if (manager && manager->frame_buffer_size_callback_) {
        manager->frame_buffer_size_callback_(width, height);
    }
}
