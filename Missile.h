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
#include "dataCollection.h"

using namespace std;

class Missile
{
public:
    GLuint vertexArrayObject;
    GLuint shaderProgramID;
    GLuint positionVertexBufferObjectID, normalVertexBufferObjectID, uvVertexBufferObjectID;
    GLuint positionElementBufferObject;
    Object obj;

    double _xMove = 0.0;
    double _zMove = 0.0;
    glm::vec3 _Color = glm::vec3(1.0, 0.0, 0.0);
    dataCollection dc;

    Missile(double xMove, double zMove) : _xMove(xMove), _zMove(zMove) {}

    void makingMissile();

    bool initShaderProgram();

    bool initShaderProgram_noTex();

    bool defineVertexArrayObject();
};

