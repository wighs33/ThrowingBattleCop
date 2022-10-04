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

#define WINDOW_WITDH	800
#define WINDOW_HEIGHT	600

#define CAMERA_POS		glm::vec3(0.0, 0.0, 10.0)
#define OBJECT_COLOR	glm::vec3(1.0, 1.0, 1.0)
#define LIGHT_AMBIENT	glm::vec3(0.5, 0.5, 0.5)
#define LIGHT_POS		glm::vec3(3.0, 3.0, 0.0)
#define LIGHT_COLOR		glm::vec3(1.0, 1.0, 1.0)

struct dataCollection {
	//bool isFirstPersonView = false;
	double cameraX = 20.0;
	double cameraY = 5.0;
	double cameraZ = 5.0;
	float cameraRot = 0.0f;
	float cameraRev = 0.0f;

	glm::vec4 cameraPos;

	void cameraPosSetting() {
		cameraPos = glm::vec4(CAMERA_POS + glm::vec3(cameraX, cameraY, cameraZ), 1.0);
		cameraPos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.0, 0.0)) * cameraPos;
		//cameraPos = isFirstPersonView ? glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -9.9)) * cameraPos : glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.0, 0.0)) * cameraPos;
	}

	glm::mat4 view;

	void viewSetting() {
		view = glm::lookAt(glm::vec3(cameraPos), glm::vec3(cameraX, cameraY/2, cameraZ), glm::vec3(0.0, 1.0, 0.0));
		view = glm::rotate(view, glm::radians(cameraRev), glm::vec3(0.0, 1.0, 0.0));
		view = glm::translate(view, glm::vec3(cameraX, 0.0, cameraZ + 10.0));
		//view = isFirstPersonView ? glm::translate(view, glm::vec3(cameraX, 0.0, cameraZ + 0.3)) : glm::translate(view, glm::vec3(cameraX, 0.0, cameraZ + 9.0));
		view = glm::rotate(view, glm::radians(cameraRot), glm::vec3(0.0, 1.0, 0.0));
		view = glm::translate(view, glm::vec3(-cameraX, 0.0, -cameraZ - 10.0));
		//view = isFirstPersonView ? glm::translate(view, glm::vec3(-cameraX, 0.0, -cameraZ - 1.1)) : glm::translate(view, glm::vec3(-cameraX, 0.0, -cameraZ - 9.0));
	}

	glm::mat4 proj = glm::perspective(glm::radians(60.0f), WINDOW_WITDH / (float)WINDOW_HEIGHT, 0.001f, 1000.f);
	glm::vec3 lightAmbient = LIGHT_AMBIENT;
	glm::vec3 lightPos = LIGHT_POS;
	glm::vec3 lightColor = LIGHT_COLOR;
	glm::vec3 objColor = OBJECT_COLOR;
	glm::vec3 obsColor = glm::vec3(0.2, 0.2, 0.2);
};

