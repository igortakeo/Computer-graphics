#ifndef EVENTS_H
#define EVENTS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Keys{
    public: 
        //Mouse
        float t_x;
        float t_y;

        //A,W,S,D
        float t_x0;
        float t_y0;

        //F,T,G,H
        float t_x1;
        float t_y1;

        //J,I,K,L
        float t_x2;
        float t_y2;

        //Setas
        float t_x3;
        float t_y3;

        //+,-
        float t_x4;
        float t_y4;

        //Z
        float t_x5;

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