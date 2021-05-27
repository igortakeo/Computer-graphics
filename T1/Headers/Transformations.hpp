#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

vector<float> CreateMatrixTranslation(float t_x, float t_y);
vector<float> CreateMatrixRotation(float t_x);
vector<float> CreateMatrixScale(float t_x, float t_y);

#endif