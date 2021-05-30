#include "../Headers/Star.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

vector<float> CreateStars(){

    vector<float> PointsStar
    {
        //Center shape
        -0.60, 0.67, 
        -0.68, 0.67,
        -0.7, 0.58,
        -0.64, 0.53,
        -0.58, 0.58,
        
        //Triangle-0
        -0.60, 0.67,            
        -0.68, 0.67,
        -0.64, 0.7392820323,

        //Triangle-1
        -0.68, 0.67,
        -0.7, 0.58,
        -0.7679422, 0.642320508,
        
        //Triangle-2
        -0.7, 0.58,
        -0.64, 0.53,
        -0.7133012701892, 0.50303847,

        //Triangle-3
        -0.64, 0.53,
        -0.58, 0.58,
        -0.56669872, 0.50303847,

        //Triangle-4
        -0.60, 0.67,    
        -0.58, 0.58,
        -0.5120577136594, 0.64232050
    };

    return PointsStar;
}