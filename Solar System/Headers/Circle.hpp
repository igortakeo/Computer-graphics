#ifndef Circle_H
#define Circle_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct coordinates{
    float x;
    float y;
}Coordinates;

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