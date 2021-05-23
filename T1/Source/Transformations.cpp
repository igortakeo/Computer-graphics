#include "../Headers/Transformations.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
