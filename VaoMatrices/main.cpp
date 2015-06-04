#pragma once

#include "GameModels.h"
#include<iostream>
#include<stdio.h>;
#include<stdlib.h>;
#include<fstream>;
#include<vector>;

#include <iostream>
#include "display.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//usefull vec3 print command
#define printVec3(a,b,c) std::cout<<a<<b<<c<<std::endl;

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
glm::mat4 translationMatrix = glm::mat4(1);
glm::mat4 rotationMatrix = glm::mat4(1);
glm::mat4 scaleMatrix = glm::mat4(1);

static bool translate=true;

void renderScene(void)
 {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.3, 0.3, 1.0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_DEPTH_CLAMP);
  glEnable( GL_MULTISAMPLE );


  glBindVertexArray(gameModels->GetModel("triangle1"));
  glUseProgram(program);

  //Load Matrices to Shader START
  // Model matrix : an identity matrix (model will be at the origin)

//  printVec3(1,2,3);

  float angle = 0;

  if(display.m_flagLocalX)
  {
      angle = display.m_angleX;

      rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(1,0,0));//the rotation matrix is multiplied with itself producind a local coordinate rotation
  }

  if(display.m_flagLocalY)
  {
     angle = display.m_angleY;

     rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(0,1,0));//the rotation matrix is multiplied with itself producind a local coordinate rotation


  }

  if(display.m_flagLocalZ)
  {
    angle = display.m_angleZ;

    rotationMatrix = glm::rotate(rotationMatrix, angle, glm::vec3(0,0,1));//the rotation matrix is multiplied with itself producind a local coordinate rotation
  }


        translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0.5,0,0));//this represents our global translation





    Model =  translationMatrix*rotationMatrix*scaleMatrix;//Often used order. Rotate and place wherever we want
//    Model =  rotationMatrix *translationMatrix;//Could be used to Rotate around the origin with the radius of translationMatrix


  //prevent from continues rotation
  display.m_flagLocalX=false;
  display.m_flagLocalY=false;
  display.m_flagLocalZ=false;



//  glm::mat4 Projection = gameModels->GetProjectionMatrix();//always the same probably
//  glm::mat4 View = gameModels->GetViewMatrix();//always the same probably

  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), ScreenWidth / (float)ScreenHeight, 0.5f, 500.f);

  // Camera matrix
  glm::mat4 View = glm::lookAt(
                              glm::vec3(0,10,-150), // Camera is at (4,3,3), in World Space
                              glm::vec3(0,0,0), // and looks at the origin
                              glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                              );

  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication works the other way around (<----<----<)

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

    glDrawArrays(GL_TRIANGLES, 0, 6);//plane made of 6 vertices
//    display.update();
//    SDL_Delay(200);
//  }


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
    gameModels->CreateTriangleModel("triangle1");

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
