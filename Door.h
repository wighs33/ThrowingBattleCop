#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "dataCollection.h"
#include "Cube.h"

class Door
{
public:
    double floorSize = 30.0;
    glm::vec3 _Color = glm::vec3(0.0, 0.0, 0.0);
    Cube cube;
    dataCollection dc;

    void makingDoor();
};
