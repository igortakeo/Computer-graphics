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
#include "../Headers/Coordinates.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#define CENTER_X -0.64
#define CENTER_Y 0.62

using namespace std;
using namespace this_thread;
using namespace chrono;

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

typedef struct colorCodes{
    float R;
    float G;
    float B;
}ColorCodes;

typedef struct translationVariable{
    float tv_1;
    float tv_2;
}TranslationVariable;

typedef struct scaleVariable{
    float sv_1;
    float sv_2;
}ScaleVariable;

typedef struct coordinatesToDraw{
    GLint Planet;
    GLint Orbits;
    GLint Star;
    GLint MiniStar;
}CoordinatesToDraw;

CoordinatesToDraw coordinatesToDraw;

void InitializeCoordinates(){
    
    coordinatesToDraw.Planet = 0;
    coordinatesToDraw.Orbits = 288;
    coordinatesToDraw.Star = 544;
    coordinatesToDraw.MiniStar = 624;
}

void ResetTeta(
    GLuint program,
    GLint loc){

    float transformation[16];

    vector<float> matrixRotation = CreateMatrixRotation(0.0);
    copy(matrixRotation.begin(), matrixRotation.end(), transformation);
    loc = glGetUniformLocation(program, "transformation");
    glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);
}

void DrawingPlanets(
    Keys keys_keyboard,
    GLuint program,
    GLint loc_color,
    GLint loc,
    ColorCodes color,
    int planetNumber,
    float teta){

    float transformation[16];

    if(planetNumber == 0){
        
        keys_keyboard = GetKeyboardKeys();
        vector<float> matrixScale= CreateMatrixScaleReferencePoint(keys_keyboard.t_x4, keys_keyboard.t_y4, 0.0, -0.1);
        copy(matrixScale.begin(), matrixScale.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);
    }
    else{
        
        vector<float> matrixRotation = CreateMatrixRotationReferencePoint(teta, 0.0, -0.1);
        copy(matrixRotation.begin(), matrixRotation.end(), transformation);
        loc = glGetUniformLocation(program, "transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);
    }

    glUniform4f(loc_color, color.R, color.G, color.B, 1.0);

    int coord = coordinatesToDraw.Planet + planetNumber*32;
    glDrawArrays(GL_TRIANGLE_FAN, coord, 32);
}

void DrawingMiniStar(
    GLuint program,
    GLint loc_color,
    GLint loc,
    ColorCodes color,
    TranslationVariable translation_v,
    int starNumber){
    
    float transformation[16];

    vector<float> matrixTranslation = CreateMatrixTranslation(translation_v.tv_1, translation_v.tv_2);

    vector<float> matrixScale = CreateMatrixScaleReferencePoint(0.2, 0.2, CENTER_X, CENTER_Y);

    vector<float> responseMult = Multiplication(matrixTranslation, matrixScale);
    copy(responseMult.begin(), responseMult.end(), transformation);
    loc = glGetUniformLocation(program, "transformation");
    glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

    glUniform4f(loc_color, color.R, color.G, color.B, 1.0);

    int coord = coordinatesToDraw.MiniStar + starNumber*20;
    glDrawArrays(GL_TRIANGLE_FAN, coord, 5);
    glDrawArrays(GL_TRIANGLES, coord+5, 15);
}

void DrawingStar(
    Keys keys_mouse,
    Keys keys_keyboard,
    GLuint program,
    GLint loc_color,
    GLint loc,
    ColorCodes color,
    TranslationVariable translation_v,
    ScaleVariable scale_v,
    int starNumber){
    
    float t_x, t_y;
    vector<float> matrixTranslation;

    keys_keyboard = GetKeyboardKeys();

    if(starNumber == 0){ 
        matrixTranslation = CreateMatrixTranslation(
            keys_keyboard.t_x0 + translation_v.tv_1, 
            keys_keyboard.t_y0 + translation_v.tv_2);
    }
    else if(starNumber == 1){
        matrixTranslation = CreateMatrixTranslation(
            keys_keyboard.t_x1 + translation_v.tv_1, 
            keys_keyboard.t_y1 + translation_v.tv_2);
    }
    else if(starNumber == 2){
       matrixTranslation = CreateMatrixTranslation(
            keys_keyboard.t_x2 + translation_v.tv_1, 
            keys_keyboard.t_y2 + translation_v.tv_2);
    }
    else if(starNumber == 3){
       matrixTranslation = CreateMatrixTranslation(
            keys_keyboard.t_x3 + translation_v.tv_1, 
            keys_keyboard.t_y3 + translation_v.tv_2);    
    }

    float transformation[16];

    vector<float> matrixRotation = CreateMatrixRotationReferencePoint(keys_keyboard.t_x5, CENTER_X, CENTER_Y);

    keys_mouse = GetMouseKeys();
    vector<float> matrixScale = CreateMatrixScaleReferencePoint(keys_mouse.t_x + scale_v.sv_1, keys_mouse.t_y + scale_v.sv_2, CENTER_X, CENTER_Y);

    vector<float> responseMult = Multiplication(matrixTranslation, matrixScale);
    responseMult = Multiplication(responseMult, matrixRotation);
    copy(responseMult.begin(), responseMult.end(), transformation);
    loc = glGetUniformLocation(program, "transformation");
    glUniformMatrix4fv(loc, 1, GL_TRUE, transformation);

    glUniform4f(loc_color, color.R, color.G, color.B, 1.0);
   
    int coord = coordinatesToDraw.Star + starNumber*20;
    glDrawArrays(GL_TRIANGLE_FAN, coord, 5);
    glDrawArrays(GL_TRIANGLES, coord+5, 15);
}

void DrawingOrbits(
    GLint loc_color,
    int orbitNumber){

    int coord = coordinatesToDraw.Orbits + orbitNumber*32;
    glUniform4f(loc_color, 0.5, 0.5, 0.5, 1.0);      
    glDrawArrays(GL_LINE_STRIP, coord, 32);
}

vector<Coordinates> ChangeToCoordinates(
    vector<float>coord){
    
    vector<Coordinates> pointsStar;
    
    for(int i=0; i<coord.size(); i+=2){
        Coordinates a;
        a.x = coord[i];
        a.y = coord[i+1];
        pointsStar.push_back(a);
    }

    return pointsStar;
}

vector<Coordinates> CreatePlanets(
    Coordinates center, 
    const int num_vertices, 
    const float angle){

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

void CreateTranslationRadious(
    vector<Coordinates> &concatenateVertices, 
    const int num_vertices, 
    const float angle){

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

    InitializeCoordinates();

    // Variables declaration
    ColorCodes color;
    TranslationVariable translation_v;
    ScaleVariable scale_v;
    Keys keys_mouse, keys_keyboard;   
    float teta_0 = 90.0; 
    float teta_1 = 90.0; 
    float teta_2 = 90.0;
    float teta_3 = 90.0; 
    float teta_4 = 90.0; 
    float teta_5 = 90.0; 
    float teta_6 = 90.0; 
    float teta_7 = 90.0; 
    float teta_8 = 90.0;

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        
        //Orbits
        for(int i=0; i<8; i++) DrawingOrbits(loc_color, i);

        //Star-0
        color.R = 1.0; color.G = 0.57254902; color.B = 0.16078431;       
        translation_v.tv_1 = 0.0; translation_v.tv_2 = 0.0;
        scale_v.sv_1 = 0.0; scale_v.sv_2 = 0.0;
        DrawingStar(keys_mouse, keys_keyboard, program, loc_color, loc, color, translation_v, scale_v, 0);

        //Star-1
        color.R = 0.6; color.G = 0.15; color.B = 0.0;
        translation_v.tv_1 = 1.33; translation_v.tv_2 = 0.0;
        scale_v.sv_1 = -0.64+0.44; scale_v.sv_2 = -0.64+0.44;
        DrawingStar(keys_mouse, keys_keyboard, program, loc_color, loc, color, translation_v, scale_v, 1);

        //Star-2
        color.R = 0.780392157; color.G = 0.847058824; color.B = 1.0;
        translation_v.tv_1 = -0.02; translation_v.tv_2 = -1.44;
        scale_v.sv_1 = -0.64+0.34; scale_v.sv_2 = -0.64+0.34;
        DrawingStar(keys_mouse, keys_keyboard, program, loc_color, loc, color, translation_v, scale_v, 2);

        //Star-3
        color.R = 0.270588235; color.G = 0.000705882; color.B = 1.0;
        translation_v.tv_1 = 1.35; translation_v.tv_2 = -1.43;
        scale_v.sv_1 = -0.64+0.3; scale_v.sv_2 = -0.64+0.3;
        DrawingStar(keys_mouse, keys_keyboard, program, loc_color, loc, color, translation_v, scale_v, 3);
        
        //Color to ministars
        color.R = 1.0; color.G = 0.874509804; color.B = 0.0;

        //Ministar-0
        translation_v.tv_1 = 0.56; translation_v.tv_2 = -0.47;
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 0);

        //Ministar-1
        translation_v.tv_1 = 0.31; translation_v.tv_2 = -0.4;  
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 1);

        //Ministar-2
        translation_v.tv_1 = 1.1; translation_v.tv_2 = -0.42;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 2);

        //Ministar-3
        translation_v.tv_1 = 0.63; translation_v.tv_2 = -1.26;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 3);

        //Ministar-4
        translation_v.tv_1 = -0.059999; translation_v.tv_2 = -0.97999;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 4);
        
        //Ministar-5
        translation_v.tv_1 = 0.56; translation_v.tv_2 = 0.02;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 5);

        //Ministar-6
        translation_v.tv_1 = 0.969999; translation_v.tv_2 = -0.78;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 6);
        
        //Ministar-7
        translation_v.tv_1 = 1.24; translation_v.tv_2 = -1.18;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 7);

        //Ministar-8
        translation_v.tv_1 = 0.53; translation_v.tv_2 = -1.04;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 8);
        
        //Ministar-9
        translation_v.tv_1 = 1.12; translation_v.tv_2 = -0.16;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 9);

        //Ministar-10
        translation_v.tv_1 = 0.0300001; translation_v.tv_2 = -0.28;        
        DrawingMiniStar(program, loc_color, loc, color, translation_v, 10);
        
        //Planet-0
        color.R = 0.8; color.G = 0.8; color.B = 0.0;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 0, teta_0);

        //Planet-1
        color.R = 0.6; color.G = 0.15; color.B = 0.0;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 1, teta_1);
        
        //Planet-2
        color.R = 0.7; color.G = 0.7; color.B = 0.7;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 2, teta_2);

        //Planet-3
        color.R = 0.0; color.G = 0.0; color.B = 0.8;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 3, teta_3);

        //Planet-4
        color.R = 0.8; color.G = 1.0; color.B = 0.0;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 4, teta_4);

        //Planet-5
        color.R = 0.5; color.G = 0.5; color.B = 0.5;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 5, teta_5);

        //Planet-6
        color.R = 0.8; color.G = 0.4; color.B = 0.0;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 6, teta_6);

        //Planet-7
        color.R = 0.0; color.G = 0.0; color.B = 0.4;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 7, teta_7);

        //Planet-8
        color.R = 0.1; color.G = 0.1; color.B = 0.4;
        DrawingPlanets(keys_keyboard, program, loc_color, loc, color, 8, teta_8);
        
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
        ResetTeta(program, loc);
        
        sleep_for(milliseconds(100));

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    exit(EXIT_SUCCESS);
}
