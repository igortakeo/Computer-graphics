#ifndef Circle_H
#define Circle_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct coordenadas{
    float x;
    float y;
}Coordenadas;

class CircleShape{
    public:
        int num_vertices;
        vector<Coordenadas>vertices;
        float radius;
        float angle;
};

CircleShape CreateCircle(int num_vertices, float radius, float angle);

#endif