#include "../Headers/Events.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>

using namespace std;

Keys mouseKeys;
Keys keyboardKeys;

void CreateMouseKeys(float x, float y){

    mouseKeys.t_x = x;
    mouseKeys.t_y = y;
}

void CreateKeyboardKeys(float x, float y){

    keyboardKeys.t_x = x;
    keyboardKeys.t_y = y;
}

Keys GetMouseKeys(){
    
    Keys returnMouseKeys;
    
    returnMouseKeys.t_x = mouseKeys.t_x;
    returnMouseKeys.t_y = mouseKeys.t_y;

    return returnMouseKeys;
}

Keys GetKeyboardKeys(){

    Keys returnKeyboardKeys;
    
    returnKeyboardKeys.t_x = keyboardKeys.t_x;
    returnKeyboardKeys.t_y = keyboardKeys.t_y;

    return returnKeyboardKeys;
}

void SetMouseEvent(GLFWwindow *window){
    glfwSetMouseButtonCallback(window, MouseEvent);
}

void SetKeyboardEvent(GLFWwindow *window){
    glfwSetKeyCallback(window, KeyboardEvent);
}

static void MouseEvent(GLFWwindow *window, int button, int action, int mods){
    
    if (button == GLFW_MOUSE_BUTTON_LEFT){
        mouseKeys.t_x += 0.01f;
        mouseKeys.t_y += 0.01f;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT){
        mouseKeys.t_x -= 0.01f;
        mouseKeys.t_y -= 0.01f;
    }   
}

static void KeyboardEvent(GLFWwindow *window, int key, int scancode, int action, int mods){

    if (key == 68) keyboardKeys.t_x += 0.01; // tecla para direita
    if (key == 65) keyboardKeys.t_x -= 0.01; // tecla para esquerda

    if (key == 87) keyboardKeys.t_y += 0.01; // tecla para cima
    if (key == 83) keyboardKeys.t_y -= 0.01; // tecla para baixo
}