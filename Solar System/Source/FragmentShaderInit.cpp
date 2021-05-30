#include "../Headers/FragmentShaderInit.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

char const *fragment_code =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

void ShaderSourceFragment(GLuint fragment){

    glShaderSource(fragment, 1, &fragment_code, NULL);
}

void CompileFragmentShader(GLuint fragment){

    glCompileShader(fragment);

    GLint isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE){

        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        printf("Erro de compilacao no Fragment Shader.\n");
    }
}