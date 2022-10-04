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

class Stone
{
public:
    double _xMove = 0.0;
    double _yMove = 0.0;
    double _zMove = 0.0;
    double _scale = 0.5;
    bool isCatch = false;
    bool isComCatch = false;
    bool isThrowOn_front = false;
    bool isThrowOn_back = false;
    bool isThrowOn_left = false;
    bool isThrowOn_right = false;
    bool isThrowToMainRobot = false;
    bool isTarget = false;
    double dMainRobotPosX = 0.0;
    double dMainRobotPosZ = 0.0;
    int throwIndex;
    Cube cube;
    dataCollection dc;

    Stone(double xMove, double zMove): _xMove(xMove),_zMove(zMove){}

    void makingStone();
};

