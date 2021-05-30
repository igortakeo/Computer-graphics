#include "../Headers/Transformations.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

vector<float> CreateMatrixTranslation(float t_x, float t_y){

    vector<float> MatTranslation
    {
        1.0, 0.0, 0.0, t_x,
        0.0, 1.0, 0.0, t_y,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 
    };

    return MatTranslation;
}

vector<float> CreateMatrixScale(float t_x, float t_y){

    vector<float> MatScale
    {
        t_x, 0.0, 0.0, 0.0,
        0.0, t_y, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 
    };

    return MatScale;
}
vector<float> CreateMatrixScaleReferencePoint(float t_x, float t_y, float p_x, float p_y){

    vector<float> MatScale
    {
        t_x, 0.0, 0.0, p_x*(1-t_x),
        0.0, t_y, 0.0, p_y*(1-t_y),
        0.0, 0.0, 1.0,         0.0,
        0.0, 0.0, 0.0,         1.0 
    };

    return MatScale;
}

vector<float> CreateMatrixRotation(float t_x){

    vector<float> MatRotation
    {
        cos(t_x), -sin(t_x), 0.0, 0.0,
        sin(t_x),  cos(t_x), 0.0, 0.0,
             0.0,       0.0, 1.0, 0.0,
             0.0,       0.0, 0.0, 1.0
    };

    return MatRotation;
}

vector<float> CreateMatrixRotationReferencePoint(float t_x, float p_x, float p_y){

    vector<float> MatRotation
    {
        cos(t_x), -sin(t_x), 0.0, p_x-p_x*cos(t_x)+p_y*sin(t_x),
        sin(t_x),  cos(t_x), 0.0, p_y-p_y*cos(t_x)-p_x*sin(t_x),
             0.0,       0.0,                            1.0, 0.0,
             0.0,       0.0,                            0.0, 1.0
    };

    return MatRotation;
}

vector<float> Multiplication(vector<float> m1, vector<float>m2){

    float m_a[4][4];
    float m_b[4][4];
    float m_c[4][4];
    vector<float> m_result(16);

    int n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_a[i][j] = m1[n];
            m_b[i][j] = m2[n];
            n += 1;
        }
    }


    for(int i=0;i<4;i++){    
        for(int j=0;j<4;j++){
            m_c[i][j]=0.0;
            for(int k=0; k < 4; k++){
                m_c[i][j] += m_a[i][k]*m_b[k][j];    
            }
        }
    }

    n = 0;
    for(int i=0; i < 4; i++){
        for(int j=0; j < 4; j++){
            m_result[n] = m_c[i][j];
            n += 1;
        }
    }

    return m_result;
}