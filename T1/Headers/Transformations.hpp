#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

vector<float> CreateMatrixTranslation(float t_x, float t_y);
vector<float> CreateMatrixRotation(float t_x);
vector<float> CreateMatrixScale(float t_x, float t_y);
vector<float> CreateMatrixScaleReferencePoint(float t_x, float t_y, float p_x, float p_y);
vector<float> CreateMatrixRotationReferencePoint(float t_x, float p_x, float p_y);
vector<float> Multiplication(vector<float> m1, vector<float>m2);

#endif