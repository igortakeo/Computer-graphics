#include "../Headers/Circle.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

float const pi = 3.1415;

CircleShape CreateCircle(int num_vertices, float radius, float angle, Coordenadas center){

    CircleShape circleShape;
    circleShape.num_vertices = num_vertices;
    circleShape.radius = radius;
    circleShape.angle = angle;

    float x, y;
    for (int i = 0; i < num_vertices; i++){
        angle += (2.0 * pi) / (float)num_vertices;
        x = center.x + cos(angle) * radius;
        y = center.y + sin(angle) * radius;
        Coordenadas c;
        c.x = x;
        c.y = y;
        circleShape.vertices.push_back(c);
    }

    return circleShape;
}