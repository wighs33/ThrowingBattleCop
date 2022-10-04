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

class Robot
{
public:
    double _xMove = 0.0;
    double _zMove = 0.0;
    double _yMove = 0.0;
    float xRotate_armAndLeg = 0.0f;
    float yRotate_direction = 0.0f;
    int comDir = 0;
    bool isPlus_armAndLegRotate = true;
    bool isStoned = false;
    bool isMoveToStone = false;
    bool isComCatchFail = true;
    Cube cube[8];
    dataCollection dc;
    glm::vec3 _Color = glm::vec3(1.0, 0.0, 0.0);
    glm::vec3 noseColor = glm::vec3(0.0, 0.0, 0.0);

    Robot(double xMove, double zMove, glm::vec3 robotColor) : _xMove(xMove), _zMove(zMove), _Color(robotColor){}

    void makingRobot();
};

