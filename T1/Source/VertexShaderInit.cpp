#include "../Headers/VertexShaderInit.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

char const *vertex_code =
    "attribute vec2 position;\n"
    "uniform mat4 transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transformation*vec4(position, 0.0, 1.0);\n"
    "}\n";

void ShaderSourceVertex(GLuint vertex){

    glShaderSource(vertex, 1, &vertex_code, NULL);
}

void CompileVertexShader(GLuint vertex){

    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE){

        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        printf("Erro de compilacao no Vertex Shader.\n");
    }
}