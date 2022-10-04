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
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

class Object
{
public:
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    bool  loadOBJ(const char* path) {
        std::vector< glm::vec3 > temp_vertices;
        std::vector< glm::vec2 > temp_uvs;
        std::vector< glm::vec3 > temp_normals;
        vertexIndices.clear();
        uvIndices.clear();
        normalIndices.clear();
        vertices.clear();
        uvs.clear();
        normals.clear();
        FILE* file = fopen(path, "r");
        if (file == NULL) {
            printf("Impossible to open the file !\n");
            return false;
        }
        while (1) {

            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; // EOF = End Of File. Quit the loop.

            // else : parse lineHeader
            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            }
            else if (strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                temp_uvs.push_back(uv);
            }
            else if (strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_normals.push_back(normal);
            }
            else if (strcmp(lineHeader, "f") == 0) {
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                if (matches != 9) {
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }

        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < uvIndices.size(); i++) {
            unsigned int uvIndex = uvIndices[i];
            glm::vec2 uv = temp_uvs[uvIndex - 1];
            uvs.push_back(uv);
        }

        for (unsigned int i = 0; i < normalIndices.size(); i++) {
            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = temp_normals[normalIndex - 1];
            normals.push_back(normal);
        }

        fclose(file);
    }

    char* filetobuf(const char* file)
    {
        FILE* fptr;
        long length;
        char* buf;
        fptr = fopen(file, "rb"); // Open file for reading
        if (!fptr) // Return NULL on failure
            return NULL;
        fseek(fptr, 0, SEEK_END); // Seek to the end of the file
        length = ftell(fptr); // Find out how many bytes into the file we are
        buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
        fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
        fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
        fclose(fptr); // Close the file
        buf[length] = 0; // Null terminator
        return buf; // Return the buffer
    }

private:
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
};



