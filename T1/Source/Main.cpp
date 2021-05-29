#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <chrono>
#include <thread>
#include "../Headers/VertexShaderInit.hpp"
#include "../Headers/FragmentShaderInit.hpp"
#include "../Headers/Events.hpp"
#include "../Headers/Circle.hpp"
#include "../Headers/Transformations.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<Coordenadas> CreatePlanets(Coordenadas center, const int num_vertices, const float angle){

    CircleShape circleShape;
    vector<Coordenadas>concatenateVertices;

    center.x = 0.0; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.08, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.2; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.02, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.3; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.04, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.4; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.04, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.5; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.03, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.6; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.05, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.7; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.04, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
    
    center.x = 0.8; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.03, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.9; center.y = 0.0;
    circleShape = CreateCircle(num_vertices, 0.03, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    return concatenateVertices;

}

void CreateTranslationRadious(vector<Coordenadas> &concatenateVertices, const int num_vertices, const float angle){

    CircleShape circleShape;
    Coordenadas center;
    center.x = 0.0;
    center.y = 0.0;
         
    circleShape = CreateCircle(num_vertices, 0.2, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
    
    circleShape = CreateCircle(num_vertices, 0.3, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
     
    circleShape = CreateCircle(num_vertices, 0.4, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
     
    circleShape = CreateCircle(num_vertices, 0.5, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
     
    circleShape = CreateCircle(num_vertices, 0.6, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
     
    circleShape = CreateCircle(num_vertices, 0.7, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
      
    circleShape = CreateCircle(num_vertices, 0.8, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
     
    circleShape = CreateCircle(num_vertices, 0.9, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
    
}


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

    vector<Coordenadas> concatenateVertices;
    const int num_vertices = 32;
    const float angle = 0.0;
    Coordenadas center;

    concatenateVertices = CreatePlanets(center, num_vertices, angle);
    CreateTranslationRadious(concatenateVertices, 32, 0.0);
    
    //------------------------------------------------------------------------

    Coordenadas vertices[num_vertices*17];
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

    float transformMatrixRotation[16];
    float teta_0 = 90.0, teta_1 = 90.0, teta_2 = 90.0, teta_3 = 90.0, teta_4 = 90.0, teta_5 = 90.0, teta_6 = 90.0, teta_7 = 90.0, teta_8 = 90.0;

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        keys = GetKeyboardKeys();

        //Desenhando Raios de Translacao (orbita) dos planetas
        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);      
        glDrawArrays(GL_LINE_STRIP, 288, 32);
        
        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);
        glDrawArrays(GL_LINE_STRIP, 320, 32);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);  
        glDrawArrays(GL_LINE_STRIP, 352, 32);
        
        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);
        glDrawArrays(GL_LINE_STRIP, 384, 32);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_LINE_STRIP, 416, 32);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_LINE_STRIP, 448, 32);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_LINE_STRIP, 480, 32);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_LINE_STRIP, 512, 32);


        //Desennhado planetas
        

        //--------------------------------------------------------
        
        //Planet-0
        vector<float> matrixRotation = CreateMatrixRotation(teta_0);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);


        glUniform4f(loc_color, 0.8, 0.8, 0.0, 1.0);      
        glDrawArrays(GL_TRIANGLE_FAN, 0, 32);


        //Planet-1
        matrixRotation = CreateMatrixRotation(teta_1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);
        
        glUniform4f(loc_color, 0.6, 0.15, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 32, 32);

        
        //Planet-2
        matrixRotation = CreateMatrixRotation(teta_2);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.7, 0.7, 0.7, 1.0);  
        glDrawArrays(GL_TRIANGLE_FAN, 64, 32);
        

        //Planet-3
        matrixRotation = CreateMatrixRotation(teta_3);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.0, 0.0, 0.8, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 96, 32);


        //Planet-4
        matrixRotation = CreateMatrixRotation(teta_4);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.8, 0.1, 0.0, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 128, 32);

        //Planet-5
        matrixRotation = CreateMatrixRotation(teta_5);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 160, 32);

        //Planet-6
        matrixRotation = CreateMatrixRotation(teta_6);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.8, 0.4, 0.0, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 192, 32);


        //Planet-7
        matrixRotation = CreateMatrixRotation(teta_7);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.0, 0.0, 0.4, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 224, 32);


        //Planet-8
        matrixRotation = CreateMatrixRotation(teta_8);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.1, 0.1, 0.4, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 256, 32);


        teta_0 += 0.8;
        teta_1 -= 0.6;
        teta_2 += 0.5;
        teta_3 -= 0.4;
        teta_4 += 0.3;
        teta_5 -= 0.2;
        teta_6 += 0.1;
        teta_7 -= 0.1;
        teta_8 -= 0.05;

        //Reseting teta in order to keep planets orbit stopped
        matrixRotation = CreateMatrixRotation(0.0);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        this_thread::sleep_for(chrono::milliseconds(100));

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}
