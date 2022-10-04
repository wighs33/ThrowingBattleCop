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

class Desk
{
public:
    double _xMove = 0.0;
    double _zMove = 0.0;
    double _scale = 10.0;
    Cube cube;
    dataCollection dc;

    Desk(double xMove, double zMove) : _xMove(xMove), _zMove(zMove) {
    }

    void makingDesk() {
        glUseProgram(cube.shaderProgramID);

        GLuint modelLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_model");
        GLuint viewLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_view");
        GLuint projectLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_projection");
        GLuint lightAmbientLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_lightAmbient");
        GLuint lightPosLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_lightPos");
        GLuint lightColorLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_lightColor");
        GLuint objColorLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_objectColor");
        GLuint cameraPosLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_cameraPos");

        glm::mat4 modelTransform_cube = glm::mat4(1.0f);
        modelTransform_cube = glm::translate(modelTransform_cube, glm::vec3(0.0, -cube.CUBE_EDGE_LENGTH / 2, 0.0));
        modelTransform_cube = glm::translate(modelTransform_cube, glm::vec3(_xMove, 0.0, _zMove));
        modelTransform_cube = glm::scale(modelTransform_cube, glm::vec3(9.0, 1.0, 1.0));
        modelTransform_cube = glm::translate(modelTransform_cube, glm::vec3(0.0, cube.CUBE_EDGE_LENGTH / 2, 0.0));
        glUniformMatrix4fv(modelLocation_cube, 1, GL_FALSE, glm::value_ptr(modelTransform_cube));
        glUniformMatrix4fv(viewLocation_cube, 1, GL_FALSE, glm::value_ptr(dc.view));
        glUniformMatrix4fv(projectLocation_cube, 1, GL_FALSE, glm::value_ptr(dc.proj));
        glUniform3fv(lightAmbientLocation_cube, 1, (float*)&dc.lightAmbient);
        glUniform3fv(lightPosLocation_cube, 1, (float*)&dc.lightPos);
        glUniform3fv(lightColorLocation_cube, 1, (float*)&dc.lightColor);
        glUniform3fv(objColorLocation_cube, 1, (float*)&dc.objColor);
        glUniform3fv(cameraPosLocation_cube, 1, (float*)&dc.cameraPos);
        glBindVertexArray(cube.vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};
