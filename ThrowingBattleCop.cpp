#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include<gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <conio.h>
#include "Cube.h"
#include "stb_image.h"
#include <random>
#include<cmath>
#include "Robot.h"
#include "Lobby.h"
#include "Sky.h"
#include "Field.h"
#include "Stone.h"
#include "LobbyFloor.h"
#include "Desk.h"
#include "Missile.h"
#include "Door.h"

using namespace std;

enum directionlist { FRONT, BACK, LEFT, RIGHT, STOP };
enum gamestatelist {START, LOBBY};
enum commandlist {CATCH,THROW,IDLE};

int direction = BACK;
int gamestate = LOBBY;
int command = IDLE;

random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_int_distribution<int> dirDist(FRONT, RIGHT);
uniform_real_distribution<double> posDist(-14.0, 14.0);

#define WINDOW_WITDH	800
#define WINDOW_HEIGHT	600

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyPress(int key, int x, int y);
GLvoid SpecialKeyUp(int key, int x, int y);
GLvoid gameUpdateTimer(int value);
GLvoid stoneCreateTimer(int value);
GLvoid missileCreateTimer(int value);
GLvoid stoneThrowTimer(int value);
GLvoid comStoneThrowTimer(int value);
GLvoid moveActionTimer(int value);
GLvoid changeDirTimer(int value);
GLvoid comMoveTimer(int value);
GLvoid Mouse(int button, int state, int x, int y);

GLfloat mx = 0.0f;
GLfloat my = 0.0f;

glm::vec2 lobbyPos=glm::vec2(20.0, 0.0);

Object obj;

dataCollection dc;
Robot mainRobot(lobbyPos.x, 0.0, glm::vec3(1.0, 0.0, 0.0));
Robot robot1(8.0, -8.0, glm::vec3(0.0, 0.0, 1.0));
Robot robot2(-8.0, -8.0, glm::vec3(1.0, 1.0, .0));
Robot robot3(-8.0, 8.0, glm::vec3(0.0, 1.0, 0.0));
vector<Robot> comRobot;
Robot shopper(20.0, -14.0, glm::vec3(0.1, 0.1, 0.1));
Lobby lobby(lobbyPos.x, lobbyPos.y);
LobbyFloor lobbyf(lobbyPos.x, lobbyPos.y,1);
Sky sky;
Field field(1);
Desk desk(20.0, -12.0);
Door door;

vector<Stone> stoneList;
vector<Missile> missileList;

float window_w = 800.0f;
float window_h = 600.0f;

double cubeEdgeLength = 1.0;

int main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{   //--- ������ �����ϱ�
    glutInit(&argc, argv); // glut �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
    glutInitWindowPosition(0, 0); // �������� ��ġ ����
    glutInitWindowSize(WINDOW_WITDH, WINDOW_HEIGHT);   // �������� ũ�� ����
    glutCreateWindow("Example1"); // ������ ���� (������ �̸�)

    //--- GLEW �ʱ�ȭ�ϱ�
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized\n";


    if (!sky.cube.initShaderProgram() || !sky.cube.defineVertexArrayObject_all()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    if (!field.cube.initShaderProgram() || !field.cube.defineVertexArrayObject_face()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    if (!lobby.cube.initShaderProgram() || !lobby.cube.defineVertexArrayObject_all()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    if (!lobbyf.cube.initShaderProgram() || !lobbyf.cube.defineVertexArrayObject_face()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    if (!desk.cube.initShaderProgram() || !desk.cube.defineVertexArrayObject_all()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    if (!door.cube.initShaderProgram_noTex() || !door.cube.defineVertexArrayObject_noTex()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 8; ++i)
        if (!mainRobot.cube[i].initShaderProgram_noTex() || !mainRobot.cube[i].defineVertexArrayObject_noTex()) {
            cerr << "Error: Shader Program ���� ����" << endl;
            std::exit(EXIT_FAILURE);
        }

    for (int i = 0; i < 8; ++i)
        if (!robot1.cube[i].initShaderProgram_noTex() || !robot1.cube[i].defineVertexArrayObject_noTex()) {
            cerr << "Error: Shader Program ���� ����" << endl;
            std::exit(EXIT_FAILURE);
        }

    for (int i = 0; i < 8; ++i)
        if (!robot2.cube[i].initShaderProgram_noTex() || !robot2.cube[i].defineVertexArrayObject_noTex()) {
            cerr << "Error: Shader Program ���� ����" << endl;
            std::exit(EXIT_FAILURE);
        }

    for (int i = 0; i < 8; ++i)
        if (!robot3.cube[i].initShaderProgram_noTex() || !robot3.cube[i].defineVertexArrayObject_noTex()) {
            cerr << "Error: Shader Program ���� ����" << endl;
            std::exit(EXIT_FAILURE);
        }

    for (int i = 0; i < 8; ++i)
        if (!shopper.cube[i].initShaderProgram_noTex() || !shopper.cube[i].defineVertexArrayObject_noTex()) {
            cerr << "Error: Shader Program ���� ����" << endl;
            std::exit(EXIT_FAILURE);
        }

    glutDisplayFunc(drawScene); // ��� �Լ��� ����
    glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ����
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyPress);
    glutSpecialUpFunc(SpecialKeyUp);
    glutMouseFunc(Mouse);
    glutTimerFunc(100, gameUpdateTimer, 1);
    glutTimerFunc(100, moveActionTimer, 1);
    glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
    //--- ����� ���� ����
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� ����
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    dc.cameraPosSetting();
    dc.viewSetting();

    mainRobot.dc = dc;
    if (comRobot.size() > 0) {
        comRobot[0].dc = dc;
        comRobot[1].dc = dc;
        comRobot[2].dc = dc;
    }
    lobby.dc = dc;
    lobbyf.dc = dc;
    sky.dc = dc;
    field.dc = dc;
    shopper.dc = dc;
    desk.dc = dc;
    door.dc = dc;
    if (stoneList.size() > 0)
        stoneList[stoneList.size() - 1].dc = dc;
    if (missileList.size() > 0)
        missileList[missileList.size() - 1].dc = dc;

    int width = 200;
    int height = 200;

    int Channel1 = 100;
    int Channel2 = 200;
    int Channel3 = 300;
    int Channel4 = 400;
    int Channel5 = 500;
    int Channel6 = 600;
    stbi_set_flip_vertically_on_load(true); //--- �̹����� �Ųٷ� �����ٸ� �߰�

    unsigned char* floorData = stbi_load("tex1.png", &width, &height, &Channel1, 3);
   unsigned char* mainData = stbi_load("tex5.png", &width, &height, &Channel2, 3);
   unsigned char* skyData = stbi_load("sky.jpg", &width, &height, &Channel3, 3);
   unsigned char* lobbyfData = stbi_load("lobbyfloortex.jpg", &width, &height, &Channel4, 3);
   unsigned char* woodData = stbi_load("wood.jpg", &width, &height, &Channel5, 3);
   unsigned char* wallData = stbi_load("wall.jpg", &width, &height, &Channel6, 3);

    unsigned int texture_fl;
    unsigned int texture_main;
    unsigned int texture_sky;
    unsigned int texture_lobbyf;
    unsigned int texture_wood;
    unsigned int texture_wall;

    glGenTextures(1, &texture_sky); //--- �ؽ�ó ����
    glBindTexture(GL_TEXTURE_2D, texture_sky); //--- �ؽ�ó ���ε�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, skyData); //---�ؽ�ó �̹��� ����

    sky.makingSky();

    glGenTextures(1, &texture_fl); //--- �ؽ�ó ����
    glBindTexture(GL_TEXTURE_2D, texture_fl); //--- �ؽ�ó ���ε�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, floorData); //---�ؽ�ó �̹��� ����

    field.makingField();

    glGenTextures(1, &texture_lobbyf); //--- �ؽ�ó ����
    glBindTexture(GL_TEXTURE_2D, texture_lobbyf); //--- �ؽ�ó ���ε�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, lobbyfData); //---�ؽ�ó �̹��� ����

    lobbyf.makingLobbyFloor();

    glGenTextures(1, &texture_main); //--- �ؽ�ó ����
    glBindTexture(GL_TEXTURE_2D, texture_main); //--- �ؽ�ó ���ε�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, mainData); //---�ؽ�ó �̹��� ����

    if (stoneList.size() > 0)
        for (Stone stone : stoneList)
            stone.makingStone();

    glGenTextures(1, &texture_wood); //--- �ؽ�ó ����
    glBindTexture(GL_TEXTURE_2D, texture_wood); //--- �ؽ�ó ���ε�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, woodData); //---�ؽ�ó �̹��� ����

    desk.makingDesk();

    glGenTextures(1, &texture_wall); //--- �ؽ�ó ����
    glBindTexture(GL_TEXTURE_2D, texture_wall); //--- �ؽ�ó ���ε�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, wallData); //---�ؽ�ó �̹��� ����

    lobby.makingLobby();

    mainRobot.makingRobot();
    for (Robot &robot : comRobot)
        robot.makingRobot();
    shopper.makingRobot();
    door.makingDoor();
    if (missileList.size() > 0)
        for (Missile missile : missileList)
            missile.makingMissile();

    glutSwapBuffers();
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_CULL_FACE);

    stbi_image_free(skyData);
    stbi_image_free(floorData);
    stbi_image_free(lobbyfData);
    stbi_image_free(mainData);
    stbi_image_free(woodData);
    stbi_image_free(wallData);

}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
    window_w = (float)w;
    window_h = (float)h;
    glViewport(0, 0, w, h);
}

bool isPlus_xRotate_robot = true;

bool isStoneThrowTimerStop = false;
bool isComStoneThrowTimerStop = false;
bool isCatchFail = true;
bool isComCatchFail = true;

bool isTimer1On = false;
bool isTimer2On = false;

bool isTimer2Stop = false;
bool isAllStop = false;

bool isKeyPress = false;

GLvoid SpecialKeyPress(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        if (!mainRobot.isStoned) {
            direction = FRONT;
            if (mainRobot._zMove > -14.8)
                mainRobot._zMove -= 0.1;
            mainRobot.yRotate_direction = 180.0f;
        }
            isKeyPress = true;
        break;
    case GLUT_KEY_DOWN:
        if (!mainRobot.isStoned) {
            direction = BACK;
            if (mainRobot._zMove < 14.8)
                mainRobot._zMove += 0.1;
            mainRobot.yRotate_direction = 0.0f;
        }
        isKeyPress = true;
        break;
    case GLUT_KEY_LEFT:
        if (!mainRobot.isStoned) {
            direction = LEFT;
            if (mainRobot._zMove > 0.5 && mainRobot._xMove > 15.2)
                mainRobot._xMove -= 0.1;
            if (mainRobot._zMove < -0.5 && mainRobot._xMove > 15.2)
                mainRobot._xMove -= 0.1;
            if (mainRobot._zMove >= -0.5 && mainRobot._zMove <= 0.5)
                mainRobot._xMove -= 0.1;
            else  if (gamestate == START && mainRobot._xMove > -14.8)
                mainRobot._xMove -= 0.1;
            mainRobot.yRotate_direction = -90.0f;
        }
        isKeyPress = true;
        break;
    case GLUT_KEY_RIGHT:
        if (!mainRobot.isStoned) {
            direction = RIGHT;
            if (gamestate == START && mainRobot._xMove < 14.8)
                mainRobot._xMove += 0.1;
            else if (gamestate == LOBBY && mainRobot._xMove < 24.8)
                mainRobot._xMove += 0.1;
            mainRobot.yRotate_direction = 90.0f;
        }
        isKeyPress = true;
        break;
    }
    glutPostRedisplay();
}

GLvoid SpecialKeyUp(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        isKeyPress = false;
        break;
    case GLUT_KEY_DOWN:
        isKeyPress = false;
        break;
    case GLUT_KEY_LEFT:
        isKeyPress = false;
        break;
    case GLUT_KEY_RIGHT:
        isKeyPress = false;
        break;
    }
    glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y){
    switch (key) {
    case 'x':
        command = CATCH;
        break;
    case 'c':
        command = THROW;
        break;
    case 'e':
        dc.cameraX = 0.0;
        dc.cameraZ = 0.0;
        break;
    case 'q':
        exit(1);
    }
    glutPostRedisplay(); //--- ������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

bool startinit = false;

GLvoid gameUpdateTimer(int value) {

    if (mainRobot._xMove < 14.8)
        gamestate = START;

    if (gamestate == START) {
        if (!startinit) {
            dc.cameraX = 0.0;
            dc.cameraY = 20.0;
            dc.cameraZ = 9.0;
            mainRobot._xMove = 8.0;
            mainRobot._zMove = 8.0;
            startinit = true;
            glutTimerFunc(1000, stoneCreateTimer, 1);
            glutTimerFunc(1000, missileCreateTimer, 1);
            glutTimerFunc(100, comMoveTimer, 1);
            glutTimerFunc(3000, changeDirTimer, 1);
            robot1.comDir = BACK;
            robot2.comDir = BACK;
            robot3.comDir = BACK;
            comRobot.push_back(robot1);
            comRobot.push_back(robot2);
            comRobot.push_back(robot3);
        }
    }

    for (Stone &stone : stoneList) {
        if ( mainRobot._xMove > stone._xMove - 0.5 && mainRobot._xMove < stone._xMove + 0.5 && mainRobot._zMove>stone._zMove - 0.5 && mainRobot._zMove < stone._zMove + 0.5) {
            if (isCatchFail && command == CATCH) {
                isCatchFail = false;
                stone.isCatch = true;
            }

            if (stone.isCatch&&command == CATCH) {
                stone._yMove = 1.0;
                stone._xMove = mainRobot._xMove;
                stone._zMove = mainRobot._zMove;
            }

            if (stone.isCatch&&!isCatchFail && command == THROW) {
                stone.isCatch = false;
                if (direction==FRONT)
                    stone.isThrowOn_front = true;
                else if (direction == BACK)
                    stone.isThrowOn_back = true;
                else if (direction == LEFT)
                    stone.isThrowOn_left = true;
                else if (direction == RIGHT)
                    stone.isThrowOn_right = true;
                isStoneThrowTimerStop = false;
                glutTimerFunc(10, stoneThrowTimer, 1);
            }
        }
    }

    if (isCatchFail)
        command = IDLE;

    for (int i = 0; i < stoneList.size(); i++) {
        for (int j = 0; j < comRobot.size(); j++) {
            if (!stoneList[i].isThrowOn_front && !stoneList[i].isThrowOn_back && !stoneList[i].isThrowOn_left && !stoneList[i].isThrowOn_right)
                if (comRobot[j].isComCatchFail && comRobot[j]._xMove > stoneList[i]._xMove - 5.0 && comRobot[j]._xMove < stoneList[i]._xMove + 5.0 && comRobot[j]._zMove>stoneList[i]._zMove - 5.0 && comRobot[j]._zMove < stoneList[i]._zMove + 5.0) {
                    if (!comRobot[j].isMoveToStone) {
                        comRobot[j].isMoveToStone = true;
                        stoneList[i].isTarget = true;
                    }

                    if (stoneList[i].isTarget) {
                        double findDistance = sqrt((comRobot[j]._xMove - stoneList[i]._xMove) * (comRobot[j]._xMove - stoneList[i]._xMove) + (comRobot[j]._zMove - stoneList[i]._zMove) * (comRobot[j]._zMove - stoneList[i]._zMove));
                        double dx = (stoneList[i]._xMove - comRobot[j]._xMove) / findDistance / 10;
                        double dz = (stoneList[i]._zMove - comRobot[j]._zMove) / findDistance / 10;
                        comRobot[j]._xMove += dx;
                        comRobot[j]._zMove += dz;
                    }
                }
                if (comRobot[j]._xMove > stoneList[i]._xMove - 0.5 && comRobot[j]._xMove < stoneList[i]._xMove + 0.5 && comRobot[j]._zMove>stoneList[i]._zMove - 0.5 && comRobot[j]._zMove < stoneList[i]._zMove + 0.5) {
                    if (comRobot[j].isComCatchFail) {
                        comRobot[j].isMoveToStone = false;
                        comRobot[j].isComCatchFail = false;
                        stoneList[i].isComCatch = true;
                    }

                    if (stoneList[i].isComCatch) {
                        stoneList[i]._yMove = 1.0;
                        stoneList[i]._xMove = comRobot[j]._xMove;
                        stoneList[i]._zMove = comRobot[j]._zMove;
                    }

                    if (stoneList[i].isComCatch && !comRobot[j].isComCatchFail && comRobot[j]._xMove > mainRobot._xMove - 8.0 && comRobot[j]._xMove < mainRobot._xMove + 8.0 && comRobot[j]._zMove>mainRobot._zMove - 8.0 && comRobot[j]._zMove < mainRobot._zMove + 8.0) {
                        stoneList[i].isComCatch = false;
                        stoneList[i].isThrowToMainRobot = true;
                        double throwDistance = sqrt((comRobot[j]._xMove - mainRobot._xMove) * (comRobot[j]._xMove - mainRobot._xMove) + (comRobot[j]._zMove - mainRobot._zMove) * (comRobot[j]._zMove - mainRobot._zMove));
                        stoneList[i].dMainRobotPosX = (mainRobot._xMove - comRobot[j]._xMove) / throwDistance/10;
                        stoneList[i].dMainRobotPosZ = (mainRobot._zMove - comRobot[j]._zMove) / throwDistance/10;
                        isComStoneThrowTimerStop = false;
                        glutTimerFunc(10, comStoneThrowTimer, 1);
                        stoneList[i].throwIndex = j;
                    }
                }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(100, gameUpdateTimer, 1);
}

GLvoid stoneThrowTimer(int value) {
    for (int i = 0; i < stoneList.size(); i++) {
        if (stoneList[i].isThrowOn_front) {
            stoneList[i]._yMove -= 0.001 * ((1.0 - stoneList[i]._yMove) * 50 + 1.0);
            stoneList[i]._zMove -= 0.1;
            if (stoneList[i]._yMove <= -0.2) {
                isCatchFail = true;
                isStoneThrowTimerStop = true;
                stoneList[i].isThrowOn_front = false;
                stoneList.erase(cbegin(stoneList) + i);
            }
            for (int j = 0; j < comRobot.size(); j++) {
                if (comRobot[j]._xMove > stoneList[i]._xMove - 0.5 && comRobot[j]._xMove < stoneList[i]._xMove + 0.5 && comRobot[j]._zMove>stoneList[i]._zMove - 0.5 && comRobot[j]._zMove < stoneList[i]._zMove + 0.5) {
                    comRobot[j].yRotate_direction = -90.0;
                    comRobot[j]._xMove = 16.0;
                    comRobot[j]._yMove = 9.0;
                    if (j == 0)
                        comRobot[j]._zMove = -14.0;
                    else if (j == 1)
                        comRobot[j]._zMove = -12.0;
                    else if (j == 2)
                        comRobot[j]._zMove = -10.0;
                    comRobot[j].isStoned = true;
                    isCatchFail = true;
                    isStoneThrowTimerStop = true;
                    stoneList[i].isThrowOn_front = false;
                    stoneList.erase(cbegin(stoneList) + i);
                }
            }
        }
        if (stoneList[i].isThrowOn_back) {
            stoneList[i]._yMove -= 0.001 * ((1.0 - stoneList[i]._yMove) * 50 + 1.0);
            stoneList[i]._zMove += 0.1;
            if (stoneList[i]._yMove <= -0.2) {
                isCatchFail = true;
                isStoneThrowTimerStop = true;
                stoneList[i].isThrowOn_back = false;
                stoneList.erase(cbegin(stoneList) + i);
            }
            for (int j = 0; j < comRobot.size(); j++) {
                if (comRobot[j]._xMove > stoneList[i]._xMove - 0.5 && comRobot[j]._xMove < stoneList[i]._xMove + 0.5 && comRobot[j]._zMove>stoneList[i]._zMove - 0.5 && comRobot[j]._zMove < stoneList[i]._zMove + 0.5) {
                    comRobot[j].yRotate_direction = -90.0;
                    comRobot[j]._xMove = 16.0;
                    comRobot[j]._yMove = 9.0;
                    if (j == 0)
                        comRobot[j]._zMove = -14.0;
                    else if (j == 1)
                        comRobot[j]._zMove = -12.0;
                    else if (j == 2)
                        comRobot[j]._zMove = -10.0;
                    comRobot[j].isStoned = true;
                    isCatchFail = true;
                    isStoneThrowTimerStop = true;
                    stoneList[i].isThrowOn_front = false;
                    stoneList.erase(cbegin(stoneList) + i);
                }
            }
        }
        if (stoneList[i].isThrowOn_left) {
            stoneList[i]._yMove -= 0.001 * ((1.0 - stoneList[i]._yMove) * 50 + 1.0);
            stoneList[i]._xMove -= 0.1;
            if (stoneList[i]._yMove <= -0.2) {
                isCatchFail = true;
                isStoneThrowTimerStop = true;
                stoneList[i].isThrowOn_left = false;
                stoneList.erase(cbegin(stoneList) + i);
            }
            for (int j = 0; j < comRobot.size(); j++) {
                if (comRobot[j]._xMove > stoneList[i]._xMove - 0.5 && comRobot[j]._xMove < stoneList[i]._xMove + 0.5 && comRobot[j]._zMove>stoneList[i]._zMove - 0.5 && comRobot[j]._zMove < stoneList[i]._zMove + 0.5) {
                    comRobot[j].yRotate_direction = -90.0;
                    comRobot[j]._xMove = 16.0;
                    comRobot[j]._yMove = 9.0;
                    if (j == 0)
                        comRobot[j]._zMove = -14.0;
                    else if (j == 1)
                        comRobot[j]._zMove = -12.0;
                    else if (j == 2)
                        comRobot[j]._zMove = -10.0;
                    comRobot[j].isStoned = true;
                    isCatchFail = true;
                    isStoneThrowTimerStop = true;
                    stoneList[i].isThrowOn_front = false;
                    stoneList.erase(cbegin(stoneList) + i);
                }
            }
        }
        if (stoneList[i].isThrowOn_right) {
            stoneList[i]._yMove -= 0.001 * ((1.0 - stoneList[i]._yMove) * 50 + 1.0);
            stoneList[i]._xMove += 0.1;
            if (stoneList[i]._yMove <= -0.2) {
                isCatchFail = true;
                isStoneThrowTimerStop = true;
                stoneList[i].isThrowOn_right = false;
                stoneList.erase(cbegin(stoneList) + i);
            }
            for (int j = 0; j < comRobot.size(); j++) {
                if (comRobot[j]._xMove > stoneList[i]._xMove - 0.5 && comRobot[j]._xMove < stoneList[i]._xMove + 0.5 && comRobot[j]._zMove>stoneList[i]._zMove - 0.5 && comRobot[j]._zMove < stoneList[i]._zMove + 0.5) {
                    comRobot[j].yRotate_direction = -90.0;
                    comRobot[j]._xMove = 16.0;
                    comRobot[j]._yMove = 9.0;
                    if (j == 0)
                        comRobot[j]._zMove = -14.0;
                    else if (j == 1)
                        comRobot[j]._zMove = -12.0;
                    else if (j == 2)
                        comRobot[j]._zMove = -10.0;
                    comRobot[j].isStoned = true;
                    isCatchFail = true;
                    isStoneThrowTimerStop = true;
                    stoneList[i].isThrowOn_front = false;
                    stoneList.erase(cbegin(stoneList) + i);
                }
            }
        }
    }

    glutPostRedisplay();
    if (!isStoneThrowTimerStop)
        glutTimerFunc(10, stoneThrowTimer, 1);
}

GLvoid comStoneThrowTimer(int value) {
    for (int i = 0; i < stoneList.size(); i++) {
        if (stoneList[i].isThrowToMainRobot) {
            stoneList[i]._yMove -= 0.001 * ((1.0 - stoneList[i]._yMove) * 50 + 1.0);
            stoneList[i]._xMove += stoneList[i].dMainRobotPosX;
            stoneList[i]._zMove += stoneList[i].dMainRobotPosZ;
            if (stoneList[i]._yMove <= -0.2) {
                comRobot[stoneList[i].throwIndex].isComCatchFail = true;
                isComStoneThrowTimerStop = true;
                stoneList[i].isThrowToMainRobot = false;
                stoneList.erase(cbegin(stoneList) + i);
            }
            if (mainRobot._xMove > stoneList[i]._xMove - 0.5 && mainRobot._xMove < stoneList[i]._xMove + 0.5 && mainRobot._zMove>stoneList[i]._zMove - 0.5 && mainRobot._zMove < stoneList[i]._zMove + 0.5) {
                mainRobot.yRotate_direction = -90.0;
                mainRobot._xMove = 16.0;
                mainRobot._yMove = 9.0;
                mainRobot._zMove = -8.0;
                mainRobot.isStoned = true;
                comRobot[stoneList[i].throwIndex].isComCatchFail = true;
                isComStoneThrowTimerStop = true;
                stoneList[i].isThrowToMainRobot = false;
                stoneList.erase(cbegin(stoneList) + i);
            }
        }
    }

    glutPostRedisplay();
    if (!isComStoneThrowTimerStop)
        glutTimerFunc(10, comStoneThrowTimer, 1);
}

GLvoid stoneCreateTimer(int value) {
    Stone stone(posDist(eng), posDist(eng));
    if (!stone.cube.initShaderProgram() || !stone.cube.defineVertexArrayObject_all()) {
        cerr << "Error: Shader Program ���� ����" << endl;
        std::exit(EXIT_FAILURE);
    }
    stoneList.push_back(stone);

    glutPostRedisplay();
    glutTimerFunc(2000, stoneCreateTimer, 1);
}

GLvoid missileCreateTimer(int value) {
    if (missileList.size() <= 3) {
        Missile missile(posDist(eng), posDist(eng));
        if (!missile.initShaderProgram_noTex() || !missile.defineVertexArrayObject()) {
            cerr << "Error: Shader Program ���� ����" << endl;
            std::exit(EXIT_FAILURE);
        }
        missileList.push_back(missile);
    }

    glutPostRedisplay();
    glutTimerFunc(8000, missileCreateTimer, 1);
}

GLvoid moveActionTimer(int value)
{
    if (isKeyPress == true) {
        if (mainRobot.isPlus_armAndLegRotate && mainRobot.xRotate_armAndLeg < 30.0f)
            mainRobot.xRotate_armAndLeg += 5.0f;
        else
            mainRobot.isPlus_armAndLegRotate = false;
        if (!mainRobot.isPlus_armAndLegRotate && mainRobot.xRotate_armAndLeg > -30.0f)
            mainRobot.xRotate_armAndLeg -= 5.0f;
        else
            mainRobot.isPlus_armAndLegRotate = true;
    }
    else
        mainRobot.xRotate_armAndLeg = 0.0f;

    if (gamestate == START) {
        for (Robot& robot : comRobot) {
            if (robot.isPlus_armAndLegRotate && robot.xRotate_armAndLeg < 30.0f)
                robot.xRotate_armAndLeg += 5.0f;
            else
                robot.isPlus_armAndLegRotate = false;
            if (!robot.isPlus_armAndLegRotate && robot.xRotate_armAndLeg > -30.0f)
                robot.xRotate_armAndLeg -= 5.0f;
            else
                robot.isPlus_armAndLegRotate = true;
        }
    }

    glutPostRedisplay(); // ȭ�� �� ���
    glutTimerFunc(100, moveActionTimer, 1);
}

GLvoid comMoveTimer(int value)
{
    for (Robot &robot : comRobot) {
        if (!robot.isMoveToStone && !robot.isStoned && robot._zMove >= -14.8 && robot._zMove <= 14.8 && robot._xMove>=-14.8 && robot._xMove <= 14.8) {
            if (robot.comDir == FRONT) {
                robot.yRotate_direction = 180.0f;
                robot._zMove -= 0.1;
            }
            else if (robot.comDir == BACK) {
                robot.yRotate_direction = 0.0f;
                robot._zMove += 0.1;
            }
            else if (robot.comDir == LEFT) {
                robot.yRotate_direction = -90.0f;
                robot._xMove -= 0.1;
            }
            else if (robot.comDir == RIGHT) {
                robot.yRotate_direction = 90.0f;
                robot._xMove += 0.1;
            }
        }
        else if(!robot.isMoveToStone && !robot.isStoned){
            if (robot.comDir == FRONT) {
                robot.comDir = BACK;
                robot.yRotate_direction = 0.0f;
                robot._zMove += 0.1;
            }
            else if (robot.comDir == BACK) {
                robot.comDir = FRONT;
                robot.yRotate_direction = 180.0f;
                robot._zMove -= 0.1;
            }
            else if (robot.comDir == LEFT) {
                robot.comDir = RIGHT;
                robot.yRotate_direction = 90.0f;
                robot._xMove += 0.1;
            }
            else if (robot.comDir == RIGHT) {
                robot.comDir = LEFT;
                robot.yRotate_direction = -90.0f;
                robot._xMove -= 0.1;
            }
        }
    }

    glutPostRedisplay(); // ȭ�� �� ���
    glutTimerFunc(100, comMoveTimer, 1);
}

GLvoid changeDirTimer(int value)
{
    for (Robot& robot : comRobot) {
        if (!robot.isMoveToStone && !robot.isStoned)
            robot.comDir = dirDist(eng);
    }

    glutPostRedisplay(); // ȭ�� �� ���
    glutTimerFunc(3000, changeDirTimer, 1);
}

GLvoid Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    }
    glutPostRedisplay();
}