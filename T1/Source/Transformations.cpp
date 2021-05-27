#include "../Headers/Transformations.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

vector<float> CreateMatrixTranslation(float t_x, float t_y){

    vector<float> MatTranslation
    {
        1.0, 0.0, 0.0, t_x,
        0.0, 1.0, 0.0, t_y,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 
    };

    return MatTranslation;
}

vector<float> CreateMatrixScale(float t_x, float t_y){

    vector<float> MatScale
    {
        t_x, 0.0, 0.0, 0.0,
        0.0, t_y, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 
    };

    return MatScale;
}

vector<float> CreateMatrixRotation(float t_x){

    vector<float> MatRotation
    {
        cos(t_x), -sin(t_x), 0.0, 0.0,
        sin(t_x),  cos(t_x), 0.0, 0.0,
             0.0,       0.0, 1.0, 0.0,
             0.0,       0.0, 0.0, 1.0
    };

    return MatRotation;
}