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
float z_rot=0;


Models::GameModels* gameModels;
GLuint program;
int ScreenWidth=800;int ScreenHeight=600;


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
glm::mat4 Model2 = glm::mat4(1);//used to transform the white cube - representing camera

glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::vec3(0,0,0));//glm::mat4(1);

glm::mat4 rotationMatrix = glm::mat4(1);
glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(0.5,0.5,0.5));

glm::mat4 translationMatrix2 =glm::translate(glm::mat4(1), glm::vec3(0,0,-0.5));///used to transform the white cube - representing camera

static bool translate=true;
static int temp;

void renderScene(void)
 {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.3, 0.3, 1.0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_DEPTH_CLAMP);
  glEnable( GL_MULTISAMPLE );


  glBindVertexArray(gameModels->GetModel("plane1"));

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

      translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-0.5));//Used to form another Model matrix rotating around the main colored Cube
  }

  if(display.m_flagLocalY)
  {
     angle = display.m_angleY;

     rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(0,1,0));//the rotation matrix is multiplied with itself producing a local coordinate rotation
     translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,0));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

     translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-0.5));//Used to form another Model matrix rotating around the main colored Cube
  }

  if(display.m_flagLocalZ)
  {
    angle = display.m_angleZ;

    rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(0,0,1));//the rotation matrix is multiplied with itself producing a local coordinate rotation
    translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,0));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

    translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,0,-0.5));//Used to form another Model matrix rotating around the main colored Cube

  }

//  translationMatrix = glm::translate(glm::mat4(1), glm::vec3(0.5,0,0));//glm::mat4(1);

//    Model =  translationMatrix*rotationMatrix;
//    Model =  rotationMatrix *translationMatrix*scaleMatrix;


// Right to left evaluation (because of OpenGL Column-Major matrices) ... so at first ROTATE .. and then TRANSLATE ()
    Model =  translationMatrix*rotationMatrix*scaleMatrix;//Often used order. Rotate and place wherever we want locally
//   Model =  rotationMatrix * translationMatrix * scaleMatrix;//Could be used to Rotate around the origin with the radius of translationMatrix



    Model2 =  rotationMatrix*translationMatrix2*scaleMatrix;//2nd formed Model Matrix



//   Pre- or post-multiplication just defines the order of operations how the member of that matrix and vector are multiplied, its purely a notational convention.

//   The common operations in 3D graphics are post-multiplying a row-vector with column-major matrices (OpenGL) and pre-multiplying a column-vector with row-major matrices (DirectX).

//   Both are basically the same operations with the same results, just the notational convention is different.



  //prevent from continues rotation
  display.m_flagLocalX=false;
  display.m_flagLocalY=false;
  display.m_flagLocalZ=false;



//  glm::mat4 Projection = gameModels->GetProjectionMatrix();//always the same probably
//  glm::mat4 View = gameModels->GetViewMatrix();//always the same probably

  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), ScreenWidth / (float)ScreenHeight, 0.5f, 500.f);



      glm::vec4 cameraUp;
      glm::vec3 cameraTarget,cameraDirection;
      glm::vec3 newcameraPosiiton = glm::vec3(Model2[3][0], Model2[3][1], Model2[3][2]);

      //find new up vector
      cameraTarget =glm::vec3((Model[3][0], Model[3][1], Model[3][2]));
      cameraDirection = (newcameraPosiiton - cameraTarget);
      glm::normalize(cameraDirection);
      glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
      glm::vec3 cameraRight = glm::vec3(glm::cross(up, cameraDirection));
      glm::normalize(cameraRight);

      cameraUp =glm::vec4(glm::cross(cameraDirection, cameraRight),1);


// Calculate & Store Rotation
float x_rot = atan2(Model[1][2],Model[2][2]);
float M_00 = Model[0][0];
float M_01 = Model[0][1];
float y_rot = atan2( Model[0][2], sqrt(M_00*M_00 + M_01*M_01) );

// This way, any gimbal lock instability in the value of x_rot is fed back into the extraction process, and will be counteracted in the value computed for z_rot. Note that this method of extracting the 3rd (z) angle makes no assumptions about the other two angles, so that it can be applied in the non-gimbal lock cases too, and no conditional branches are needed

float s1 = sin(x_rot);
float c1 = cos(x_rot);
float z_rot = atan2(s1*Model[2][0]-c1*Model[1][0], c1*Model[1][1]-s1*Model[2][1]);


glm::mat4 matRot=matrixFromAxisAngle(cameraDirection, z_rot);
cameraUp=matRot*cameraUp;

printVec3(z_rot,z_rot,z_rot)

//      printVec3(cameraUp.x,cameraUp.y,cameraUp.z);



glm::mat4 View = glm::lookAt(
                          glm::vec3(0,20,-450), // Camera is at (4,3,3), in World Space
                          glm::vec3(0,0,0), // and looks at the origin
                          glm::vec3(cameraUp)  // Head is up (set to 0,-1,0 to look upside-down)
                          );
  // Our ModelViewProjection : multiplication of our 3 matrices
  // Remember, matrix multiplication works the other way around (<----<----<)
  glm::mat4 MVP        = Projection * View * Model;

//  View = glm::lookAt(
//                              glm::vec3(0,20,-450), // Camera is at (4,3,3), in World Space
//                              glm::vec3(0,0,0), // and looks at the origin
//                              glm::vec3(0,1,0) //Head is up (set to 0,-1,0 to look upside-down)
//                              );
//  Model2=glm::mat4(1);
  glm::mat4 MVP2        = Projection * View * Model2;




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

//  glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
////  glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
////  glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
//  glm::mat4 View = glm::lookAt(
//                    glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
//                    glm::vec3(0,0,0), // and looks at the origin
//                    glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                );
//  glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
//  glm::mat4 MVP = Projection * View * Model;
//  GLuint LocationMVP = glGetUniformLocation(program, "MVP");
//  glUniformMatrix4fv(LocationMVP, 1, GL_FALSE, glm::value_ptr(MVP));



//  for(int i =1;i<=6;i++)
//  {
//    /* Make our background black */
//    glClearColor(0.0, 0.0, 0.0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 36);//plane made of 36 vertices (6 planes * 2 triangles * 3 vertices each = 36 vertices passed onto)
//    display.update();
//    SDL_Delay(200);
//  }



    // Now grab and draw the second Plane (Note this is switching to the new generated VAO)

    //Load Matrices to Shader END
    glBindVertexArray(gameModels->GetModel("plane2"));
    glUseProgram(program);
    glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);//plane made of 6 vertices


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
    gameModels->CreatePlaneModel("plane1");
    gameModels->CreatePlaneModel2("plane2");

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
}
