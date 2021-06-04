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

    keyboardKeys.t_x0 = x;
    keyboardKeys.t_y0 = y;
    keyboardKeys.t_x1 = x;
    keyboardKeys.t_y1 = y;
    keyboardKeys.t_x2 = x;
    keyboardKeys.t_y2 = y;
    keyboardKeys.t_x3 = x;
    keyboardKeys.t_y3 = y;
    keyboardKeys.t_x4 = 1.0;
    keyboardKeys.t_y4 = 1.0;
    keyboardKeys.t_x5 = x;
}

Keys GetMouseKeys(){
    
    Keys returnMouseKeys;
    
    returnMouseKeys.t_x = mouseKeys.t_x;
    returnMouseKeys.t_y = mouseKeys.t_y;

    return returnMouseKeys;
}

Keys GetKeyboardKeys(){

    Keys returnKeyboardKeys;
    
    returnKeyboardKeys.t_x0 = keyboardKeys.t_x0;
    returnKeyboardKeys.t_y0 = keyboardKeys.t_y0;
    returnKeyboardKeys.t_x1 = keyboardKeys.t_x1;
    returnKeyboardKeys.t_y1 = keyboardKeys.t_y1;
    returnKeyboardKeys.t_x2 = keyboardKeys.t_x2;
    returnKeyboardKeys.t_y2 = keyboardKeys.t_y2;
    returnKeyboardKeys.t_x3 = keyboardKeys.t_x3;
    returnKeyboardKeys.t_y3 = keyboardKeys.t_y3;
    returnKeyboardKeys.t_x4 = keyboardKeys.t_x4;
    returnKeyboardKeys.t_y4 = keyboardKeys.t_y4;
    returnKeyboardKeys.t_x5 = keyboardKeys.t_x5;

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

    if (key == 68) keyboardKeys.t_x0 += 0.01; // D
    if (key == 65) keyboardKeys.t_x0 -= 0.01; // A
    if (key == 87) keyboardKeys.t_y0 += 0.01; // W
    if (key == 83) keyboardKeys.t_y0 -= 0.01; // S

    if (key == 72) keyboardKeys.t_x1 += 0.01; // H
    if (key == 70) keyboardKeys.t_x1 -= 0.01; // F
    if (key == 84) keyboardKeys.t_y1 += 0.01; // T
    if (key == 71) keyboardKeys.t_y1 -= 0.01; // G

    if (key == 76) keyboardKeys.t_x2 += 0.01; // L
    if (key == 74) keyboardKeys.t_x2 -= 0.01; // J
    if (key == 73) keyboardKeys.t_y2 += 0.01; // I
    if (key == 75) keyboardKeys.t_y2 -= 0.01; // K

    if (key == 262) keyboardKeys.t_x3 += 0.01; // Right
    if (key == 263) keyboardKeys.t_x3 -= 0.01; // Left
    if (key == 265) keyboardKeys.t_y3 += 0.01; // Up
    if (key == 264) keyboardKeys.t_y3 -= 0.01; // Down

    if(key == 334){ // +
        keyboardKeys.t_x4  += 0.01;
        keyboardKeys.t_y4  += 0.01;
    }
    if(key == 333){ // -
        keyboardKeys.t_x4  -= 0.01;
        keyboardKeys.t_y4  -= 0.01;    
    }

    if (key == 90) keyboardKeys.t_x5 += 0.1; // Z
}