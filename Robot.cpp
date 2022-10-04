#include "Robot.h"

void Robot::makingRobot() {

    glUseProgram(cube[0].shaderProgramID);//促府

    GLuint modelLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_model");
    GLuint viewLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_view");
    GLuint projectLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube1 = glGetUniformLocation(cube[0].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube1 = glm::mat4(1.0f);
    modelTransform_cube1 = glm::translate(modelTransform_cube1, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube1 = glm::rotate(modelTransform_cube1, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    modelTransform_cube1 = glm::translate(modelTransform_cube1, glm::vec3(0.0, -0.1, 0.0));
    modelTransform_cube1 = glm::rotate(modelTransform_cube1, glm::radians(xRotate_armAndLeg), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube1 = glm::translate(modelTransform_cube1, glm::vec3(-0.1, -0.2, 0.0));
    modelTransform_cube1 = glm::scale(modelTransform_cube1, glm::vec3(0.1, 0.4, 0.1));
    glUniformMatrix4fv(modelLocation_cube1, 1, GL_FALSE, glm::value_ptr(modelTransform_cube1));
    glUniformMatrix4fv(viewLocation_cube1, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube1, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube1, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube1, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube1, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube1, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation_cube1, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube[0].vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(cube[1].shaderProgramID);//促府

    GLuint modelLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_model");
    GLuint viewLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_view");
    GLuint projectLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube2 = glGetUniformLocation(cube[1].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube2 = glm::mat4(1.0f);
    modelTransform_cube2 = glm::translate(modelTransform_cube2, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube2 = glm::rotate(modelTransform_cube2, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    modelTransform_cube2 = glm::translate(modelTransform_cube2, glm::vec3(0.0, -0.1, 0.0));
    modelTransform_cube2 = glm::rotate(modelTransform_cube2, glm::radians(-xRotate_armAndLeg), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube2 = glm::translate(modelTransform_cube2, glm::vec3(0.1, -0.2, 0.0));
    modelTransform_cube2 = glm::scale(modelTransform_cube2, glm::vec3(0.1, 0.4, 0.1));
    glUniformMatrix4fv(modelLocation_cube2, 1, GL_FALSE, glm::value_ptr(modelTransform_cube2));
    glUniformMatrix4fv(viewLocation_cube2, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube2, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube2, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube2, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube2, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube2, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation_cube2, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube[1].vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(cube[2].shaderProgramID);//个

    GLuint modelLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_model");
    GLuint viewLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_view");
    GLuint projectLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube3 = glGetUniformLocation(cube[2].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube3 = glm::mat4(1.0f);
    modelTransform_cube3 = glm::translate(modelTransform_cube3, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube3 = glm::rotate(modelTransform_cube3, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    //modelTransform_cube3 = glm::rotate(modelTransform_cube3, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube3 = glm::translate(modelTransform_cube3, glm::vec3(0.0, 0.2, 0.0));
    modelTransform_cube3 = glm::scale(modelTransform_cube3, glm::vec3(0.4, 0.6, 0.4));
    glUniformMatrix4fv(modelLocation_cube3, 1, GL_FALSE, glm::value_ptr(modelTransform_cube3));
    glUniformMatrix4fv(viewLocation_cube3, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube3, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube3, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube3, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube3, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube3, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation_cube3, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube[2].vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(cube[3].shaderProgramID);//迫

    GLuint modelLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_model");
    GLuint viewLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_view");
    GLuint projectLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube4 = glGetUniformLocation(cube[3].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube4 = glm::mat4(1.0f);
    modelTransform_cube4 = glm::translate(modelTransform_cube4, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube4 = glm::rotate(modelTransform_cube4, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    modelTransform_cube4 = glm::translate(modelTransform_cube4, glm::vec3(0.0, 0.35, 0.0));
    modelTransform_cube4 = glm::rotate(modelTransform_cube4, glm::radians(-xRotate_armAndLeg), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube4 = glm::translate(modelTransform_cube4, glm::vec3(-0.25, -0.15, 0.0));
    modelTransform_cube4 = glm::scale(modelTransform_cube4, glm::vec3(0.1, 0.4, 0.1));
    glUniformMatrix4fv(modelLocation_cube4, 1, GL_FALSE, glm::value_ptr(modelTransform_cube4));
    glUniformMatrix4fv(viewLocation_cube4, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube4, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube4, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube4, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube4, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube4, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation_cube4, 1, (float*)&dc.cameraPos);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(cube[4].shaderProgramID);//迫

    GLuint modelLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_model");
    GLuint viewLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_view");
    GLuint projectLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube5 = glGetUniformLocation(cube[4].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube5 = glm::mat4(1.0f);
    modelTransform_cube5 = glm::translate(modelTransform_cube5, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube5 = glm::rotate(modelTransform_cube5, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    modelTransform_cube5 = glm::translate(modelTransform_cube5, glm::vec3(0.0, 0.35, 0.0));
    modelTransform_cube5 = glm::rotate(modelTransform_cube5, glm::radians(xRotate_armAndLeg), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube5 = glm::translate(modelTransform_cube5, glm::vec3(0.25, -0.15, 0.0));
    modelTransform_cube5 = glm::scale(modelTransform_cube5, glm::vec3(0.1, 0.4, 0.1));
    glUniformMatrix4fv(modelLocation_cube5, 1, GL_FALSE, glm::value_ptr(modelTransform_cube5));
    glUniformMatrix4fv(viewLocation_cube5, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube5, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube5, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube5, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube5, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube5, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation_cube5, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube[4].vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(cube[5].shaderProgramID);//赣府

    GLuint modelLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_model");
    GLuint viewLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_view");
    GLuint projectLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube6 = glGetUniformLocation(cube[5].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube6 = glm::mat4(1.0f);
    modelTransform_cube6 = glm::translate(modelTransform_cube6, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube6 = glm::rotate(modelTransform_cube6, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    // modelTransform_cube6 = glm::rotate(modelTransform_cube6, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube6 = glm::translate(modelTransform_cube6, glm::vec3(0.0, 0.6, 0.0));
    modelTransform_cube6 = glm::scale(modelTransform_cube6, glm::vec3(0.2, 0.2, 0.2));
    glUniformMatrix4fv(modelLocation_cube6, 1, GL_FALSE, glm::value_ptr(modelTransform_cube6));
    glUniformMatrix4fv(viewLocation_cube6, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube6, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube6, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube6, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube6, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube6, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation_cube6, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube[5].vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glUseProgram(cube[6].shaderProgramID);//内

    GLuint modelLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_model");
    GLuint viewLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_view");
    GLuint projectLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube7 = glGetUniformLocation(cube[6].shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform_cube7 = glm::mat4(1.0f);
    modelTransform_cube7 = glm::translate(modelTransform_cube7, glm::vec3(_xMove, _yMove, _zMove));
    modelTransform_cube7 = glm::rotate(modelTransform_cube7, glm::radians(yRotate_direction), glm::vec3(0.0, 1.0, 0.0));
    //modelTransform_cube7 = glm::rotate(modelTransform_cube7, glm::radians(xRotateAni), glm::vec3(1.0, 0.0, 0.0));
    modelTransform_cube7 = glm::translate(modelTransform_cube7, glm::vec3(0.0, 0.6, 0.1));
    modelTransform_cube7 = glm::scale(modelTransform_cube7, glm::vec3(0.05, 0.1, 0.05));
    glUniformMatrix4fv(modelLocation_cube7, 1, GL_FALSE, glm::value_ptr(modelTransform_cube7));
    glUniformMatrix4fv(viewLocation_cube7, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube7, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube7, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube7, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube7, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube7, 1, (float*)&noseColor);
    glUniform3fv(cameraPosLocation_cube7, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube[6].vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
