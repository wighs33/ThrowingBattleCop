#include "Field.h"

void Field::makingField() {
    glUseProgram(cube.shaderProgramID);

    GLuint modelLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_model");
    GLuint viewLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_view");
    GLuint projectLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_projection");
    GLuint lightAmbientLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_lightPos");
    GLuint lightColorLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_lightColor");
    GLuint objColorLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation_cube = glGetUniformLocation(cube.shaderProgramID, "g_cameraPos");
    int tLocation_cube = glGetUniformLocation(cube.shaderProgramID, "outColor"); //--- outTexture À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
    glUniform1i(tLocation_cube, 0); //--- »ùÇÃ·¯¸¦ 0¹ø À¯´ÖÀ¸·Î ¼³Á¤

    glm::mat4 modelTransform_cube = glm::mat4(1.0f);      //¹Ù´Ú
    modelTransform_cube = glm::translate(modelTransform_cube, glm::vec3(0.0, -cube.CUBE_EDGE_LENGTH / 2, 0.0));
    modelTransform_cube = glm::scale(modelTransform_cube, glm::vec3(floorSize, floorSize, floorSize));
    modelTransform_cube = glm::translate(modelTransform_cube, glm::vec3(0.0, -cube.CUBE_EDGE_LENGTH / 2, 0.0));
    glUniformMatrix4fv(modelLocation_cube, 1, GL_FALSE, glm::value_ptr(modelTransform_cube));
    glUniformMatrix4fv(viewLocation_cube, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation_cube, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation_cube, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation_cube, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation_cube, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation_cube, 1, (float*)&dc.objColor);
    glUniform3fv(cameraPosLocation_cube, 1, (float*)&dc.cameraPos);
    glBindVertexArray(cube.vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
