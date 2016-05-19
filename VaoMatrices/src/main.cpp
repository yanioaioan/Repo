
#include "ModelLoader.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include <QTime>
#include <iostream>
#include "display.h"
#include "shader.h"
#include <QImage>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include <ngl/VertexArrayObject.h>


//usefull vec3 print command
#define printVec3(a,b,c) //std::cout<<a<<","<<b<<","<<c<<std::endl;

glm::mat4 matrixFromAxisAngle(glm::vec3 axis, float angle);
void loadTexture(const char *texturePath);
void unLoadTexture();

ModelLoader* m;
GLuint program;
GLuint m_textureNamesArray[2];
short loaderTexturesCounter=0;
int ScreenWidth=800;int ScreenHeight=600;
int m_Frames = 0;
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


#include <iomanip>
float * getEulerAngles(const glm::mat4 & rotationMatrix)
{

    double dArray[16] = {0.0};

   // //std::cout<<std::endl;//std::cout<<std::endl;//std::cout<<std::endl;
    const float *pSource = (const float*)glm::value_ptr(rotationMatrix);
    for (int i = 0; i < 16; ++i)
    {

        if(i%4==0)//every row
            //std::cout<<std::endl;

        dArray[i] = pSource[i];

//            if( dArray[i] < (1/pow(10,20)) )
//            {
//                //std::cout<<setw(10)<<0<<"\t";
//            }
//            else
        {
//            //std::cout<<setw(10)<<dArray[i]<<"\t";
        }


    }////std::cout<<std::endl;//std::cout<<std::endl;//std::cout<<std::endl;



    float bank;
    float heading;
    float attitude;
    //extract euler angles from rotation mat

    if(dArray[5]!=1 || dArray[5]!=-1) //if we are not in the south or north pole
    {
         bank = atan2(-dArray[6],dArray[5]);
         heading = atan2(-dArray[8],dArray[0]);
         attitude = asin(-dArray[4]);
    }
     else
    {
        bank = 0;
        heading = atan2(dArray[3],dArray[10]);
        attitude = asin(-dArray[4]);
    }
//    //std::cout<<bank*(180.0f/M_PI)<<endl<<heading*(180.0f/M_PI)<<endl<<attitude*(180.0f/M_PI)<<std::endl;

    float eulerangles[3];
    eulerangles[0]=bank*(180.0f/M_PI);eulerangles[1]=heading*(180.0f/M_PI);eulerangles[2]=attitude*(180.0f/M_PI);
    return eulerangles;

}



struct Light {
    glm::vec3 position;
    glm::vec3 intensities; //a.k.a. the color of the light
    float ambientCoefficient;
};

Light gLight;


Display display(ScreenWidth,ScreenHeight,"Vao Model Loading & Modern Opengl (Matrices Shaders)- (using SDL for window & opengl context handling)");



//FPS camera, right-handed coordinate system.

// Pitch should be in the range of [-90 ... 90] degrees and yaw
// should be in the range of [0 ... 360] degrees.
glm::mat4 FPSViewRH( glm::vec3 eye, float pitch, float yaw )
{
    if(pitch>2*M_PI || yaw>2*M_PI)//in which case we 've entered degrees
    {
        pitch=pitch*(M_PI/180.0);
        yaw=yaw*(M_PI/180.0);
    }

    // If the pitch and yaw angles are in degrees,
    // they need to be converted to radians. Here
    // I assume the values are already converted to radians.
    float cosPitch = cos(pitch);
    float sinPitch = sin(pitch);
    float cosYaw = cos(yaw);
    float sinYaw = sin(yaw);

    glm::vec3 xaxis = { cosYaw, 0, -sinYaw };
    glm::vec3 yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
    glm::vec3 zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    glm::mat4 viewMatrix = {
        glm::vec4(       xaxis.x,            yaxis.x,            zaxis.x,      0 ),
        glm::vec4(       xaxis.y,            yaxis.y,            zaxis.y,      0 ),
        glm::vec4(       xaxis.z,            yaxis.z,            zaxis.z,      0 ),
        glm::vec4( -dot( xaxis, eye ), -dot( yaxis, eye ), -dot( zaxis, eye ), 1 )
    };

    return viewMatrix;

}

#include <iomanip>


enum rotationAxisFlag
{
    y,
    x,
    z
}
rotationAxisFlag=y;

glm::mat4 Model = glm::mat4(1);
glm::mat4 Model2 = glm::mat4(1);

glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::vec3(0,1,2));//glm::mat4(1);
glm::mat4 translationMatrix2 = glm::translate(glm::mat4(1), glm::vec3(0,1,2));//glm::mat4(1);

glm::mat4 translationMatrix3 = glm::translate(glm::mat4(1), glm::vec3(0,0,0));//glm::mat4(1);

glm::mat4 rotationMatrix = glm::mat4(1);
glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(1,1,1));
glm::mat4 scaleMatrix2 = glm::scale(glm::mat4(1), glm::vec3(0.5,0.5,0.5));


//static bool translate=true;
//static int temp;

glm::vec4 newUp(0,1,0,0);

static float x_rot;
static float y_rot;
static float z_rot;

static float localWhiteCubeRot;

glm::mat4 pushTo;
glm::mat4 rot;

void renderScene(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.3, 0.3, 0.3, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  ModelLoader *m=ModelLoader::instance(program);


  //Load Matrices to Shader START
  // Model matrix : an identity matrix (model will be at the origin)

//  printVec3(1,2,3);

  float angle = 0;


  if(display.m_flagLocalX)
  {
      angle = display.m_angleX;

      rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(1,0,0));//the rotation matrix is multiplied with itself producing a local coordinate rotation
//      translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,2));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

     // translationMatrix2 = glm::translate(translationMatrix, glm::vec3(0,0,-2));//Used to form another Model matrix rotating around the main colored Cube



      //for the cube rotation around the warrior
      //first we need to extract the euler angles from the rotation matrix (cause the angle gets zeroed-out every time, and it's only the rotation matrix that gets updated..no reason why)

//      float * eulerangles = getEulerAngles(rotationMatrix);
//      eulerangles[0];//bank
//      eulerangles[1];//heading
//      eulerangles[2];//attitude


      x_rot+=angle;

//      translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0,-1,-2));
      rot= glm::rotate(translationMatrix, x_rot, glm::vec3(1,0,0)); //rotationMatrix*translationMatrix;
      glm::mat4 localrotationofWhiteCube=glm::rotate(rot, localWhiteCubeRot++/180.0f , glm::vec3(0,1,0));
      pushTo = glm::translate(rot,glm::vec3(0,1,2)) * localrotationofWhiteCube;
//      translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0,1,2));
  }

  if(display.m_flagLocalY)
  {
     angle = display.m_angleY;

     //std::cout<<angle <<std::endl;

     rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(0,1,0));//the rotation matrix is multiplied with itself producing a local coordinate rotation
//     translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,2));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

    // translationMatrix2 = glm::translate(translationMatrix, glm::vec3(0,0,-2));//Used to form another Model matrix rotating around the main colored Cube



     //for the cube rotation around the warrior
     y_rot +=angle;

     std::cout<<y_rot<<std::endl;

//     translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0,-1,-2));
     rot= glm::rotate(translationMatrix, y_rot , glm::vec3(0,1,0));
     glm::mat4 localrotationofWhiteCube=glm::rotate(rot, localWhiteCubeRot++/180.0f , glm::vec3(0,1,0));
     pushTo = glm::translate(rot,glm::vec3(0,1,2)) * localrotationofWhiteCube;
//     translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0,1,2));

  }

  if(display.m_flagLocalZ)
  {
    angle = display.m_angleZ;

    rotationMatrix = glm::rotate(/*glm::mat4(1) */ /*Model*/ rotationMatrix, angle, glm::vec3(0,0,1));//the rotation matrix is multiplied with itself producing a local coordinate rotation
//    translationMatrix = glm::translate(glm::mat4(1)/*translationMatrix*/,glm::vec3(0,0,2));//this represents our global translation when reinitialized with glm::mat4(1) / or our local translation if multiplied with translation matrix itself from the previous iteration

    //translationMatrix2 = glm::translate(translationMatrix, glm::vec3(0,0,-2));//Used to form another Model matrix rotating around the main colored Cube

    // Roll section
    z_rot+=angle;


    //for the cube rotation around the warrior
//    translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0,-1,-2));
    rot= glm::rotate(translationMatrix, z_rot, glm::vec3(0,0,1)); //rotationMatrix*translationMatrix;
    glm::mat4 localrotationofWhiteCube=glm::rotate(rot, localWhiteCubeRot++/180.0f , glm::vec3(0,1,0));
    pushTo = glm::translate(rot,glm::vec3(0,1,2)) * localrotationofWhiteCube;
//    translationMatrix = glm::translate(glm::mat4(1),glm::vec3(0,1,2));



  }

    //  translationMatrix = glm::translate(glm::mat4(1), glm::vec3(0.5,0,0));//glm::mat4(1);

    //  Model =  translationMatrix*rotationMatrix;
    //  Model =  rotationMatrix *translationMatrix*scaleMatrix;


//      Right to left evaluation (because of OpenGL Column-Major matrices) ... so at first ROTATE .. and then TRANSLATE ()

//      Often used order. Rotate and place wherever we want locally
        Model =  translationMatrix*rotationMatrix*scaleMatrix;
//      Could be used to Rotate around the origin with the radius of translationMatrix
//      Model =  rotationMatrix * translationMatrix * scaleMatrix;


        //glm::mat4 rotationMatrix2 = glm::rotate(rotationMatrix2, localWhiteCubeRot++/360.0f ,glm::vec3(1,0,0));
        //rotationMatrix = rotationMatrix2 * rotationMatrix2;

        //move the cube up and front relative to the model //Works fine if no offset from origin
//        translationMatrix2 = glm::translate(translationMatrix , glm::vec3(0,1,2));
//        glm::mat4 localCubeRotationMat = glm::rotate(glm::mat4(1) ,  localWhiteCubeRot++/180.0f , glm::vec3(1,1,1));
//        Model2 =  rotationMatrix* translationMatrix2*localCubeRotationMat *scaleMatrix2;//Flipped rotationMatrix with translationMatrix to achieve rotation around a single point

//        translationMatrix2 = glm::translate(translationMatrix , glm::vec3(0,0,-2));
//        translationMatrix2 = glm::rotate(translationMatrix2 ,  /*localWhiteCubeRot++/180.0f*/45.0f , glm::vec3(1,1,1));
//        translationMatrix2 = glm::translate(translationMatrix2 , glm::vec3(0,0,2));


        Model2 =  /*rotationMatrix* translationMatrix2*/pushTo *scaleMatrix2;//Flipped rotationMatrix with translationMatrix to achieve rotation around a single point




//        //std::cout<<rotationMatrix[0][0]<<std::endl;//0row 0column
//        //std::cout<<rotationMatrix[0][1]<<std::endl;//0row 1column
//        //std::cout<<rotationMatrix[0][2]<<std::endl;//0row 2column
//        //std::cout<<rotationMatrix[0][3]<<std::endl;//0row 3column
        double dArray[16] = {0.0};

       // //std::cout<<std::endl;//std::cout<<std::endl;//std::cout<<std::endl;
        const float *pSource = (const float*)glm::value_ptr(rotationMatrix);
        for (int i = 0; i < 16; ++i)
        {

            if(i%4==0)//every row
                //std::cout<<std::endl;

            dArray[i] = pSource[i];

//            if( dArray[i] < (1/pow(10,20)) )
//            {
//                //std::cout<<setw(10)<<0<<"\t";
//            }
//            else
            {
//                //std::cout<<setw(10)<<dArray[i]<<"\t";
            }


        }////std::cout<<std::endl;//std::cout<<std::endl;//std::cout<<std::endl;




//        m00	m01	m02	m03
//        m10	m11	m12	m13
//        m20	m21	m22	m23
//        m30	m31	m32	m3

//        bank = atan2(-m12,m11)
//        heading = atan2(-m20,m00)
//        attitude = asin(m10)


//   Pre- or post-multiplication just defines the order of operations how the member of that matrix and vector are multiplied, its purely a notational convention.
//   The common operations in 3D graphics are post-multiplying a row-vector with column-major matrices (OpenGL) and pre-multiplying a column-vector with row-major matrices (DirectX).
//   Both are basically the same operations with the same results, just the notational convention is different.


//  prevent from continuous rotation
    display.m_flagLocalX=false;
    display.m_flagLocalY=false;
    display.m_flagLocalZ=false;

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), ScreenWidth / (float)ScreenHeight, 0.5f, 500.f);

//  Camera matrix
    glm::vec3 newcameraposition(Model2[3][0], Model2[3][1], Model2[3][2]-2);
    glm::vec3 target(Model[3][0], Model[3][1], Model[3][2]);
    glm::vec3 cameraDirection = target-newcameraposition;
    glm::normalize(cameraDirection);
    glm::vec4 upVec = glm::vec4(0,1,0,0);
    glm::vec3 rightVec = glm::cross(glm::vec3(upVec),cameraDirection);
    glm::normalize(rightVec);
    newUp= glm::vec4(glm::cross(cameraDirection,rightVec),0);

    glm::mat4 tmpmat=matrixFromAxisAngle(cameraDirection, -z_rot*(M_PI/180));//to be used for roll only! so,
                                                                             //if there's a rotation specified for z it will roll
                                                                             //(used for new Up Vec Calculation for the camera)
    newUp =  tmpmat*upVec;

//  printVec3(newcameraposition.x,newcameraposition.y,newcameraposition.z)

//  Model2 = glm::translate(Model, glm::vec3(0,0,-200));
//  glm::mat4 View = Model2;

//  printVec3(Model2[3][0], Model2[3][1], Model2[3][2])



    // Cameras:

    //1)Camera Supporting Roll (around Z axis)

//     Recompute Up Vector -  Supporting Roll (around Z axis)
//    glm::mat4 View = glm::lookAt(
//                              glm::vec3(Model2[3][0], Model2[3][1], Model2[3][2]),
//                              glm::vec3(Model[3][0], Model[3][1], Model[3][2]), // and looks at the origin
//                              glm::vec3(newUp) /*glm::vec3(0,1,0)*/  // Head is up (set to 0,-1,0 to look upside-down)
//                              );

//    glm::mat4 View=FPSViewRH(-newcameraposition,-40,0);


    // 2) Standar Up Vector - Not Supporting Roll (around Z axis)

//     Standar Up Vector - Not Supporting Roll (around Z axis) - Camera Tracking the player object 3rd person
//    glm::mat4 View = glm::lookAt(
//                              glm::vec3(Model2[3][0], Model2[3][1], Model2[3][2]),
//                              glm::vec3(Model[3][0], Model[3][1], Model[3][2]), // and looks at the origin
//                              glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
//                              );


    // 3) Standar Up Vector - Not Supporting Roll (around Z axis)- Camera Statically Placed

    // Standar Up Vector - Not Supporting Roll (around Z axis)- Camera Statically Placed - NOT Tracking the player object
    glm::mat4 View = glm::lookAt(
                              glm::vec3(0,10,-8),
                              glm::vec3(Model[3][0], Model[3][1]+2, Model[3][2]), // and looks at the origin
                              glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                              );




    // 4) 3rd person Tracking manual calculate of camera's new position

//    //Spherical coordinates
//    float x=Model2[3][0];//white cube's position
//    float y=Model2[3][1];
//    float z=Model2[3][2];

//    float r=sqrt(x*x + y*y + z*z);
//    float theta=atan2(y,x);
//    float phi=acos(z/r);

//    //Convert to Cartesian Coordinataes for camera position
//    float scaleValue=10;

//    //camera's position
//    float cartesCamX = scaleValue*r*cos(theta)*sin(phi);
//    float cartesCamY = scaleValue*r*sin(theta)*sin(phi);
//    float cartesCamZ = scaleValue*r*cos(phi);

//    // Normalize your look vector
//    glm::vec3 lookVector=glm::vec3(Model[3][0]-Model2[3][0], Model[3][1]-Model2[3][1], Model[3][2]-Model2[3][2]);
//    glm::normalize(lookVector);

//    //Take the cross product of your look vector and a vector of 0,1,0. This gives you your right vector.
//    glm::vec3 rightVector=glm::cross(lookVector, glm::vec3(0,1,0));

//    //Take the cross product of your right vector and your look vector. This is your new up vector, which is a perpendicular to your original look vector.
//    glm::vec3 newUpVector=glm::cross(rightVector, lookVector);
//    //std::cout<<newUpVector.x<<","<<newUpVector.y<<","<<newUpVector.z<<std::endl;

//    glm::mat4 View = glm::lookAt(glm::vec3(cartesCamX,cartesCamY,cartesCamZ), glm::vec3(Model[3][0], Model[3][1], Model[3][2]),  newUpVector);




    //  HERE I SCALED CAUSE THE TESTING MODEL WAS BIG & translated it the be centered to the screen
    glm::mat4 MVP        = Projection * View * glm::scale(Model,glm::vec3(0.1,0.1,0.1)); // Remember, matrix multiplication works the other way around (<----<----<)

    glm::mat4 MVP2       = Projection * View * Model2; // Remember, matrix multiplication works the other way around (<----<----<)

    //  reset to origin
    //  glm::mat4 MVP(1);

    // Get a handle for our "MVP" uniform.
    // Only at initialisation time.
    GLuint MatrixID = glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //Load Matrices to Shader END

    //use shader with program id = program
    glUseProgram(program);

    //Pass light to shader
    GLuint lightpos = glGetUniformLocation(m->m_shaderProgramId, "light.position");//or 'zero' instead of retrieving the reference to the attribute "position input"
    glUniform3f(lightpos, gLight.position.x, gLight.position.y, gLight.position.z);
    GLuint lightcolor = glGetUniformLocation(m->m_shaderProgramId, "light.intensities");//or 'zero' instead of retrieving the reference to the attribute "position input"
    glUniform3f(lightcolor, gLight.intensities.x, gLight.intensities.y, gLight.intensities.z);
    GLuint ambientColor = glGetUniformLocation(m->m_shaderProgramId, "light.ambientCoefficient");//or 'zero' instead of retrieving the reference to the attribute "position input"
    glUniform1f(ambientColor, gLight.ambientCoefficient);



    // Bind Texture before drawing - Used for apllying colored texture and normal mapping to the 2nd small cube

    GLuint locColourMap = glGetUniformLocation(m->m_shaderProgramId, "tex"); // The texture map
    glUniform1i(locColourMap, 0);//"tex" sampler2D

    GLuint locNormalMap = glGetUniformLocation(m->m_shaderProgramId, "tex1"); // The normal map
    glUniform1i(locNormalMap, 1);//"tex1" sampler2D

    // Bind our texture to the appropriate texture image unit
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureNamesArray[0]);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textureNamesArray[1]);


    // Warrior Drawing / Or Cube 1 DRAWING

//    glBindVertexArray(m->GetModel("cube1"));
    glBindVertexArray(m->GetModel("Warrior"));

    // Pass model matrix of 1st cube to shader for lighting calculations (However this could also happen here in c++ code as well for performance reasons)
    GLuint modelmatrixPassToShader = glGetUniformLocation(m->m_shaderProgramId, "modelmatrixcube");//or 'zero' instead of retrieving the reference to the attribute "position input"
    glUniformMatrix4fv(modelmatrixPassToShader, 1, GL_FALSE, &Model[0][0]);

    glm::mat4 MV = View*Model;
    GLuint worldmatrixPassToShader = glGetUniformLocation(m->m_shaderProgramId, "MV");//or 'zero' instead of retrieving the reference to the attribute "position input"
    glUniformMatrix4fv(worldmatrixPassToShader, 1, GL_FALSE, &MV[0][0]);


    glDrawArrays(GL_TRIANGLES, 0, m->vboMesh.size());//model made of mesh's vertices
    glBindVertexArray(0);

    //  Cube 2 DRAWING
    // Now grab and draw the second cube (Note this is switching to the new generated VAO)

    //Load Matrices to Shader END

//    Draw Multiple (100) Vaos at 60fps
//    for(int i=2;i<=100;i++)
//    {
//        glm::mat4 tmpTranslation = glm::translate(Model2,glm::vec3(0,i*2,0));
//        Model =  rotationMatrix*tmpTranslation*scaleMatrix;
//        MVP2   = Projection * View * Model;

//        glGetUniformLocation(program, "MVP");
//        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);

//        char tmpbuf [50];
//        sprintf(tmpbuf, "cube%d",i);
//        glBindVertexArray(m->GetModel(tmpbuf));


//        glDrawArrays(GL_TRIANGLES, 0, 36);//cube made of 36 vertices
//        glBindVertexArray(0);
//    }



    //bind and draw cube 2
    glBindVertexArray(m->GetModel("cube2"));
    glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, m->cube2Vertices);//cube made of 36 vertices (1 cube = 6 planes * 2 triangles each plane * 3 vertices each triangle = 36 vertices passed onto the shader)
    glBindVertexArray(0);


//    //glm::mat4 rotationMatrixLocalRotCubeWhite = glm::mat4(1);
//    glm::mat4 Model2Local = glm::mat4(1);
//    Model2 =  translationMatrix2*rotationMatrix*scaleMatrix2;
//    Model2Local= glm::rotate( Model2, 45.0f, glm::vec3(0,1,0));

//    glm::mat4 MVP2local   = Projection * View * Model2Local;


//    glBindVertexArray(m->GetModel("cube2"));
//    glGetUniformLocation(program, "MVP");

//    // Send our transformation to the currently bound shader,
//    // in the "MVP" uniform
//    // For each model you render, since the MVP will be different (at least the M part)
//    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2local[0][0]);

//    // Pass model matrix of 2nd cube to shader for lighting calculations (However this could also happen here in c++ code as well for performance reasons)
//    modelmatrixPassToShader = glGetUniformLocation(m->m_shaderProgramId, "modelmatrixcube");//or 'zero' instead of retrieving the reference to the attribute "position input"
//    glUniformMatrix4fv(modelmatrixPassToShader, 1, GL_FALSE, &Model2Local[0][0]);

//    glDrawArrays(GL_TRIANGLES, 0, m->cube2Vertices);//cube made of 36 vertices (1 cube = 6 planes * 2 triangles each plane * 3 vertices each triangle = 36 vertices passed onto the shader)
//    glBindVertexArray(0);



    //unbind Texture
//    unLoadTexture();


    // GRID DRAWING

    glLineWidth((GLfloat)2.5f);

    glBindVertexArray(m->GetModel("Grid"));
    glGetUniformLocation(program, "MVP");

    // Send our transformation to the currently bound shader,
    // in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    Model = glm::mat4(1);

    MVP        = Projection * View * Model;
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    /////////////////////////////
    glBindBuffer(GL_ARRAY_BUFFER,m->Gridvbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Set Uniform color for the grid
    GLuint colorUniformAttr = glGetUniformLocation(m->m_shaderProgramId, "gridcolor");//or 'zero' instead of retrieving the reference to the attribute "position input"
    GLfloat uniformColor[] = { 0.3f, 0.2f, 0.25f, 1.0f};
    glUniform4fv(colorUniformAttr, 1, uniformColor);


    // Draw Horizontal Lines
    for (int i = 0; i < 50; i++)
    {
      glDrawArrays(GL_LINE_STRIP, 50*i, 50);
//    That works, although we did make 50 OpenGL calls,
//    which is not so much, but one would rather avoid doing that.
//    We also need to draw vertical lines, but the vertices are not in the right order!
//    Although, in this case, we can cheat by using the stride and pointer parameters:
    }


    //Cheating using stride to draw vertical lines
    //Draw Vertical Lines
    for(int i = 0; i < 50; i++)
    {
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 50 * sizeof(ModelLoader::point), (void *)(i * sizeof(ModelLoader::point)));//draw every other 12 bytes (cause struct point contains 3 GLFloats and so..3*4bytes=12 bytes)
      glDrawArrays(GL_LINE_STRIP, 0, 50);
    }
    /////////////////////////////


    uniformColor[0] = 0;uniformColor[1] = 0;uniformColor[2] = 0;uniformColor[3] = 0;//reset uniform color values to 0 and ..
    glUniform4fv(colorUniformAttr, 1, uniformColor);//pass uniform color to shader when we are finished with drawing the grid

    // Unbind VAO of the grid
    glBindVertexArray(0);


//     Draw a grid in immediate mode "quickly" (if wanted)!
//     glBegin(GL_LINES);
//     for (GLfloat i = -100; i <= 100; i += 1) {
//       glVertex3f(i, 0, 100); glVertex3f(i, 0, -100);
//       glVertex3f(100, 0, i); glVertex3f(-100, 0, i);
//     }
//     glEnd();

    m_Frames++;
//    //std::cout<<"m_Frames="<<m_Frames<<std::endl;

    gLight.position.z=-10+2*10/6*cos(m_Frames*M_PI/180);
    gLight.position.x=-1+2/6*cos(m_Frames*M_PI/180);

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
    shader.InitShaders("./shaders/shaderV.glsl", "./shaders/shaderF.glsl");
    program = shader.getProgramShaderId();

    //  Enable Vaos & Load
    ModelLoader *m = ModelLoader::instance(program);
//    m = new ModelLoader(program);



//    m->CreateCubeModel("cube1");
    m->CreateCubeModel2("cube2");
    m->CreateWarriorModel("Warrior");

    loadTexture("textures/Imrod_Diffuse.tga");
    loadTexture("textures/Imrod_norm.tga");//create the texture to be loaded as part of the cube2 model


    //    Draw Multiple (100) Vaos at 60fps
    // for(int i=2;i<=100;i++)
    // {
    //   char tmpbuf [50];
    //   sprintf(tmpbuf, "cube%d",i);
//         m->CreateCubeModel2(/*tmpbuf*/"cube2");
    // }


     // Initialize light
     gLight.intensities.x=1.5; gLight.intensities.y=1.5; gLight.intensities.z=1.5;// light's color
     gLight.position.x=0; gLight.position.y=20; gLight.position.z=-20;// light's position
     gLight.ambientCoefficient=1.7;


    m->CreateGrid("Grid");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_CLAMP);
    glEnable( GL_MULTISAMPLE );

    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);

//    Matrices Initial Setup
    glm::mat4 Projection = glm::perspective(glm::radians(60.0f), ScreenWidth / (float)ScreenHeight, 0.5f, 150.f);
    //  Pass in the projection matrix to our model so we can pass it to the vertex shader
    m->SetProjectionMatrix(Projection);

    // Camera matrix
    glm::mat4 View = glm::lookAt(
                                glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
                                glm::vec3(0,0,0), // and looks at the origin
                                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                );

    m->SetViewMatrix(View);
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

void unLoadTexture()
{
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void loadTexture(const char* texturePath)
{
  QImage *image = new QImage();
  bool loaded=image->load(texturePath);
  if(loaded == true)
  {
    int width=image->width();
    int height=image->height();

    unsigned char *data = new unsigned char[ width*height*3];
    unsigned int index=0;
    QRgb colour;
    for( int y=0; y<height; ++y)
    {
      for( int x=0; x<width; ++x)
      {
        colour=image->pixel(x,y);

        data[index++]=qRed(colour);
        data[index++]=qGreen(colour);
        data[index++]=qBlue(colour);
      }
    }

        if(loaderTexturesCounter++==0)// generate mipmaps for the 1st texture
        {
            glGenTextures(1,&m_textureNamesArray[0]);
            // Bind our texture to the appropriate texture image unit
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_textureNamesArray[0]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
            //std::cout<<"texture GL set "<<texturePath<<"\n";
            glGenerateMipmap(GL_TEXTURE_2D); //  Allocate the mipmaps
        }
        else// generate mipmaps for the 2nd texture
        {
            glGenTextures(1,&m_textureNamesArray[1]);
            // Bind our texture to the appropriate texture image unit
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D,m_textureNamesArray[1]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
          //std::cout<<"texture GL set "<<texturePath<<"\n";
            glGenerateMipmap(GL_TEXTURE_2D); //  Allocate the mipmaps
        }


  }

  glEnable(GL_MULTISAMPLE);

}

int main(/*int argc, char **argv*/)
{
 glewInit();

 Init();
 // Measure speed
 QTime currentTime;
 currentTime.start();

    while(!display.isClosed())
    {
        //  Clear background
        display.clear(0.3, 0.3, 0.3,1);
        renderScene();

        // Calculate TimeElapsed & FPS
        double tmpTime=currentTime.elapsed();

//        printf("Time elapsed per frame is %f ms\n", tmpTime / float(m_Frames));
//        printf("FPS is %f frames per/sec \n", float(m_Frames)/(float(tmpTime) / 1000.0f) );


        currentTime.restart ();
        m_Frames=0;

        //SwapBuffers
        display.update();

    }

// m->DeleteModel("cube1");m->DeleteModel("cube2");m->DeleteModel("grid"); No need to be called since the ModelLoader destructor takes care of the clean up process
// delete m;//if we don't make use of singleton we need to delete the actual ModelLoader m object

 ModelLoader::DestroySingleton();
 glDeleteProgram(program);

 unLoadTexture();
 // remove the texture now we are done
 glDeleteTextures(2,m_textureNamesArray);

 return 0;
}
