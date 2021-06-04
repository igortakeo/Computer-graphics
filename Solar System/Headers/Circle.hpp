#ifndef Circle_H
#define Circle_H
#include "../Headers/Coordinates.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

class CircleShape{
    public:
        int num_vertices;
        vector<Coordinates>vertices;
        float radius;
        float angle;
        Coordinates center;
};

CircleShape CreateCircle(int num_vertices, float radius, float angle, Coordinates center);

#endif