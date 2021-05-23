#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../Headers/VertexShaderInit.hpp"
#include "../Headers/FragmentShaderInit.hpp"
#include "../Headers/Events.hpp"
#include "../Headers/Circle.hpp"
#include "../Headers/Transformations.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void){

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow *window = glfwCreateWindow(800, 800, "Solar system", NULL, NULL);
    glfwMakeContextCurrent(window);
    GLint GlewInitResult = glewInit();

    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    ShaderSourceVertex(vertex);
    ShaderSourceFragment(fragment);

    CompileVertexShader(vertex);
    CompileFragmentShader(fragment);

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    //----------------------------Creating circles----------------------------

    vector<Coordenadas>concatenateVertices;
    int num_vertices = 32;
    float pi = 3.14;
    float radius = 0.20;
    float angle = 0.0;
    Coordenadas center;
    
    CircleShape circleShape;

    center.x = 0.5; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, radius, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.0; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, radius, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.0; center.y = 0.5;
    circleShape = CreateCircle(num_vertices, radius, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());


    center.x = 0.0; center.y = -0.5;
    circleShape = CreateCircle(num_vertices, radius, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = -0.5; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, radius, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());


    //------------------------------------------------------------------------

    Coordenadas vertices[num_vertices*5];
    copy(concatenateVertices.begin(), concatenateVertices.end(), vertices);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *)0);

    GLint loc_color = glGetUniformLocation(program, "color");

    CreateKeyboardKeys(0.0, 0.0);
    SetKeyboardEvent(window);

    Keys keys = GetKeyboardKeys();

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        keys = GetKeyboardKeys();

        float transformMatrixTranslation[16];
        vector<float>matrixTranslation = CreateMatrixTranslation(keys.t_x, keys.t_y);
        copy(matrixTranslation.begin(), matrixTranslation.end(), transformMatrixTranslation);

        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixTranslation);
        
        glUniform4f(loc_color, 0.0, 0.5, 0.0, 1.0);      
        glDrawArrays(GL_TRIANGLE_FAN, 0, 32);

        glUniform4f(loc_color, 0.5, 0.0, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 32, 32);

        glUniform4f(loc_color, 0.0, 0.0, 0.5, 1.0);  
        glDrawArrays(GL_TRIANGLE_FAN, 64, 32);
        
        glUniform4f(loc_color, 0.5, 0.5, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 96, 32);

        glUniform4f(loc_color, 0.0, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 128, 32);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}
