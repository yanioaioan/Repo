#pragma once

#include "GameModels.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>

#include <iostream>
#include "display.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//usefull vec3 print command
#define printVec3(a,b,c) std::cout<<a<<","<<b<<","<<c<<std::endl;

glm::mat4 matrixFromAxisAngle(glm::vec3 axis, float angle) ;


Models::GameModels* gameModels;
GLuint program;
int ScreenWidth=800;int ScreenHeight=600;

//void roll( float angle, glm::vec3 upvector )
//{
//// roll the camera through angle degrees
//float cs = cos( M_PI/180 * angle );
//float sn = sin( M_PI/180 * angle );
//glm::vec3 t = upvector; // remember old u

//upvector = glm::vec3(cs*t.x -sn*v.x, cs*t.y -sn.v.y, cs*t.z -sn.v.z );
////v = ( sn*t.x+ cs*v.x,sn*t.y+ cs.v.y,sn*t.z+ cs.v.z );
////setModelViewMatrix( );
//}



Display display(ScreenWidth,ScreenHeight,"");

//static float angle;

enum rotationAxisFlag
{
    y,
    x,
    z
}
rotationAxisFlag=y;

glm::mat4 Model = glm::mat4(1);
glm::mat4 Model2 = glm::mat4(1);

glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::vec3(0,0,0));//glm::mat4(1);
glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-1));//glm::mat4(1);

glm::mat4 rotationMatrix = glm::mat4(1);
glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(1,1,1));


static bool translate=true;
static int temp;

glm::vec4 newUp(0,1,0,0);

static float z_rot;

void renderScene(void)
 {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.3, 0.3, 1.0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_DEPTH_CLAMP);
  glEnable( GL_MULTISAMPLE );

  glBindVertexArray(gameModels->GetModel("cube1"));

  glUseProgram(program);

  //Load Matrices to Shader START
  // Model matrix : an identity matrix (model will be at the origin)

//  printVec3(1,2,3);

  float angle = 0;


  if(display.m_flagLocalX)
  {
      angle = display.m_angleX;

      rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(1,0,0));//the rotation matrix is multiplied with itself producing a local coordinate rotation
      translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,0));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

      translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-1));//Used to form another Model matrix rotating around the main colored Cube


  }

  if(display.m_flagLocalY)
  {
     angle = display.m_angleY;

     rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(0,1,0));//the rotation matrix is multiplied with itself producing a local coordinate rotation
     translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,0));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

     translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-1));//Used to form another Model matrix rotating around the main colored Cube

  }

  if(display.m_flagLocalZ)
  {
    angle = display.m_angleZ;

    rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(0,0,1));//the rotation matrix is multiplied with itself producing a local coordinate rotation
    translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,0));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

    translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-1));//Used to form another Model matrix rotating around the main colored Cube

    // Roll section
    z_rot+=angle;
  }

    //  translationMatrix = glm::translate(glm::mat4(1), glm::vec3(0.5,0,0));//glm::mat4(1);

    //  Model =  translationMatrix*rotationMatrix;
    //  Model =  rotationMatrix *translationMatrix*scaleMatrix;


//      Right to left evaluation (because of OpenGL Column-Major matrices) ... so at first ROTATE .. and then TRANSLATE ()

//      Often used order. Rotate and place wherever we want locally
        Model =  translationMatrix*rotationMatrix*scaleMatrix;
//      Could be used to Rotate around the origin with the radius of translationMatrix
//      Model =  rotationMatrix * translationMatrix * scaleMatrix;


     Model2 = rotationMatrix*translationMatrix2*scaleMatrix;//Flipped rotationMatrix with translationMatrix to achieve rotation around a single point


//   Pre- or post-multiplication just defines the order of operations how the member of that matrix and vector are multiplied, its purely a notational convention.
//   The common operations in 3D graphics are post-multiplying a row-vector with column-major matrices (OpenGL) and pre-multiplying a column-vector with row-major matrices (DirectX).
//   Both are basically the same operations with the same results, just the notational convention is different.


//  prevent from continuous rotation
    display.m_flagLocalX=false;
    display.m_flagLocalY=false;
    display.m_flagLocalZ=false;

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), ScreenWidth / (float)ScreenHeight, 0.5f, 500.f);

//  Camera matrix
    glm::vec3 newcameraposition(Model2[3][0], Model2[3][1], Model2[3][2]);
    glm::vec3 target(Model[3][0], Model[3][1], Model[3][2]);
    glm::vec3 cameraDirection = target-newcameraposition;
    glm::normalize(cameraDirection);
    glm::vec4 upVec = glm::vec4(0,1,0,0);
    glm::vec3 rightVec = glm::cross(glm::vec3(upVec),cameraDirection);
    glm::normalize(rightVec);
    newUp= glm::vec4(glm::cross(cameraDirection,rightVec),0);

    glm::mat4 tmpmat=matrixFromAxisAngle(cameraDirection, -z_rot*(M_PI/180));//to be used for roll only! so, if there's a rotation specified for z it will roll

    newUp =  tmpmat*upVec;

//  printVec3(newcameraposition.x,newcameraposition.y,newcameraposition.z)

//  Model2 = glm::translate(Model, glm::vec3(0,0,-200));
//  glm::mat4 View = Model2;

//  printVec3(Model2[3][0], Model2[3][1], Model2[3][2])

    // Recompute Up Vector -  Supporting Roll (around Z axis)
    glm::mat4 View = glm::lookAt(
                              glm::vec3(Model2[3][0]*400, Model2[3][1]*400, Model2[3][2]*400/*0,0,-450*/),
                              glm::vec3(Model[3][0]*200, Model[3][1]*200, Model[3][2]*200), // and looks at the origin
                              glm::vec3(newUp) /*glm::vec3(0,1,0)*/  // Head is up (set to 0,-1,0 to look upside-down)
                              );


    // Standar Up Vector - Not Supporting Roll (around Z axis) - Camera Tracking the player object
//    glm::mat4 View = glm::lookAt(
//                              glm::vec3(/*0,0,-450*/Model2[3][0]*400, Model2[3][1]*400, Model2[3][2]*400),
//                              glm::vec3(Model[3][0]*200, Model[3][1]*200, Model[3][2]*200), // and looks at the origin
//                              glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                              );

    // Standar Up Vector - Not Supporting Roll (around Z axis)- Camera Statically Placed - NOT Tracking the player object
//    glm::mat4 View = glm::lookAt(
//                              glm::vec3(0,0,-450),
//                              glm::vec3(Model[3][0]*200, Model[3][1]*200, Model[3][2]*200), // and looks at the origin
//                              glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                              );

//  Our ModelViewProjection : multiplication of our 3 matrices
//  Model = glm::mat4(1);
//  Model =glm::translate(Model,glm::vec3(0,0,-10));

    glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication works the other way around (<----<----<)

    glm::mat4 MVP2       = Projection * View * Model2; // Remember, matrix multiplication works the other way around (<----<----<)

    //reset to origin
    //  glm::mat4 MVP(1);

    // Get a handle for our "MVP" uniform.
    // Only at initialisation time.
    GLuint MatrixID = glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //Load Matrices to Shader END



    // Cube 1 DRAWING

    glDrawArrays(GL_TRIANGLES, 0, 36);//cube made of 36 vertices (6 planes * 2 triangles * 3 vertices each = 36 vertices passed onto)
    glBindVertexArray(0);

    //  Cube 2 DRAWING

    // Now grab and draw the second cube (Note this is switching to the new generated VAO)

    //Load Matrices to Shader END
    glBindVertexArray(gameModels->GetModel("cube2"));
    glUseProgram(program);
    glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);//cube made of 36 vertices
    glBindVertexArray(0);



//    GRID DRAWING

//    glLineWidth((GLfloat)2.5f);





    glBindVertexArray(gameModels->GetModel("Grid"));
    glUseProgram(program);
    glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    Model = glm::mat4(1);

    MVP        = Projection * View * Model;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


//    glDrawArrays(GL_LINES, 0, 3200 );//draw grid


    /////////////////////////////
    glBindBuffer(GL_ARRAY_BUFFER,gameModels->Gridvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Set Uniform color for the grid
    GLuint colorUniformAttr = glGetUniformLocation(gameModels->m_shaderProgramId, "mycolor");//or 'zero' instead of retrieving the reference to the attribute "position input"
    GLfloat uniformColor[] = { 0.3f, 0.2f, 0.25f, 1.0f};
    glUniform4fv(colorUniformAttr, 1, uniformColor);

    //Draw Horizontal Lines
    for(int i = 0; i < 101; i++)
    {
      glDrawArrays(GL_LINE_STRIP, 101 * i, 101);
//    That works, although we did make 101 OpenGL calls,
//    which is not so much, but one would rather avoid doing that.
//    We also need to draw vertical lines, but the vertices are not in the right order!
//    Although, in this case, we can cheat by using the stride and pointer parameters:
    }

    //Draw Vertical Lines
    for(int i = 0; i < 101; i++) {
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 101 * sizeof(Models::point), (void *)(i * sizeof(Models::point)));//draw every other 12 bytes (cause struct point contains 3 GLFloats and so..3*4bytes=12 bytes)
      glDrawArrays(GL_LINE_STRIP, 0, 101);
    }
    /////////////////////////////


    uniformColor[0] = 0;

    // Unbind VAO of the grid
    glBindVertexArray(0);


//     Draw a grid in immediate mode "quickly"!
//     glBegin(GL_LINES);
//     for (GLfloat i = -10; i <= 10; i += 1) {
//       glVertex3f(i, 0, 10); glVertex3f(i, 0, -10);
//       glVertex3f(10, 0, i); glVertex3f(-10, 0, i);
//     }
//     glEnd();

}

void Init()
{

    //Trivial SDL initializations
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    //load and compile shaders
    Shader shader;
    shader.InitShaders("./shaders/shader.vs", "./shaders/shader.fs");
    program = shader.getProgramShaderId();

    //Enable Vaos & Load
    gameModels = new Models::GameModels(program);
    gameModels->CreateCubeModel("cube1");
    gameModels->CreateCubeModel2("cube2");
    gameModels->CreateGrid("Grid");
//    gameModels->createVBOgrid("VBOGrid");


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.5f, 150.f);
    //  Pass in the projection matrix to our model so we can pass it to the vertex shader
    gameModels->SetProjectionMatrix(Projection);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
                                glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                );

    gameModels->SetViewMatrix(View);

}




glm::mat4 matrixFromAxisAngle(glm::vec3 axis, float angle) {

    glm::mat4 tmp;

    double c = cos(angle);
    double s = sin(angle);
    double t = 1.0 - c;
    //  if axis is not already normalised then uncomment this
    // double magnitude = sqrt(axis.x*axis.x + axis.y*axis.y + axis.z*axis.z);
    // if (magnitude==0) throw error;
    // axis.x /= magnitude;
    // axis.y /= magnitude;
    // axis.z /= magnitude;

    tmp[0][0] = c + axis.x*axis.x*t;
    tmp[1][1] = c + axis.y*axis.y*t;
    tmp[2][2] = c + axis.z*axis.z*t;


    double tmp1 = axis.x*axis.y*t;
    double tmp2 = axis.z*s;
    tmp[1][0] = tmp1 + tmp2;
    tmp[0][1] = tmp1 - tmp2;
    tmp1 = axis.x*axis.z*t;
    tmp2 = axis.y*s;
    tmp[2][0] = tmp1 - tmp2;
    tmp[0][2] = tmp1 + tmp2;
    tmp1 = axis.y*axis.z*t;
    tmp2 = axis.x*s;
    tmp[2][1] = tmp1 + tmp2;
    tmp[1][2] = tmp1 - tmp2;

    return tmp;
}



int main(int argc, char **argv)
{
 glewInit();

 Init();

    while(!display.isClosed())
    {
        //  Clear background
        display.clear(0,0.05,0.05,1);

        renderScene();

        display.update();
    }


 delete gameModels;
 glDeleteProgram(program);

 return 0;



//    unsigned char arr[10] = {547643754884864,43,46,4,5,76,43,34,57,193};

//    std::cout<< "Array" <<std::endl;

//    for(unsigned i=0; i<10; ++i)
//        std::cout<< arr[i] << " ";

//    std::cout<<std::endl;



}
