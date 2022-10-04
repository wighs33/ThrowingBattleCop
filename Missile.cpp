#include "Missile.h"

void Missile::makingMissile() {
    glUseProgram(shaderProgramID);

    GLuint modelLocation = glGetUniformLocation(shaderProgramID, "g_model");
    GLuint viewLocation = glGetUniformLocation(shaderProgramID, "g_view");
    GLuint projectLocation = glGetUniformLocation(shaderProgramID, "g_projection");
    GLuint lightAmbientLocation = glGetUniformLocation(shaderProgramID, "g_lightAmbient");
    GLuint lightPosLocation = glGetUniformLocation(shaderProgramID, "g_lightPos");
    GLuint lightColorLocation = glGetUniformLocation(shaderProgramID, "g_lightColor");
    GLuint objColorLocation = glGetUniformLocation(shaderProgramID, "g_objectColor");
    GLuint cameraPosLocation = glGetUniformLocation(shaderProgramID, "g_cameraPos");

    glm::mat4 modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, glm::vec3(_xMove, -0.5, _zMove));
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(dc.view));
    glUniformMatrix4fv(projectLocation, 1, GL_FALSE, glm::value_ptr(dc.proj));
    glUniform3fv(lightAmbientLocation, 1, (float*)&dc.lightAmbient);
    glUniform3fv(lightPosLocation, 1, (float*)&dc.lightPos);
    glUniform3fv(lightColorLocation, 1, (float*)&dc.lightColor);
    glUniform3fv(objColorLocation, 1, (float*)&_Color);
    glUniform3fv(cameraPosLocation, 1, (float*)&dc.cameraPos);
    glBindVertexArray(vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 1704);
}

bool Missile::initShaderProgram() {
    const GLchar* vertexShaderSource = obj.filetobuf("vertex.glsl");
    const GLchar* fragmentShaderSource = obj.filetobuf("fragment.glsl");


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
        glDeleteShader(vertexShader);
        return false;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;

        return false;
    }


    shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);

    glLinkProgram(shaderProgramID);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
        cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
        return false;
    }
    glUseProgram(shaderProgramID);

    return true;
}

bool Missile::initShaderProgram_noTex() {
    const GLchar* vertexShaderSource = obj.filetobuf("vertex.glsl");
    const GLchar* fragmentShaderSource = obj.filetobuf("fragment_noTex.glsl");


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
        glDeleteShader(vertexShader);
        return false;
    }


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;

        return false;
    }


    shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);

    glLinkProgram(shaderProgramID);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
        cerr << "ERROR: shader program 연결 실패\n" << errorLog << endl;
        return false;
    }
    glUseProgram(shaderProgramID);

    return true;
}

bool Missile::defineVertexArrayObject() {

    obj.loadOBJ("missile.obj");

    //Vertex Buffer Object(VBO)를 생성하여 vertex 데이터를 복사한다.
    glGenBuffers(1, &positionVertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, positionVertexBufferObjectID);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    // glGenBuffers(1, &trianglePositionElementBufferObject);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trianglePositionElementBufferObject);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(positionIndex), positionIndex, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, obj.vertices.size() * sizeof(glm::vec3), &obj.vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normalVertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, normalVertexBufferObjectID);
    glBufferData(GL_ARRAY_BUFFER, obj.normals.size() * sizeof(glm::vec3), &obj.normals[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    GLint positionAttribute = glGetAttribLocation(shaderProgramID, "in_position");
    if (positionAttribute == -1) {
        cerr << "position 속성 설정 실패" << endl;
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, positionVertexBufferObjectID);
    glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(positionAttribute);

    GLint normalAttribute = glGetAttribLocation(shaderProgramID, "in_normal");
    if (normalAttribute == -1) {
        cerr << "normal 속성 설정 실패" << endl;
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, normalVertexBufferObjectID);
    glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normalAttribute);

    glBindVertexArray(0);


    return true;
}
