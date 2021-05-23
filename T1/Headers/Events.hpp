#ifndef EVENTS_H
#define EVENTS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Keys{
    public: 
        float t_x;
        float t_y;
};
void CreateMouseKeys(float x, float y);
void CreateKeyboardKeys(float x, float y);
Keys GetMouseKeys();
Keys GetKeyboardKeys();
void SetMouseEvent(GLFWwindow *window);
void SetKeyboardEvent(GLFWwindow *window);
static void MouseEvent(GLFWwindow *window, int button, int action, int mods);
static void KeyboardEvent(GLFWwindow *window, int key, int scancode, int action, int mods);

#endif