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
#include "../Headers/Star.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#define CENTER_X -0.64
#define CENTER_Y 0.62

using namespace std;

/*
    //Commands

    W,A,S,D: Translation of orange star
    T,F,G,H: Translation of red star
    J,K,L,I: Translation of white star
    Z: Rotation of 4 border stars
    Arrows: Translation of purple star

    + and -: Scale of sun
    Mouse button left and button right: Scale of stars

*/


vector<Coordinates> ChangeToCoordinates(vector<float>coord){
    
    vector<Coordinates> pointsStar;
    
    for(int i=0; i<coord.size(); i+=2){
        Coordinates a;
        a.x = coord[i];
        a.y = coord[i+1];
        pointsStar.push_back(a);
    }

    return pointsStar;
}

vector<Coordinates> CreatePlanets(Coordinates center, const int num_vertices, const float angle){

    CircleShape circleShape;
    vector<Coordinates>concatenateVertices;

    center.x = 0.0; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.06, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.1; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.02, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.2; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.04, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.3; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.04, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.4; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.03, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.5; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.05, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.6; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.04, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
    
    center.x = 0.7; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.03, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    center.x = 0.8; center.y = -0.1;
    circleShape = CreateCircle(num_vertices, 0.03, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());

    return concatenateVertices;

}

void CreateTranslationRadious(vector<Coordinates> &concatenateVertices, const int num_vertices, const float angle){

    CircleShape circleShape;
    Coordinates center;
    center.x = 0.0;
    center.y = -0.1;
         
    circleShape = CreateCircle(num_vertices, 0.1, angle, center);
    concatenateVertices.insert(concatenateVertices.end(), circleShape.vertices.begin(), circleShape.vertices.end());
    
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

    vector<Coordinates> concatenateVertices;
    const int num_vertices = 32;
    const float angle = 0.0;
    Coordinates center;

    concatenateVertices = CreatePlanets(center, num_vertices, angle);
    CreateTranslationRadious(concatenateVertices, 32, 0.0);
    
    //------------------------------------------------------------------------

    //----------------------------Creating stars----------------------------
    
    //Star-1
    vector<float>coord = CreateStars();
    vector<Coordinates> pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Star-2
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Star-3
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Star-4
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-1
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-2
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-3
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-4
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-5
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-6
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-7
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //Ministar-8
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());
    
    //Ministar-9
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());
    
    //Ministar-10
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());
    
    //Ministar-11
    coord = CreateStars();
    pointsStar = ChangeToCoordinates(coord);
    concatenateVertices.insert(concatenateVertices.end(), pointsStar.begin(), pointsStar.end());

    //------------------------------------------------------------------------


    Coordinates vertices[concatenateVertices.size()];
    copy(concatenateVertices.begin(), concatenateVertices.end(), vertices);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *)0);

    GLint loc_color = glGetUniformLocation(program, "color");

    CreateMouseKeys(0.62, 0.62);
    CreateKeyboardKeys(0.0, 0.0);
    SetMouseEvent(window);
    SetKeyboardEvent(window);

    Keys keys_mouse, keys_keyboard;

    float transformMatrixRotation[16];
    float transformMatrixScale[16];
    float transformMatrixTranslation[16];
    float transformation[16];

    float teta_0 = 90.0, teta_1 = 90.0, teta_2 = 90.0, teta_3 = 90.0, teta_4 = 90.0, teta_5 = 90.0, teta_6 = 90.0, teta_7 = 90.0, teta_8 = 90.0;

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        //*******Drawing orbits*******

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

        //*******Drawing stars*******
        
        //Star-1
        keys_keyboard = GetKeyboardKeys();
        vector<float> matrixTranslation = CreateMatrixTranslation(keys_keyboard.t_x0, keys_keyboard.t_y0);
        vector<float> matrixRotation = CreateMatrixRotationReferencePoint(keys_keyboard.t_x5, CENTER_X, CENTER_Y);

        keys_mouse = GetMouseKeys();
        vector<float> matrixScale = CreateMatrixScaleReferencePoint(keys_mouse.t_x, keys_mouse.t_y, CENTER_X, CENTER_Y);

        vector<float> responseMult = Multiplication(matrixTranslation, matrixScale);
        responseMult = Multiplication(responseMult, matrixRotation);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.57254902, 0.160784314, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 544, 5);
        glDrawArrays(GL_TRIANGLES, 549, 15);
        
        //Star-2
        keys_keyboard = GetKeyboardKeys();
        matrixTranslation = CreateMatrixTranslation(keys_keyboard.t_x1+1.33, keys_keyboard.t_y1+0.0);
        matrixRotation = CreateMatrixRotationReferencePoint(keys_keyboard.t_x5, CENTER_X, CENTER_Y);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(keys_mouse.t_x-0.64+0.44, keys_mouse.t_y-0.64+0.44, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        responseMult = Multiplication(responseMult, matrixRotation);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 0.6, 0.15, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 564, 5);
        glDrawArrays(GL_TRIANGLES, 569, 15);

        //Star-3
        keys_keyboard = GetKeyboardKeys();
        matrixTranslation = CreateMatrixTranslation(keys_keyboard.t_x2-0.02, keys_keyboard.t_y2-1.44);
        matrixRotation = CreateMatrixRotationReferencePoint(keys_keyboard.t_x5, CENTER_X, CENTER_Y);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(keys_mouse.t_x-0.64+0.34, keys_mouse.t_y-0.64+0.34, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        responseMult = Multiplication(responseMult, matrixRotation);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 0.780392157, 0.847058824, 1.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 584, 5);
        glDrawArrays(GL_TRIANGLES, 589, 15);

        //Star-4
        keys_keyboard = GetKeyboardKeys();
        matrixTranslation = CreateMatrixTranslation(keys_keyboard.t_x3+1.35, keys_keyboard.t_y3-1.43);
        matrixRotation = CreateMatrixRotationReferencePoint(keys_keyboard.t_x5, CENTER_X, CENTER_Y);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(keys_mouse.t_x-0.64+0.3, keys_mouse.t_y-0.64+0.3, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        responseMult = Multiplication(responseMult, matrixRotation);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 0.270588235, 0.000705882, 1.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 604, 5);
        glDrawArrays(GL_TRIANGLES, 609, 15);

        //Ministar-1
        matrixRotation = CreateMatrixRotation(1.0);
        matrixTranslation = CreateMatrixTranslation(0.56, -0.47);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 624, 5);
        glDrawArrays(GL_TRIANGLES, 629, 15);

        //Ministar-2
        matrixTranslation = CreateMatrixTranslation(0.31, -0.4);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 644, 5);
        glDrawArrays(GL_TRIANGLES, 649, 15);

        //Ministar-3
        matrixTranslation = CreateMatrixTranslation(1.1, -0.42);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 664, 5);
        glDrawArrays(GL_TRIANGLES, 669, 15);

        //Ministar-4
        matrixTranslation = CreateMatrixTranslation(0.63, -1.26);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 684, 5);
        glDrawArrays(GL_TRIANGLES, 689, 15);

        //Ministar-5
        matrixTranslation = CreateMatrixTranslation(-0.059999, -0.97999);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 704, 5);
        glDrawArrays(GL_TRIANGLES, 709, 15);
        
        //Ministar-6
        matrixTranslation = CreateMatrixTranslation(0.56, 0.02);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 724, 5);
        glDrawArrays(GL_TRIANGLES, 729, 15);
        
        //Ministar-7
        matrixTranslation = CreateMatrixTranslation(0.969999, -0.78);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 744, 5);
        glDrawArrays(GL_TRIANGLES, 749, 15);
        
        //Ministar-8
        matrixTranslation = CreateMatrixTranslation(1.24, -1.18);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 764, 5);
        glDrawArrays(GL_TRIANGLES, 769, 15);

        //Ministar-9
        matrixTranslation = CreateMatrixTranslation(0.53, -1.04);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 784, 5);
        glDrawArrays(GL_TRIANGLES, 789, 15);
        
        //Ministar-10
        matrixTranslation = CreateMatrixTranslation(1.12, -0.16);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 804, 5);
        glDrawArrays(GL_TRIANGLES, 809, 15);
        
        //Ministar-11
        matrixTranslation = CreateMatrixTranslation(0.0300001, -0.28);

        keys_mouse = GetMouseKeys();
        matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

        responseMult = Multiplication(matrixTranslation, matrixScale);
        copy(responseMult.begin(), responseMult.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

        glUniform4f(loc_color, 1.0, 0.874509804, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 804, 5);
        glDrawArrays(GL_TRIANGLES, 829, 15);
        
        //*******Drawing planets*******
        
        //Planet-0
        keys_keyboard = GetKeyboardKeys();
        matrixScale= CreateMatrixScaleReferencePoint(keys_keyboard.t_x4, keys_keyboard.t_y4, 0.0, -0.1);
        copy(matrixScale.begin(), matrixScale.end(), transformMatrixScale);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixScale);

        glUniform4f(loc_color, 0.8, 0.8, 0.0, 1.0);      
        glDrawArrays(GL_TRIANGLE_FAN, 0, 32);


        //Planet-1
        matrixRotation = CreateMatrixRotationReferencePoint(teta_1, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);
        
        glUniform4f(loc_color, 0.6, 0.15, 0.0, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 32, 32);

        
        //Planet-2
        matrixRotation = CreateMatrixRotationReferencePoint(teta_2, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.7, 0.7, 0.7, 1.0);  
        glDrawArrays(GL_TRIANGLE_FAN, 64, 32);
        

        //Planet-3
        matrixRotation = CreateMatrixRotationReferencePoint(teta_3, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.0, 0.0, 0.8, 1.0);
        glDrawArrays(GL_TRIANGLE_FAN, 96, 32);


        //Planet-4
        matrixRotation = CreateMatrixRotationReferencePoint(teta_4, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.8, 0.1, 0.0, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 128, 32);

        //Planet-5
        matrixRotation = CreateMatrixRotationReferencePoint(teta_5, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 160, 32);

        //Planet-6
        matrixRotation = CreateMatrixRotationReferencePoint(teta_6, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.8, 0.4, 0.0, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 192, 32);


        //Planet-7
        matrixRotation = CreateMatrixRotationReferencePoint(teta_7, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformMatrixRotation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformMatrixRotation);

        glUniform4f(loc_color, 0.0, 0.0, 0.4, 1.0);        
        glDrawArrays(GL_TRIANGLE_FAN, 224, 32);


        //Planet-8
        matrixRotation = CreateMatrixRotationReferencePoint(teta_8, 0.0, -0.1);
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
