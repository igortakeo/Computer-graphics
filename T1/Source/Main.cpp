#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../Headers/VertexShaderInit.hpp"
#include "../Headers/FragmentShaderInit.hpp"
#include "../Headers/Events.hpp"
#include <iostream>

using namespace std;

// variaveis globais
typedef struct{
    float x, y;
} coordenadas;

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

    // Preparando dados para enviar a GPU
    coordenadas vertices[32];

    int num_vertices = 32;
    float pi = 3.14;
    float counter = 0;
    float radius = 0.20;
    float angle = 0.0;
    float x, y;
    for (int i = 0; i < num_vertices; i++){
        angle += (2.0 * pi) / (float)num_vertices;
        x = cos(angle) * radius;
        y = sin(angle) * radius;
        coordenadas c;
        c.x = x;
        c.y = y;
        vertices[i] = c;
    }

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *)0);

    CreateKeyboardKeys(0.0, 0.0);
    SetKeyboardEvent(window);

    Keys keys = GetKeyboardKeys();

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        
        keys = GetKeyboardKeys();

        float s_x = keys.t_x, s_y = keys.t_y;

        float mat_translation[16] = {
            1.0f, 0.0f, 0.0f, s_x,
            0.0f, 1.0f, 0.0f, s_y,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f};

        // enviando a matriz de transformacao para a GPU, vertex shader, variavel mat_transformation
        loc = glGetUniformLocation(program, "mat_Mult");
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_translation);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 32);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}
