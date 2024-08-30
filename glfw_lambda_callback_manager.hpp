#ifndef GLFW_LAMBDA_CALLBACK_MANAGER_HPP
#define GLFW_LAMBDA_CALLBACK_MANAGER_HPP

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

class GLFWLambdaCallbackManager {
  public:
    using CharCallback = std::function<void(unsigned int)>;
    using KeyCallback = std::function<void(int, int, int, int)>;
    using CursorPosCallback = std::function<void(double, double)>;
    //    using MouseButtonCallback = std::function<void(int, int, int)>;

    GLFWLambdaCallbackManager(GLFWwindow *window, CharCallback char_callback, KeyCallback key_callback,
                              CursorPosCallback cursor_pos_callback);

  private:
    static void char_callback_wrapper(GLFWwindow *window, unsigned int codepoint);
    static void key_callback_wrapper(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void cursor_pos_callback_wrapper(GLFWwindow *window, double mouse_position_x, double mouse_position_y);
    //    static void mouse_button_callback_wrapper(GLFWwindow *window, int button, int action, int mods);

    GLFWwindow *window_;
    CharCallback char_callback_;
    KeyCallback key_callback_;
    CursorPosCallback cursor_pos_callback_;
    //    MouseButtonCallback mouse_button_callback_;
};

#endif // GLFW_LAMBDA_CALLBACK_MANAGER_HPP