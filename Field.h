#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "dataCollection.h"
#include "Cube.h"

class Field
{
public:
    double floorSize = 30.0;
    Cube cube;
    dataCollection dc;

    Field(int face) {
        cube.face = face;
    }

    void makingField();
};

