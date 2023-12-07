//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "cube.h"
#include "sphere.h"
#include "Sphere2.h"
#include "Pyramid.h"
#include "stb_image.h"
#include <iostream>
#include <vector>

using namespace std;

long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);

void drawCylinder(unsigned int& cVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void scene(unsigned int& cVAO, Shader& lightingShader, Shader& ourShader);
void sun2(float tx, float ty, float tz, Shader& lightingShader, glm::mat4 alTogether);
void road_fence(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether);
void spa_center(Cube& cube1, Cube& cube2, Cube& cube3, Cube& cube4,unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture);

void spa_road(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture);
void watch_tower(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture);
void ball(float tx, float ty, float tz, Shader& lightingShader, glm::mat4 alTogether);

void gym(Cube& cube, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture);
void road(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture);
void swimming_pool(Cube& cube, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture);
void machine_1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x);
void machine_2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x);
void machine_3(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x);
void voley(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void shaderActivate(Shader& shader);



// settings
const unsigned int SCR_WIDTH = 1900;
const unsigned int SCR_HEIGHT = 1200;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float z_x[3] = { 0.0,0.0,0.0 };
float x_x[3] = { 0.0,0.0,0.0 };


float b_x = 0.0;
float b_y = 0.0;
float boat_x = 0.0;
float h_x = 0.0;
float h_x2 = 0.0;
bool ball_t = false;
float rx = 0.0;
float ty = 0.0;

float m3_rx = 0.0;
float m3_ty = 0.0;


//bezier
GLint viewport[4];

/////////////////////////////////////////////////////////////
float wcsClkDn[3], wcsClkUp[3];
vector <float> cntrlPoints{
-0.0450, 1.9950, 5.1000,
-0.1100, 1.9700, 5.1000,
-0.1700, 1.9400, 5.1000,
-0.2150, 1.9000, 5.1000,
-0.2750, 1.8750, 5.1000,
-0.3250, 1.8500, 5.1000,
-0.3800, 1.8150, 5.1000,
-0.4250, 1.7850, 5.1000,
-0.4800, 1.7650, 5.1000,
-0.5300, 1.7350, 5.1000,
-0.5850, 1.6950, 5.1000,
-0.6400, 1.6750, 5.1000,
-0.7100, 1.6450, 5.1000,
-0.7400, 1.6300, 5.1000,
-0.7550, 1.6150, 5.1000,
-0.7850, 1.5900, 5.1000,
-0.8150, 1.5650, 5.1000,
-0.8300, 1.5350, 5.1000,
};


vector <float> cntrlPoints1{
-0.0700, 2.0350, 5.1000,
-0.1200, 2.0450, 5.1000,
-0.1550, 2.0450, 5.1000,
-0.1950, 2.0350, 5.1000,
-0.3300, 1.9800, 5.1000,
-0.4550, 1.9450, 5.1000,
-0.5450, 1.8750, 5.1000,
-0.6150, 1.7950, 5.1000,
-0.7250, 1.6500, 5.1000,
-0.6700, 1.6350, 5.1000,
-0.6300, 1.6250, 5.1000,
-0.6000, 1.6100, 5.1000,
-0.5700, 1.5950, 5.1000,
-0.5400, 1.5650, 5.1000,
-0.5300, 1.5250, 5.1000,
-0.5300, 1.4650, 5.1000,
-0.5300, 1.4650, 5.1000,
-0.5850, 1.4150, 5.1000,
-0.6150, 1.4100, 5.1000,
-0.7550, 1.3950, 5.1000,
-0.8850, 1.3950, 5.1000,
-1.0100, 1.3700, 5.1000,
-1.1400, 1.2950, 5.1000,
-1.1600, 1.2450, 5.1000,
-1.1750, 1.1500, 5.1000,
-1.1450, 1.0950, 5.1000,
-1.0550, 1.0700, 5.1000,
-0.9450, 1.0200, 5.1000,
-0.8200, 0.9800, 5.1000,
-0.7000, 0.9750, 5.1000,
-0.6450, 0.9750, 5.1000,
-0.6350, 0.8600, 5.1000,
-1.0100, 0.8050, 5.1000,
-1.3400, 0.8100, 5.1000,
-1.3700, 0.7600, 5.1000,
-1.4500, 0.6850, 5.1000,
-1.4700, 0.6050, 5.1000,
-1.4700, 0.5900, 5.1000,
-1.4000, 0.4050, 5.1000,
-1.2750, 0.3550, 5.1000,
-1.0300, 0.3200, 5.1000,
-0.7400, 0.2600, 5.1000,
-0.5700, 0.2650, 5.1000,
-0.2500, 0.2800, 5.1000,
};


vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];



const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = true;
bool showHollowBezier = true;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierVAO1;


    



const int MAX_DEPTH = 2;
const int CHILDREN_NUMBER = 1;
// camera
Camera camera(glm::vec3(0.0f, 1.1f, 5.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


void sun(Sphere2& sphere2, float length, float width, float baseHeight, float tx, float ty, float tz, unsigned int& cubeVAO, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    float r = 253 / 255.0, g = 184 / 255.0, b = 19 / 255.0;
    //Sphere sphere = Sphere(1, 36, 18, glm::vec3(r, g, b), glm::vec3(r, g, b), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

    //  Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, glm::vec3 amb = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 diff = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f), float shiny = 32.0f) : verticesStride(24)

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4  rotateXMatrix, rotateYMatrix, rotateZMatrix;
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(sx, sy, sz));
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(tx, ty, tz));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translate * rotateXMatrix * rotateYMatrix * rotateZMatrix * scale;
    sphere2.drawSphereWithTexture(lightingShaderWithTexture, model);

}

void disco_Light(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture )
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.15, 0.2, 0.2));
    translate = glm::translate(model, glm::vec3(-6.0, 1.27, 5));
    model = alTogether * translate*scale;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    

}


void pahar(Pyramid& pyramid, float sx, float sy, float sz, float tx, float ty, float tz, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    //sand texture

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4  rotateXMatrix, rotateYMatrix, rotateZMatrix, rotateXMatrix2, rotateY2Matrix;


    glm::mat4 modelTexture6 = glm::mat4(1.0f);
    glm::mat4 modelTexture7 = glm::mat4(1.0f);
    glm::mat4 translate6 = glm::mat4(1.0f);
    glm::mat4 scale6 = glm::mat4(1.0f);

    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateY2Matrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scale6 = glm::scale(modelTexture6, glm::vec3(sx, sy, sz));
    translate6 = glm::translate(modelTexture6, glm::vec3(tx, ty, tz));
    modelTexture6 = alTogether * translate6 * rotateXMatrix * rotateYMatrix * rotateZMatrix * scale6;
    //model = alTogether * translate * rotateXMatrix * rotateYMatrix * rotateZMatrix * scale;
    modelTexture7 = alTogether * translate6 * rotateXMatrix * rotateY2Matrix * rotateZMatrix * scale6;


    pyramid.setTransform(modelTexture6);
    pyramid.draw(lightingShaderWithTexture);
    pyramid.setTransform(modelTexture7);
    pyramid.draw(lightingShaderWithTexture);
    //cube6.drawCubeWithTexture(lightingShaderWithTexture, modelTexture6);

}



void drawCylinder(unsigned int& cVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 60.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cVAO);
    glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
}

void tree(unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5 , 0.9, 0.1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, .9, 0.2));
    model =alTogether * translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95/255.0, 48/255.0, 31/255.0);

    identityMatrix = glm::mat4(1.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5, 1.9, 0.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.06, .6, 0.06));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = alTogether * translateMatrix * rotateZMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95 / 255.0, 48 / 255.0, 31 / 255.0);

    identityMatrix = glm::mat4(1.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.5, 1.9, -0.4));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.06, .6, 0.06));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = alTogether * translateMatrix * rotateZMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95 / 255.0, 48 / 255.0, 31 / 255.0);

    identityMatrix = glm::mat4(1.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.75, 1.9, 0.1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.06, .6, 0.06));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translateMatrix * rotateZMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95 / 255.0, 48 / 255.0, 31 / 255.0);

    identityMatrix = glm::mat4(1.0f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.2, 1.9, 0.1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.06, .6, 0.06));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = alTogether * translateMatrix * rotateZMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95 / 255.0, 48 / 255.0, 31 / 255.0);
}



void human(unsigned int& cVAO, Shader& lightingShader, float r, float g, float b)
{

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.5 - i* 0.1, 0.4, 3.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.031, 0.155, 0.031));
        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 0 / 255.0, 84 / 255.0, 0 / 255.0);
    }

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.5 - i * 0.1, 0.1, 3.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, 0.14, 0.025));
        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 241 / 255.0, 194 / 255.0, 125 / 255.0);
    }

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.55, 0.55, 3.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.18, 0.05));
    model = translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 30 / 255.0, 44 / 255.0, 155 / 255.0);

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.628 + i * 0.156, 0.59, 3.38));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02, 0.18, 0.02));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(50.0f + h_x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix ;
        drawCylinder(cVAO, lightingShader, model, 241 / 255.0, 194 / 255.0, 125 / 255.0);
    }

    for (int i = 0; i < 1; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.55, 0.72, 3.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, 0.1, 0.025));
        
        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 241 / 255.0, 194 / 255.0, 125 / 255.0);
    }   
}


void human2(unsigned int& cVAO, Shader& lightingShader, float r, float g, float b)
{
    float fx = 3.05;

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.5 - i * 0.1, 0.4, 3.5-fx));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.031, 0.155, 0.031));
        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 0 / 255.0, 84 / 255.0, 0 / 255.0);
    }

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.5 - i * 0.1, 0.1, 3.5-fx));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, 0.14, 0.025));
        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 241 / 255.0, 194 / 255.0, 125 / 255.0);
    }

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.55, 0.55, 3.5-fx));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.18, 0.05));
    model = translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 34 / 255.0, 139 / 255.0, 34 / 255.0);
   

    for (int i = 0; i < 2; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.628 + i * 0.156, 0.585, 3.38 -fx+0.22));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02, 0.18, 0.02));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(140.0f + h_x2), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 241 / 255.0, 194 / 255.0, 125 / 255.0);
    }

    for (int i = 0; i < 1; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.55, 0.72, 3.5-fx));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025, 0.1, 0.025));

        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 241 / 255.0, 194 / 255.0, 125 / 255.0);
    }
}


void umbrella(unsigned int& cVAO, Shader& lightingShader)
{
    for (int i = 0; i < 4; i++)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.4 + i* 1.0, 0.5, 1.63 ));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01, 0.35, 0.01));
        model = translateMatrix * scaleMatrix;
        //drawCylinder(cVAO , lightingShader, model, 0 / 255.0, 84 / 255.0, 0 / 255.0);
    }
}


void mountain(Pyramid& pyramid, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    pahar(pyramid, 2.5, 2.5 , 2.5, -8, -0.5, -10, lightingShaderWithTexture, alTogether);
    pahar(pyramid, 2.5, 2.5, 2.5, -8, -0.5, -12, lightingShaderWithTexture, alTogether);
    pahar(pyramid, 2.5, 2.5, 2.5, -7, -0.5, -12.5, lightingShaderWithTexture, alTogether);
    pahar(pyramid, 2, 2, 2, -5.5, -0.5, -12.5, lightingShaderWithTexture, alTogether);

    pahar(pyramid, 2.5, 2.5, 2.5, 8, -0.5, -10, lightingShaderWithTexture, alTogether);
    pahar(pyramid, 2.5, 2.5, 2.5, 8, -0.5, -12, lightingShaderWithTexture, alTogether);
    pahar(pyramid, 2.5, 2.5, 2.5, 7, -0.5, -12.5, lightingShaderWithTexture, alTogether);
    pahar(pyramid, 2, 2, 2, 5.5, -0.5, -12.5, lightingShaderWithTexture, alTogether);

}


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(4.8f,  1.7f,  4.55f),
    glm::vec3(-6.0f,  1.4f,  5.0f),
    glm::vec3(2.4f, 11.5f, -19.0f),
    glm::vec3(0.0f,  3.0f,  0.0f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.7f, 0.7f, 0.7f,     // ambient
    0.7f, 0.7f, 0.7f,      // diffuse
    0.7f, 0.7f, 0.7f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.7f, 0.7f, 0.7f,     // ambient
    0.7f, 0.7f, 0.7f,      // diffuse
    0.7f, 0.7f, 0.7f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);


PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.7f, 0.7f, 0.7f,     // ambient
    0.7f, 0.7f, 0.7f,      // diffuse
    0.7f, 0.7f, 0.7f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);


PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.7f, 0.7f, 0.7f,     // ambient
    0.7f, 0.7f, 0.7f,      // diffuse
    0.7f, 0.7f, 0.7f,         // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);


// light settings
bool onOffPointToggle = true;
bool onOffSpotToggle = true;
bool onOffDirectToggle = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;

//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//glm::mat4 view = camera.GetViewMatrix();
glm::mat4 projection;
glm::mat4 view;

string diffuseMapPath;
string specularMapPath;
unsigned int diffMap;
unsigned int specMap;

//Cube cube;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


glm::mat4 transforamtion(float tx, float ty, float tz, float sx, float sy, float sz) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(tx, ty, tz));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(sx, sy, sz));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    return model;
}

void texture_draw(Shader& lightingShaderWithTexture,string diffuseMapPath, string specularMapPath,float x, float y, glm::mat4 model)
{
    shaderActivate(lightingShaderWithTexture);
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, x, y);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    
}

Cube nw_text_d(string diffuseMapPath, string specularMapPath, float x, float y)
{
    
    diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, x, y);
    
    return cube;

}

glm::mat4 model_mat(float width, float height, float length, float x, float y, float z)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, height, length));
    translate = glm::translate(model, glm::vec3(x,y,z));
    model = scale * translate;
    return model;
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    ////glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    // cylinder code

    float ver_arr[] = {

        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.809017f, 1.0f, 0.587785f, 0.809017f, 1.0f, 0.587785f,
        0.309017f, 1.0f, 0.951057f, 0.309017f, 1.0f, 0.951057f,
        -0.309017f, 1.0f, 0.951057f, -0.309017f, 1.0f, 0.951057f,
        -0.809017f, 1.0f, 0.587785f, -0.809017f, 1.0f, 0.587785f,
        -1.0f, 1.0f, 1.22465e-16f, -1.0f, 1.0f, 1.22465e-16f,
        -0.809017f, 1.0f, -0.587785f, -0.809017f, 1.0f, -0.587785f,
        -0.309017f, 1.0f, -0.951057f, -0.309017f, 1.0f, -0.951057f,
        0.309017f, 1.0f, -0.951057f, 0.309017f, 1.0f, -0.951057f,
        0.809017f, 1.0f, -0.587785f, 0.809017f, 1.0f, -0.587785f,

        1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
        0.809017f, -1.0f, 0.587785f, 0.809017f, -1.0f, 0.587785f,
        0.309017f, -1.0f, 0.951057f, 0.309017f, -1.0f, 0.951057f,
        -0.309017f, -1.0f, 0.951057f, -0.309017f, -1.0f, 0.951057f,
        -0.809017f, -1.0f, 0.587785f, -0.809017f, -1.0f, 0.587785f,
        -1.0f, -1.0f, 1.22465e-16f, -1.0f, -1.0f, 1.22465e-16f,
        -0.809017f, -1.0f, -0.587785f, -0.809017f, -1.0f, -0.587785f,
        -0.309017f, -1.0f, -0.951057f, -0.309017f, -1.0f, -0.951057f,
        0.309017f, -1.0f, -0.951057f, 0.309017f, -1.0f, -0.951057f,
        0.809017f, -1.0f, -0.587785f, 0.809017f, -1.0f, -0.587785f,


        1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
        0.809017f, -1.0f, 0.587785f, 0.809017f, -1.0f, 0.587785f,
        0.309017f, -1.0f, 0.951057f, 0.309017f, -1.0f, 0.951057f,
        -0.309017f, -1.0f, 0.951057f, -0.309017f, -1.0f, 0.951057f,
        -0.809017f, -1.0f, 0.587785f, -0.809017f, -1.0f, 0.587785f,
        -1.0f, -1.0f, 1.22465e-16f, -1.0f, -1.0f, 1.22465e-16f,
        -0.809017f, -1.0f, -0.587785f, -0.809017f, -1.0f, -0.587785f,
        -0.309017f, -1.0f, -0.951057f, -0.309017f, -1.0f, -0.951057f,
        0.309017f, -1.0f, -0.951057f, 0.309017f, -1.0f, -0.951057f,
        0.809017f, -1.0f, -0.587785f, 0.809017f, -1.0f, -0.587785f,

        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.809017f, 1.0f, 0.587785f, 0.809017f, 1.0f, 0.587785f,
        0.309017f, 1.0f, 0.951057f, 0.309017f, 1.0f, 0.951057f,
        -0.309017f, 1.0f, 0.951057f, -0.309017f, 1.0f, 0.951057f,
        -0.809017f, 1.0f, 0.587785f, -0.809017f, 1.0f, 0.587785f,
        -1.0f, 1.0f, 1.22465e-16f, -1.0f, 1.0f, 1.22465e-16f,
        -0.809017f, 1.0f, -0.587785f, -0.809017f, 1.0f, -0.587785f,
        -0.309017f, 1.0f, -0.951057f, -0.309017f, 1.0f, -0.951057f,
        0.309017f, 1.0f, -0.951057f, 0.309017f, 1.0f, -0.951057f,
        0.809017f, 1.0f, -0.587785f, 0.809017f, 1.0f, -0.587785f,


        0.0,-1.0,0.0, 0.0,-1.0,0.0,
        0.0,1.0,0.0, 0.0,1.0,0.0

    };

    unsigned int ind_arr[] = {
        0, 11, 1,
        11, 0, 10,
        1, 12, 2,
        12, 1, 11,
        2, 13, 3,
        13, 2, 12,
        3, 14, 4,
        14, 3, 13,
        4, 15, 5,
        15, 4, 14,
        5, 16, 6,
        16, 5, 15,
        6, 17, 7,
        17, 6, 16,
        7, 18, 8,
        18, 7, 17,
        8, 19, 9,
        19, 8, 18,
        9, 10, 0,
        10, 9, 19,

        40,20,21,
        40,21,22,
        40,22,23,
        40,23,24,
        40,24,25,
        40,25,26,
        40,26,27,
        40,27,28,
        40,28,29,
        40,29,20,

        41,30,31,
        41,31,32,
        41,32,33,
        41,33,34,
        41,34,35,
        41,35,36,
        41,36,37,
        41,37,38,
        41,38,39,
        41,39,30


        /*
        21,10,11,
        21,11,12,
        21,12,13,
        21,13,14,
        21,14,15,
        21,15,16,
        21,16,17,
        21,17,18,
        21,18,19,
        21,19,10*/

    };

    unsigned int cVAO, cVBO, cEBO;
    glGenVertexArrays(1, &cVAO);
    glGenBuffers(1, &cVBO);
    glGenBuffers(1, &cEBO);

    glBindVertexArray(cVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ver_arr), ver_arr, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind_arr), ind_arr, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);




    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    string swming_diff = "images/pool.png";
    string swming_spec = "images/pool.png";
    Cube swming_cube = nw_text_d(swming_diff, swming_spec, 5.0, 5.0);

    string gym_diff = "images/wood.jpg";
    string gym_spec = "images/wood.jpg";
    Cube gym_cube = nw_text_d(gym_diff, gym_spec, 4.0, 4.0);

    string wall_diff = "images/wood.jpg";
    string wall_spec = "images/wood.jpg";
    Cube wall_cube = nw_text_d(wall_diff, wall_spec, 2.0, 2.0);

    string b_diff = "images/gym.jpg";
    string b_spec = "images/gym.jpg";
    Cube b_cube = nw_text_d(b_diff, b_spec, 1.0, 1.0);

    string w_diff = "images/window.png";
    string w_spec = "images/window.png";
    Cube w_cube = nw_text_d(w_diff, w_spec, 1.0, 1.0);

    string d_diff = "images/door.png";
    string d_spec = "images/door.png";
    Cube d_cube = nw_text_d(d_diff, d_spec, 1.0, 1.0);


    //voleytext
    string diffuseMapPath_volley = "images/pic_volley.png";
    string specularMapPath_volley = "images/pic_volley.png";

    unsigned int diffMap_volley = loadTexture(diffuseMapPath_volley.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_volley = loadTexture(specularMapPath_volley.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Sphere2 volley_s = Sphere2(1.0f, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap_volley, specMap_volley, 0.0f, 0.0f, 300.0f, 300.0f);

    //pahar
    glm::mat4 model1 = glm::mat4(1.0f);
    Pyramid pyramid(model1, "images/hill.png");
    Pyramid ship(model1, "images/boat.png");

    bool ch = false;

    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);

    
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierVAO1 = hollowBezier(cntrlPoints1.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(173/255.0, 216/255.0, 230/255.0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);

        
        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        // glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        view = camera.GetViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);


       
       

        if (showHollowBezier)
        {

          

            glm::mat4 identityMatrix = glm::mat4(1.0f);
            glm::mat4 model3 = glm::mat4(1.0f);// make sure to initialize matrix to identity matrix first
            glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix;
            translateMatrix = glm::translate(identityMatrix, glm::vec3(6.2, -1, 0.15));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 2, 2));
            model3 = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
            lightingShader.setMat4("model", model3);
            //cout << "h" << endl;
            lightingShader.use();
            lightingShader.setVec3("material.ambient", glm::vec3(55/255.0, 144/255.0, 0.0f));
            lightingShader.setVec3("material.diffuse", glm::vec3(55 / 255.0, 144 / 255.0, 0.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);

            glBindVertexArray(bezierVAO1);
            glDrawElements(GL_TRIANGLES,                    // primitive type
                (unsigned int)indices.size(),          // # of indices
                GL_UNSIGNED_INT,                 // data type
                (void*)0);                       // offset to indices

            // unbind VAO
            glBindVertexArray(0);


        }



        for (int i = 0; i < 3; i++)
        {
            z_x[i] += 0.12;
            x_x[i] += (0.004+ i* 0.001);

            if (z_x[0] > 10)
            {
                z_x[0] = 0.0;
                x_x[0] = 0.0;
            }
            if (z_x[1] > 8)
            {
                z_x[1] = 0.0;
                x_x[1] = 0.0;
            }
            if (z_x[2] > 6)
            {
                z_x[2] = 0.0;
                x_x[2] = 0.0;
            }
        }
       

        

        human(cVAO, lightingShader,1, 0, 0 );

        human2(cVAO, lightingShader, 1, 0, 0);

        if (ch == false)
        {
            

            voley(cubeVAO, lightingShader, model);
           // boat(ship, cubeVAO, lightingShader,lightingShaderWithTexture, model);
            machine_1(cubeVAO, lightingShader, model, -2);
            machine_1(cubeVAO, lightingShader, model, 0);
            machine_1(cubeVAO, lightingShader, model, 2);

            machine_1(cubeVAO, lightingShader, model, 4);

            machine_2(cubeVAO, lightingShader, model, 2);
            machine_3(cubeVAO, lightingShader, model, 2);
            tree(cVAO, lightingShader, model);
            mountain(pyramid, lightingShaderWithTexture, model);


            sun(volley_s, 0.06, 0.06, 0.06, -4.55, 0.5 + b_x, 3.3 + b_y, cubeVAO, lightingShaderWithTexture, model);

            swimming_pool(swming_cube, lightingShader, model, lightingShaderWithTexture);
            scene(cVAO, lightingShader, ourShader);
           // voley(cubeVAO, lightingShader, model);
            road(cubeVAO, lightingShader, model, lightingShaderWithTexture);
            gym(gym_cube, lightingShader, model, lightingShaderWithTexture);
            sun2(3, 12, -20, lightingShader, model);
            road_fence(cubeVAO, cVAO, lightingShader, model);
            spa_center(wall_cube, b_cube, w_cube, d_cube, cubeVAO, cVAO, lightingShader, model, lightingShaderWithTexture);
            spa_road(cubeVAO, cVAO, lightingShader, model, lightingShaderWithTexture);

            disco_Light(cubeVAO, cVAO, lightingShader, model, lightingShaderWithTexture);

            watch_tower(cubeVAO, cVAO, lightingShader, model, lightingShaderWithTexture);

            ball(-4.55, 0.85 , 3.5, lightingShader, model);

           ball(-4.55, 0.85, 3.5 -3.05, lightingShader, model);

          

          
            
        }
       


        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 3; i < 3; i++)
        {
            glm::mat4 identityMatrix = glm::mat4(1.0f);
            model = glm::mat4(1.0f);
            glm::mat4 t1, t2;
            t1 = glm::scale(identityMatrix, glm::vec3(.2f)); // Make it a smaller cube
            t2 = glm::translate(identityMatrix, pointLightPositions[i]);
            model = t2 * t1;
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        

        ////texture
        //glm::mat4 modelTexture = glm::mat4(1.0f);
        //glm::mat4 translate = glm::mat4(1.0f);
        //glm::mat4 scale = glm::mat4(0.5f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X+1, translate_Y+1, translate_Z + 1));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X * 0.5, scale_Y * 0.5, scale_Z * 0.5));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("view", view);
        lightingShaderWithTexture.setMat4("projection", projection);

        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);

      


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    } 



    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void shaderActivate(Shader& shader)
{
    shader.use();
    shader.setVec3("viewPos", camera.Position);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}



void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}




void scene(unsigned int& cVAO, Shader& lightingShader, Shader& ourShader)
{

    glm::mat4 model = glm::mat4(1.0f);

    
    model = glm::mat4(1.0f);

    for (int i = 0; i < 3; i++) {

        model = transforamtion(-.0, 0.01 - x_x[i], -11.0 + z_x[i] + i*2, .2, 7.5, 0.2);

        drawCylinder(cVAO, lightingShader, model, 127 / 255.0, 205 / 255.0, 255 / 255.0);
    }

    

}





void gym(Cube& cube, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture)
{
    float baseHeight = 0.01;
    float width = 15.0;
    float length = 8.5;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.2));
    model = alTogether * scale * translate;
   // drawCube(cubeVAO, lightingShader, model, 194 / 255.0, 178 / 255.0, 128 / 255.0);

    shaderActivate(lightingShaderWithTexture);
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    shaderActivate(lightingShader);

                                

}

void spa_road(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture)
{
 
    glm::mat4 model = glm::mat4(1.0f);
    model = alTogether * model_mat(0.8, 0.02, 1.1, 8.0, 0.0, 4.3);
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    model = alTogether * model_mat(2.5, 0.02, 0.8, 1.6, 0.0, 5.9);
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    model = alTogether * model_mat(2.5, 0.02, 0.8, 1.6, 0.0, 5.9);
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.1, 1.0, 4.65));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03, 1, 0.03));
    model = translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 83/255.0, 83/255.0, 83/255.0);

    model = alTogether * model_mat(0.15, 0.01, 0.01, 33, 180, 465);
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    model = alTogether * model_mat(0.1, 0.01, 0.1, 48.5, 178, 46);
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    model = alTogether * model_mat(0.1, 0.07, 0.1, 48.5, 24.5, 46);
    drawCube(cubeVAO, lightingShader, model, 0.8f, 0.8f, 0.8f);

    


}

void watch_tower(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture)
{

    glm::mat4 model = glm::mat4(1.0f);
   

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.50, 1.0, 5.65));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03, 1, 0.03));
    model = translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95/255.0, 48/255.0, 31/255.0);

    identityMatrix = glm::mat4(1.0f);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.50, 1.0, 5.1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03, 1, 0.03));
    model = translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95 / 255.0, 48 / 255.0, 31 / 255.0);

    identityMatrix = glm::mat4(1.0f);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.8, 1.0, 5.65));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03, 1, 0.03));
    model = translateMatrix * scaleMatrix;
    drawCylinder(cVAO, lightingShader, model, 95 / 255.0, 48 / 255.0, 31 / 255.0);

    
    model = alTogether * model_mat(0.8, 0.05, 0.8, -8.2, 25.0, 6.25);
    drawCube(cubeVAO, lightingShader, model, 0.8f, 0.8f, 0.8f);



}

void spa_center(Cube& cube1, Cube& cube2, Cube& cube3, Cube& cube4,unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture)
{
    float baseHeight = 0.05;
    float width = 2.5;
    float length = 3;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(2.0, 0.2, 0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    baseHeight = 1.8;
    width = 2.2;
    length = 3;

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(2.5, 0.0, 0.5));
    model = alTogether * scale * translate;
   // drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    shaderActivate(lightingShaderWithTexture);
    cube1.drawCubeWithTexture(lightingShaderWithTexture, model);
    shaderActivate(lightingShader);


    for (int i = 0; i < 2; i++) {

        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.6, 2, 2.5 + i));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03, 0.2, 0.03));
        model = translateMatrix * scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 0 / 255.0, 84 / 255.0, 147 / 255.0);

    }

    baseHeight = 0.6;
    width = 0.02;
    length = 1.2;

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(278, 3.2, 2.01));
    model = alTogether * scale * translate;
   // drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);
    
    shaderActivate(lightingShaderWithTexture);
    cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
    shaderActivate(lightingShader);

    model = alTogether * model_mat(0.8, 0.8, 0.025, 7.7, 0.4, 180);
    shaderActivate(lightingShaderWithTexture);
    cube3.drawCubeWithTexture(lightingShaderWithTexture, model);
    shaderActivate(lightingShader);


    model = alTogether * model_mat(0.025, 1.0, 0.6, 218, 0.08, 5.0);
    shaderActivate(lightingShaderWithTexture);
    cube4.drawCubeWithTexture(lightingShaderWithTexture, model);
    shaderActivate(lightingShader);

    model = alTogether * model_mat(2.7, 0.05, 3.2, 1.85, 36.0, 0.45);
    drawCube(cubeVAO, lightingShader, model, 0.8f, 0.8f, 0.8f);
    

}

void road_fence(unsigned int& cubeVAO, unsigned int& cVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.02;
    float width = 15.0;
    float length = 0.02;

    for (int i = 0; i < 3; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);
        glm::mat4 translate2 = glm::mat4(1.0f);
        glm::mat4 scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(width, baseHeight, length));
        translate = glm::translate(model, glm::vec3(-0.5, 10+(i*5), 290));
        model = alTogether * scale * translate;
        drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);
    }

    for (int i = 0; i < 16; i++) {

        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.5 + i, 0.3, 5.82));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.03, 0.3, 0.03));
        model = translateMatrix *  scaleMatrix;
        drawCylinder(cVAO, lightingShader, model, 206/255.0, 211/255.0, 212/255.0);

    }

    
}

void road(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture)
{


    float baseHeight = 0.2;
    float width = 15.0;
    float length = 1.1;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, -0.5, 5.26));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);


    baseHeight = 0.01;
    width = 15.0;
    length = 1.0;

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 9.1, 5.85));
    model = alTogether * scale * translate;


    
    string diffuseMapPath = "images/road_image.jpg";
    string specularMapPath = "images/road_image.jpg";
    texture_draw(lightingShaderWithTexture, diffuseMapPath, specularMapPath, 4.0, 1.0, model);
    shaderActivate(lightingShader);
}

void swimming_pool(Cube &cube,Shader& lightingShader, glm::mat4 alTogether, Shader& lightingShaderWithTexture)
{
    float baseHeight = 0.01;
    float width = 15.0;
    float length = 10;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -1.17));
    model = alTogether * scale * translate;
  

    shaderActivate(lightingShaderWithTexture); 
    cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    shaderActivate(lightingShader);
}


void voley(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{


    float baseHeight = 1.2;
    float width = 0.02;
    float length = 0.02;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-300.0, -0.0, 100.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-150.0, -0.0, 100.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);

    baseHeight = 0.02;
    width = 3.0;
    length = 0.005;
    for (int i = 1; i <= 2; i++)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(width, baseHeight, length));
        translate = glm::translate(model, glm::vec3(-2.0, 25.0 * i, 400.0));
        model = alTogether * scale * translate;
        drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 255 / 255.0, 255 / 255.0);
    }

    baseHeight = 0.5;
    width = 0.02;
    length = 0.005;

    for (int i = 0; i < 30; i++)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(width, baseHeight, length));
        translate = glm::translate(model, glm::vec3(-150.0 - (i * 5), 1.0, 400.0));
        model = alTogether * scale * translate;
        drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 255 / 255.0, 255 / 255.0);

    }

    baseHeight = 0.02;
    width = 2.85;
    length = 0.005;
    for (int i = 1; i <= 4; i++)
    {
        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(width, baseHeight, length));
        translate = glm::translate(model, glm::vec3(-2.08, 25.0 + (i * 5), 400.0));
        model = alTogether * scale * translate;
        drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 255 / 255.0, 255 / 255.0);
    }


}

void machine_1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 2)
{

    float baseHeight = 0.03;
    float width = 0.5;
    float length = 1.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(0.0 + x, 1.4, 0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);


    baseHeight = 0.1;
    width = 0.03;
    length = 0.03;

    for (int i = 0; i < 2; i++)
    {

        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(width, baseHeight, length));
        translate = glm::translate(model, glm::vec3(1.0 + (x * 16.5), -0.3, 18.0 + (i * 28)));
        model = alTogether * scale * translate;
        drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 128 / 255.0, 0 / 255.0);

        model = glm::mat4(1.0f);
        translate = glm::mat4(1.0f);
        scale = glm::mat4(1.0f);
        scale = glm::scale(model, glm::vec3(width, baseHeight, length));
        translate = glm::translate(model, glm::vec3(15.0 + (x * 16.5), -0.3, 18.0 + (i * 28)));
        model = alTogether * scale * translate;
        drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 128 / 255.0, 0 / 255.0);

    }

    baseHeight = 0.03;
    width = 0.5;
    length = 0.4;

    glm::mat4  rotateYMatrix;

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length*1.8));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 0.05, 1.5));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 128 / 255.0, 0 / 255.0);

    //head_2

    baseHeight = 0.03;
    width = 0.5;
    length = 1.0;

    model = glm::mat4(1.0f);

    scale = glm::scale(model, glm::vec3(width, baseHeight, length / 2));
    translate = glm::translate(model, glm::vec3(0.0 + x, 23.0, 2.17));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 86 / 255.0, 86 / 255.0, 86 / 255.0);


}

void machine_2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 2)
{

    float baseHeight = 0.03;
    float width = 0.05;
    float length = 1.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    //part_3
    glm::mat4  rotateYMatrix;

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 0.05, 2.52));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_1
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width * 1.5, baseHeight * 1.5, length / 2));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 1.05, 2.5));
    rotateYMatrix = glm::rotate(model, glm::radians(-135.0f + rx), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_2
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width * 1.5, baseHeight * 1.5, length / 2 + 0.05));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 1.05, 2.5));
    rotateYMatrix = glm::rotate(model, glm::radians(-35.0f - rx), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_4
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width * 2, baseHeight * 10, length / 5));
    translate = glm::translate(model, glm::vec3(-0.05 + x / 2.0, 0.05 + ty, 2.65));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);
}

void machine_3(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether, float x = 2)
{
    float baseHeight = 0.03;
    float width = 0.05;
    float length = 1.0;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);

    //part_1
    glm::mat4  rotateYMatrix;

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight*2, length*2));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 0.05, 2.52 + 1));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_2
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width * 1.5, baseHeight * 1.5, length / 2));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 2, 2.5+1));
    rotateYMatrix = glm::rotate(model, glm::radians(0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 0 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_3
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width , baseHeight , length *2 ));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 0.05, 2.52 + 1 + 0.5));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_4
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight*10, length/2.5));
    translate = glm::translate(model, glm::vec3(0.0 + x / 2.0, 0.05 +m3_ty, 2.52 + 1 + 0.5+0.12));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_5_1
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight * 1.6, length / 3.5));
    translate = glm::translate(model, glm::vec3(-0.05 + x / 2.0, 0.05+0.5  , 2.52 + 1));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f - m3_rx), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);

    
    //part_5_2
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight * 1.6, -(length / 3.5)));
    translate = glm::translate(model, glm::vec3(-0.05 + x / 2.0, 0.05 + 0.5, 2.52 + 1));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f - m3_rx ), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_5_3
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, -(length / 3.5),baseHeight * 1.6));
    translate = glm::translate(model, glm::vec3(-0.05 + x / 2.0, 0.05 + 0.5, 2.52 + 1));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f - m3_rx), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);

    //part_5_4
    model = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, (length / 3.5), baseHeight * 1.6));
    translate = glm::translate(model, glm::vec3(-0.05 + x / 2.0, 0.05 + 0.5, 2.52 + 1));
    rotateYMatrix = glm::rotate(model, glm::radians(90.0f - m3_rx), glm::vec3(-1.0f, 0.0f, 0.0f));
    model = alTogether * translate * rotateYMatrix * scale;
    drawCube(cubeVAO, lightingShader, model, 255 / 255.0, 0 / 255.0, 0 / 255.0);
    
    

}

void sun2(float tx, float ty, float tz, Shader& lightingShader, glm::mat4 alTogether)
{
    float r = 253 / 255.0, g = 184 / 255.0, b = 19 / 255.0;
    Sphere sphere = Sphere(1, 36, 18, glm::vec3(r, g, b), glm::vec3(r, g, b), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
    
    //  Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, glm::vec3 amb = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 diff = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f), float shiny = 32.0f) : verticesStride(24)

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(sx, sy, sz));
   // scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(identityMatrix, glm::vec3(tx, ty, tz));
  
    model = alTogether * translate;
    sphere.drawSphere(lightingShader, model);
}

void ball(float tx, float ty, float tz, Shader& lightingShader, glm::mat4 alTogether)
{
    float r = 224 / 255.0, g = 172 / 255.0, b = 105 / 255.0;
    Sphere sphere = Sphere(0.06, 36, 18, glm::vec3(r, g, b), glm::vec3(r, g, b), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);

    //  Sphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18, glm::vec3 amb = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 diff = glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3 spec = glm::vec3(0.5f, 0.5f, 0.5f), float shiny = 32.0f) : verticesStride(24)

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(sx, sy, sz));
   // scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(identityMatrix, glm::vec3(tx, ty, tz));

    model = alTogether * translate;
    sphere.drawSphere(lightingShader, model);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        //eyeZ -= 2.5 * deltaTime;
        //basic_camera.changeEye(eyeX, eyeY, eyeZ);

        if (rx < 22)
        {
            rx += 2;
            ty += 0.05;
            cout << rx << endl;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        if (rx > 0)
        {
            rx -= 2;
            ty -= 0.05;
            cout << rx << endl;
        }
    }


    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if (m3_rx < 620)
        {
            m3_rx += 20;
            m3_ty += 0.05;
        }
        

        cout << "m3_rx " << m3_rx<<endl;
        cout << "m3_ty " << m3_ty<<endl;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        if (m3_rx > 0)
        {
            m3_rx -= 20;
            m3_ty -= 0.05;
        }
        
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        if (onOffPointToggle)
        {
            pointlight1.turnOff();

            onOffPointToggle = !onOffPointToggle;
        }
        else
        {
            pointlight1.turnOn();

            onOffPointToggle = !onOffPointToggle;
        }

    }


    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {

        if (onOffSpotToggle)
        {

            pointlight2.turnOff();
            onOffSpotToggle = !onOffSpotToggle;
        }
        else
        {
            pointlight2.turnOn();
            onOffSpotToggle = !onOffSpotToggle;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {

        if (onOffSpotToggle)
        {

            pointlight3.turnOff();
            onOffSpotToggle = !onOffSpotToggle;
        }
        else
        {
            pointlight3.turnOn();
            onOffSpotToggle = !onOffSpotToggle;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {

        z_x[0] += 0.2;
        x_x[0] += 0.005;

        if (z_x[0] > 6)
        {
            z_x[0] = 0.0;
            x_x[0] = 0.0;
        }
    }

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {

        

        cout << b_y << endl;
        if (b_y <= 0.0 && b_y >= -1.3)
        {
            b_y -= 0.05;
            b_x += 0.022;
            h_x += 0.5;
        }
        else if (b_y <= -1.3 && b_y >= -2.6)
        {
            b_y -= 0.05;
            b_x -= 0.022;
            h_x -= 0.05;
        }
        if (b_y <= -2.6)
        {
            b_y = -2.6;
            b_x = 0.0;
            h_x = 0;
        }

        
    }

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {



        if (b_y <= -1.3 && b_y >= -2.6)
        {
            b_y += 0.05;
            b_x += 0.022;
            h_x2 -= 0.5;
        }
        else if (b_y <= 0.0 && b_y >= -1.3)
        {
            b_y += 0.05;
            b_x -= 0.022;
            h_x2 += 0.5;
        }

        if (b_y >= 0.0)
        {
            b_y = 0.0;
            b_x = 0.0; 
            h_x2 = 0;
        }
       


    }

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {



        boat_x -= 0.01;



    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}



long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}

