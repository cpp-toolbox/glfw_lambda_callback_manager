# glfw_lambda_callback_manager
SUBPROJECT

By default you don't have access to much inside of the regular glfw callbacks, this causes most people to just use some global state and access those things inside the callbacks, this is for those who don't want that.

If you don't use global state then you are limited to stuffing what you need in the glfw user pointer, for example suppose you want to update the hud when the user types, so the hud has to be part of the user pointer, now you want to also update some other part of the code like the input state of the keyboard, and so that also needs to go into the user pointer, so this user pointer starts becoming a little bloated with random things, instead we could create our own polling on the keyboard by iterating through each key of interest and then checking if it's pressed, but this also feels hacky. 

Another solution is that in main.cpp you could create lambda functions which are global and then the callbacks can access the lambdas, and so you don't have to mess with the user pointer, but now your lambdas are global which we didn't want to do.

Another thought is that maybe the lambdas could be defined in main(), but that provides a problem because we can't define c style functions inside of other c style functions, and so we can never make our callbacks use the lambdas because they would have to be defined outside of this function call, but then the lambdas would already be removed from the stack.

This subproject provides a solution by encapsulating the lambdas in a class, and then providing class members which are regular c style functions which call the lambdas.

## usage
```cpp
    std::function<void(unsigned int)> char_callback = [](unsigned int _) {};
    std::function<void(int, int, int, int)> key_callback = [](int _, int _1, int _2, int _3) {};
    std::function<void(double, double)> mouse_pos_callback = [](double _, double _1) {};
    std::function<void(int, int, int)> mouse_button_callback = [](int _, int _1, int _2) {};
    GLFWLambdaCallbackManager glcm(window, char_callback, key_callback, mouse_pos_callback, mouse_button_callback);
```
