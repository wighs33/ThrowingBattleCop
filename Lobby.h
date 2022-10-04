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

class Lobby
{
public:
    double _xMove = 0.0;
    double _zMove = 0.0;
    double _scale = 10.0;
    Cube cube;
    dataCollection dc;

    Lobby(double xMove, double zMove) : _xMove(xMove), _zMove(zMove) {
    }

    void makingLobby();
};




