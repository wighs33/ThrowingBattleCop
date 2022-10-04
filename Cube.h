#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Object.h"

using namespace std;

class Cube
{
public:
    GLuint vertexArrayObject;
    GLuint shaderProgramID;
    GLuint positionVertexBufferObjectID, normalVertexBufferObjectID, uvVertexBufferObjectID;
    GLuint positionElementBufferObject;
    Object obj;
    int face = 0;
    double CUBE_EDGE_LENGTH = 1.0;

    bool initShaderProgram();

    bool initShaderProgram_noTex();

    bool defineVertexArrayObject_face();

    bool defineVertexArrayObject_all();

    bool defineVertexArrayObject_noTex();
};

