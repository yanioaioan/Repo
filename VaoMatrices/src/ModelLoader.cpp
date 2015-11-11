#include "ModelLoader.h"
#include <iostream>
#include<ngl/Obj.h>

#include <objLoader.h>

//using namespace Models;

ModelLoader::ModelLoader(GLuint shaderProgramId)
{
    //introduce the m_shaderProgramId to the ModelLoader Class
    m_shaderProgramId = shaderProgramId;

    // Shader variable positions
    posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or '0' instead of retrieving the reference to the attribute "position input"
    colAttrib = glGetAttribLocation(m_shaderProgramId, "in_color");//or '1' instead of retrieving the reference to the attribute "colour input"
    texAttrib = glGetAttribLocation(m_shaderProgramId, "in_uv");//or '2' instead of retrieving the reference to the attribute "uv input"

    normAttrib = glGetAttribLocation(m_shaderProgramId, "in_normal");//or '3' instead of retrieving the reference to the attribute "in normal"
    bitanAttrib = glGetAttribLocation(m_shaderProgramId, "in_bitangent");//or '4' instead of retrieving the reference to the attribute "in bitangent"
    binorAttrib = glGetAttribLocation(m_shaderProgramId, "in_binormal");//or '5' instead of retrieving the reference to the attribute "in binormal"
}

ModelLoader::~ModelLoader()
{

  std::map<std::string, Model>::iterator it;
  for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
  {
    //delete VAO and VBOs (if many)
    unsigned int* p = &it->second.vao;
    glDeleteVertexArrays(1, p);
    glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
    it->second.vbos.clear();
  }
  GameModelList.clear();
}




void ModelLoader::CreateCubeModel(const std::string& gameModelName)
{
   unsigned int vao;
   unsigned int vbo;

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   std::vector<VertexStructure> vertices;//our vertex positions & colors

/*   Manual Addition of Values   */
//   vertices.push_back(VertexStructure(glm::vec3( 0.5, -0.5, 0.5), glm::vec4( 1,-0, 0, 1)));
//   vertices.push_back(VertexStructure(glm::vec3(-0.5, -0.5, -0.5), glm::vec4( 0, 1, 0, 1)));
//   vertices.push_back(VertexStructure(glm::vec3( 0.5, 0.5, 0.0),  glm::vec4( 1, 0, 1, 1)));



//   // Left bottom triangle
//           -0.5f, 0.5f, 0f,
//           -0.5f, -0.5f, 0f,
//           0.5f, -0.5f, 0f,
//           // Right top triangle
//           0.5f, -0.5f, 0f,
//           0.5f, 0.5f, 0f,
//           -0.5f, 0.5f, 0f

   /*** Supposedely Imported Attributes  START***/   /*CENTER CUBE*/
   std::vector<glm::vec3> imported_positions;
   imported_positions.push_back(glm::vec3( -1 , -1, -1));imported_positions.push_back(glm::vec3( -1, 1, -1));imported_positions.push_back(glm::vec3( -1, 1, 1)); //LEFT
   imported_positions.push_back(glm::vec3( -1, 1, 1));imported_positions.push_back(glm::vec3( -1,-1,-1));imported_positions.push_back(glm::vec3( -1,-1,1));//get all position values

   imported_positions.push_back(glm::vec3( 1 , 1, -1));imported_positions.push_back(glm::vec3( 1, 1, 1));imported_positions.push_back(glm::vec3( 1, -1, -1)); //RIGHT
   imported_positions.push_back(glm::vec3( 1,-1,-1));imported_positions.push_back(glm::vec3( 1,-1,1));imported_positions.push_back(glm::vec3( 1,1,1));//get all position values

   imported_positions.push_back(glm::vec3( -1,1,-1));imported_positions.push_back(glm::vec3( -1,1,1));imported_positions.push_back(glm::vec3( 1, 1, 1)); //UP
   imported_positions.push_back(glm::vec3( 1,1,1));imported_positions.push_back(glm::vec3(1,1,-1));imported_positions.push_back(glm::vec3(-1,1,-1));//get all position values

   imported_positions.push_back(glm::vec3( -1,-1,-1));imported_positions.push_back(glm::vec3( -1,-1,1));imported_positions.push_back(glm::vec3( 1, -1, 1)); //DOWN
   imported_positions.push_back(glm::vec3( 1,-1,1));imported_positions.push_back(glm::vec3(1,-1,-1));imported_positions.push_back(glm::vec3(-1,-1,-1));//get all position values

   imported_positions.push_back(glm::vec3( -1,1,-1));imported_positions.push_back(glm::vec3( 1,1,-1));imported_positions.push_back(glm::vec3( 1, -1, -1)); //FRONT
   imported_positions.push_back(glm::vec3( 1,-1,-1));imported_positions.push_back(glm::vec3(-1,-1,-1));imported_positions.push_back(glm::vec3(-1,1,-1));//get all position values

   imported_positions.push_back(glm::vec3( -1,-1,1));imported_positions.push_back(glm::vec3( 1,-1,1));imported_positions.push_back(glm::vec3( 1,1,1)); //BACK
   imported_positions.push_back(glm::vec3( 1,1,1));imported_positions.push_back(glm::vec3(-1,1,1));imported_positions.push_back(glm::vec3(-1,-1,1));//get all position values



   std::vector<glm::vec4> imported_colours;
   imported_colours.push_back(glm::vec4( 1, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 1, 0, 1));
   imported_colours.push_back(glm::vec4( 1, 0, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 1, 1));//get all position values

   imported_colours.push_back(glm::vec4( 1, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 1, 0, 1));
   imported_colours.push_back(glm::vec4( 1, 0, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 1, 1));//get all position values

   imported_colours.push_back(glm::vec4( 1, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 1, 0, 1));
   imported_colours.push_back(glm::vec4( 1, 0, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 1, 1));//get all position values

   imported_colours.push_back(glm::vec4( 1, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 1, 0, 1));
   imported_colours.push_back(glm::vec4( 1, 0, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 1, 1));//get all position values

   imported_colours.push_back(glm::vec4( 1, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 1, 0, 1));
   imported_colours.push_back(glm::vec4( 1, 0, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 1, 1));//get all position values

   imported_colours.push_back(glm::vec4( 1, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 0, 1, 1));imported_colours.push_back(glm::vec4( 0, 1, 0, 1));
   imported_colours.push_back(glm::vec4( 1, 0, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 0, 1));imported_colours.push_back(glm::vec4( 1, 1, 1, 1));//get all position values
   /*** Supposedely Imported Attributes  END***/


   //Just For Test Purposes, to be removed
   std::vector<glm::vec2> imported_texureUVs;


   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1));
   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
   imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1));
   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
   imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
   imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
   imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1));
   imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
   imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1));

   //----------------------------------------------//
   //   sample of cube from maya
   //   vt 0.000000 0.000000
   //   vt 1.000000 0.000000
   //   vt 1.000000 1.000000
   //   vt 0.000000 1.000000


   std::vector<glm::vec2> textures;
   for(unsigned int i=0;i<imported_texureUVs.size();i++)
   {
       textures.push_back(glm::vec2(imported_texureUVs[i]));
   }



   //Calculate Vertex Normals
   std::vector<glm::vec3> imported_normals;
       glm::vec3 nLeft = glm::cross( (imported_positions[1]-imported_positions[0]) , ((imported_positions[2]-imported_positions[0])) );//left normal
       glm::vec3 nRight = glm::cross( (imported_positions[7]-imported_positions[6]) , ((imported_positions[8]-imported_positions[6])) );//right normal
       glm::vec3 nUp = glm::cross( (imported_positions[13]-imported_positions[12]) , ((imported_positions[14]-imported_positions[12])) );//up normal
       glm::vec3 nDown = glm::cross( (imported_positions[19]-imported_positions[18]) , ((imported_positions[20]-imported_positions[18])) );//down normal
       glm::vec3 nFront = glm::cross( (imported_positions[25]-imported_positions[24]) , ((imported_positions[26]-imported_positions[24])) );//front normal
       glm::vec3 nBack = glm::cross( (imported_positions[31]-imported_positions[30]) , ((imported_positions[32]-imported_positions[30])) );//back normal

       glm::normalize(nLeft);glm::normalize(nRight);glm::normalize(nUp);glm::normalize(nDown);glm::normalize(nFront);glm::normalize(nBack);

   //Fill the normals' vector with the corresponind normal for each vertex as defined above (imported_positions)
   imported_normals.push_back( (nLeft+nFront+nDown)/3.0f ); imported_normals.push_back( (nLeft+nFront+nUp)/3.0f ); imported_normals.push_back( (nLeft+nBack+nUp)/3.0f );
   imported_normals.push_back( (nLeft+nFront+nUp)/3.0f ); imported_normals.push_back( (nLeft+nFront+nDown)/3.0f ); imported_normals.push_back( (nLeft+nBack+nDown)/3.0f );

   imported_normals.push_back( (nRight+nFront+nUp)/3.0f ); imported_normals.push_back( (nLeft+nUp+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nFront)/3.0f );
   imported_normals.push_back( (nRight+nFront+nDown)/3.0f ); imported_normals.push_back( (nRight+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nBack)/3.0f );

   imported_normals.push_back( (nLeft+nUp+nFront)/3.0f ); imported_normals.push_back( (nLeft+nUp+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nBack)/3.0f );
   imported_normals.push_back( (nRight+nUp+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nFront)/3.0f ); imported_normals.push_back( (nLeft+nUp+nFront)/3.0f );

   imported_normals.push_back( (nLeft+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nBack)/3.0f );
   imported_normals.push_back( (nRight+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nDown+nFront)/3.0f );

   imported_normals.push_back( (nLeft+nUp+nFront)/3.0f ); imported_normals.push_back( (nRight+nUp+nFront)/3.0f ); imported_normals.push_back( (nRight+nDown+nFront)/3.0f );
   imported_normals.push_back( (nRight+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nUp+nFront)/3.0f );

   imported_normals.push_back( (nLeft+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nBack)/3.0f );
   imported_normals.push_back( (nRight+nUp+nBack)/3.0f ); imported_normals.push_back( (nLeft+nUp+nBack)/3.0f ); imported_normals.push_back( (nLeft+nDown+nBack)/3.0f );


   std::vector<glm::vec3> normals;
   for(unsigned int i=0;i<imported_normals.size();i++)
   {
       normals.push_back(glm::vec3(imported_normals[i]));
   }


   //Just For Test Purposes, to be removed






   /*   Auto Addition of Values  Supposedely Imported START*/

    std::vector<glm::vec3> positions;

   //   positions.push_back(glm::vec3( 0.5, -0.5, 0.5));positions.push_back(glm::vec3( -0.5, -0.5, -0.5));positions.push_back(glm::vec3( 0.5, 0.5, 0.0));//get all position values
   for(unsigned int i=0;i<imported_positions.size();i++)
   {
       positions.push_back(glm::vec3(imported_positions[i]));
   }


   std::vector<glm::vec4> colours;
   //   colours.push_back(glm::vec4( 1,-0, 0, 1));colours.push_back(glm::vec4( 0, 1, 0, 1));colours.push_back(glm::vec4( 1,0, 1, 1));//get all colour values
   for(unsigned int i=0;i<imported_colours.size();i++)
   {
       colours.push_back(glm::vec4(imported_colours[i]));
   }
   /*   Auto Addition of Values  Supposedely Imported END*/


   /*  Structures to the VBO */
   if(positions.size()==colours.size())
   {
       for(unsigned int i=0;i<positions.size();i++)//for all vertices imported
       {

           VertexStructure d(positions[i],colours[i],/*glm::vec2(0,0)*/ textures[i], /*glm::vec3(1,1,1)*/ normals[i],  glm::vec3(1,1,1),  glm::vec3(1,1,1));
           vertices.push_back(d);//each time add a VertexStructure of the retreived position and colour value
//           std::cout<<positions[i][1]<<","<<colours[i][1]<<std::endl;
       }
   }

   cubeVertices=positions.size();

   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStructure) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

   posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or 'zero' instead of retrieving the reference to the attribute "position input"

   glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)0);
   glEnableVertexAttribArray(posAttrib);

   //addition for colours

   colAttrib = glGetAttribLocation(m_shaderProgramId, "in_color");//or 'one' instead of retrieving the reference to the attribute "position input"
   glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)12);// 3 coordinate element vertices * 4 byte float each one
   glEnableVertexAttribArray(colAttrib);


   //addition of texture uvs

   texAttrib = glGetAttribLocation(m_shaderProgramId, "in_uv");//or '2' instead of retrieving the reference to the attribute "position input"
   glEnableVertexAttribArray(texAttrib);
   glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)28);// 4 coordinate element vertices * 4 byte float each one so.... 12 byte which is the current offset +..16 = 28
                                                                                                                                                                                   //bytes offset for the uvs

   //addition of normals

   normAttrib = glGetAttribLocation(m_shaderProgramId, "in_normal");//or '3' instead of retrieving the reference to the attribute "position input"
   glEnableVertexAttribArray(normAttrib);
   glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)36);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36
                                                                                                                                                                               //bytes offset for the normals

    //addition of bitangents

    bitanAttrib = glGetAttribLocation(m_shaderProgramId, "in_bitangent");//or '3' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(bitanAttrib);
    glVertexAttribPointer(bitanAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)48);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36

    //addition of binormals

    binorAttrib = glGetAttribLocation(m_shaderProgramId, "in_binormal");//or '3' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(binorAttrib);
    glVertexAttribPointer(binorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)60);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36



   Model myModel;                            //is allocated on Stack
   myModel.vao = vao;                        //add vao
   myModel.vbos.push_back(vbo);              //add vbo
   GameModelList[gameModelName] = myModel;  //add to std::map

}

void ModelLoader::CreateCubeModel2(const std::string& gameModelName)
{
    unsigned int vao;
    unsigned int vbo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    std::vector<VertexStructure> vertices;//our vertex positions & colors

    /*   Manual Addition of Values   */
    //   vertices.push_back(VertexStructure(glm::vec3( 0.5, -0.5, 0.5), glm::vec4( 1,-0, 0, 1)));
    //   vertices.push_back(VertexStructure(glm::vec3(-0.5, -0.5, -0.5), glm::vec4( 0, 1, 0, 1)));
    //   vertices.push_back(VertexStructure(glm::vec3( 0.5, 0.5, 0.0),  glm::vec4( 1, 0, 1, 1)));



    //   // Left bottom triangle
    //           -0.5f, 0.5f, 0f,
    //           -0.5f, -0.5f, 0f,
    //           0.5f, -0.5f, 0f,
    //           // Right top triangle
    //           0.5f, -0.5f, 0f,
    //           0.5f, 0.5f, 0f,
    //           -0.5f, 0.5f, 0f


    /*** Supposedely Imported Attributes  START***/   /*FRONT CUBE*/
    std::vector<glm::vec3> imported_positions;
    imported_positions.push_back(glm::vec3( -1 , -1, -4));imported_positions.push_back(glm::vec3( -1, 1, -4));imported_positions.push_back(glm::vec3( -1, 1, -2)); //LEFT
    imported_positions.push_back(glm::vec3( -1, 1, -2));imported_positions.push_back(glm::vec3( -1,-1, -4));imported_positions.push_back(glm::vec3( -1,-1,-2));//get all position values

    imported_positions.push_back(glm::vec3( 1 , 1, -4));imported_positions.push_back(glm::vec3( 1, 1, -2));imported_positions.push_back(glm::vec3( 1, -1, -4)); //RIGHT
    imported_positions.push_back(glm::vec3( 1,-1,-4));imported_positions.push_back(glm::vec3( 1,-1,-2));imported_positions.push_back(glm::vec3( 1,1,-2));//get all position values

    imported_positions.push_back(glm::vec3( -1,1,-4));imported_positions.push_back(glm::vec3( -1,1,-2));imported_positions.push_back(glm::vec3( 1, 1, -2)); //UP
    imported_positions.push_back(glm::vec3( 1,1,-2));imported_positions.push_back(glm::vec3(1,1,-4));imported_positions.push_back(glm::vec3(-1,1,-4));//get all position values

    imported_positions.push_back(glm::vec3( -1,-1,-4));imported_positions.push_back(glm::vec3( -1,-1,-2));imported_positions.push_back(glm::vec3( 1, -1, -2)); //DOWN
    imported_positions.push_back(glm::vec3( 1,-1,-2));imported_positions.push_back(glm::vec3(1,-1,-4));imported_positions.push_back(glm::vec3(-1,-1,-4));//get all position values

    imported_positions.push_back(glm::vec3( -1,1,-4));imported_positions.push_back(glm::vec3( 1,1,-4));imported_positions.push_back(glm::vec3( 1, -1, -4)); //FRONT
    imported_positions.push_back(glm::vec3( 1,-1,-4));imported_positions.push_back(glm::vec3(-1,-1,-4));imported_positions.push_back(glm::vec3(-1,1,-4));//get all position values

    imported_positions.push_back(glm::vec3( -1,-1,-2));imported_positions.push_back(glm::vec3( 1,-1,-2));imported_positions.push_back(glm::vec3( 1,1,-2)); //BACK
    imported_positions.push_back(glm::vec3( 1,1,-2));imported_positions.push_back(glm::vec3(-1,1,-2));imported_positions.push_back(glm::vec3(-1,-1,-2));//get all position values



    std::vector<glm::vec4> imported_colours;
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));//get all position values

    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));//get all position values

    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));//get all position values

    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));//get all position values

    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));//get all position values

    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));
    imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));imported_colours.push_back(glm::vec4( 1, 1, 1, 0.3));//get all position values


    //GLfloat texture[] = {
    //                      0,0,0,1,1,1 ,0,0,1,0,1,1, //back
    //                      0,1,1,0,1,1 ,0,0,1,0,0,1, // front
    //                      0,0,1,0,1,1 ,0,1,1,1,0,0, //top
    //                      0,0,1,0,1,1 ,0,1,1,1,0,0, //bottom
    //                      1,0,1,1,0,0 ,0,0,0,1,1,1, // left
    //                      1,0,1,1,0,0 ,0,0,0,1,1,1, // right

    //                      };

    std::vector<glm::vec2> imported_texureUVs;

    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1));
    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
    imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1));
    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
    imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1));
    imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
    imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1));
    imported_texureUVs.push_back(glm::vec2( 1, 0)); imported_texureUVs.push_back(glm::vec2( 1, 1)); imported_texureUVs.push_back(glm::vec2( 0, 0));
    imported_texureUVs.push_back(glm::vec2( 0, 0)); imported_texureUVs.push_back(glm::vec2( 0, 1)); imported_texureUVs.push_back(glm::vec2( 1, 1));




    //Calculate Vertex Normals
    std::vector<glm::vec3> imported_normals;
    glm::vec3 nLeft = glm::cross( (imported_positions[1]-imported_positions[0]) , ((imported_positions[2]-imported_positions[0])) );//left normal
    glm::vec3 nRight = glm::cross( (imported_positions[7]-imported_positions[6]) , ((imported_positions[8]-imported_positions[6])) );//right normal
    glm::vec3 nUp = glm::cross( (imported_positions[13]-imported_positions[12]) , ((imported_positions[14]-imported_positions[12])) );//up normal
    glm::vec3 nDown = glm::cross( (imported_positions[19]-imported_positions[18]) , ((imported_positions[20]-imported_positions[18])) );//down normal
    glm::vec3 nFront = glm::cross( (imported_positions[25]-imported_positions[24]) , ((imported_positions[26]-imported_positions[24])) );//front normal
    glm::vec3 nBack = glm::cross( (imported_positions[31]-imported_positions[30]) , ((imported_positions[32]-imported_positions[30])) );//back normal

    glm::normalize(nLeft);glm::normalize(nRight);glm::normalize(nUp);glm::normalize(nDown);glm::normalize(nFront);glm::normalize(nBack);

    //Fill the normals' vector with the corresponind normal for each vertex as defined above (imported_positions)
    imported_normals.push_back( (nLeft+nFront+nDown)/3.0f ); imported_normals.push_back( (nLeft+nFront+nUp)/3.0f ); imported_normals.push_back( (nLeft+nBack+nUp)/3.0f );
    imported_normals.push_back( (nLeft+nFront+nUp)/3.0f ); imported_normals.push_back( (nLeft+nFront+nDown)/3.0f ); imported_normals.push_back( (nLeft+nBack+nDown)/3.0f );

    imported_normals.push_back( (nRight+nFront+nUp)/3.0f ); imported_normals.push_back( (nLeft+nUp+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nFront)/3.0f );
    imported_normals.push_back( (nRight+nFront+nDown)/3.0f ); imported_normals.push_back( (nRight+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nBack)/3.0f );

    imported_normals.push_back( (nLeft+nUp+nFront)/3.0f ); imported_normals.push_back( (nLeft+nUp+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nBack)/3.0f );
    imported_normals.push_back( (nRight+nUp+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nFront)/3.0f ); imported_normals.push_back( (nLeft+nUp+nFront)/3.0f );

    imported_normals.push_back( (nLeft+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nBack)/3.0f );
    imported_normals.push_back( (nRight+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nDown+nFront)/3.0f );

    imported_normals.push_back( (nLeft+nUp+nFront)/3.0f ); imported_normals.push_back( (nRight+nUp+nFront)/3.0f ); imported_normals.push_back( (nRight+nDown+nFront)/3.0f );
    imported_normals.push_back( (nRight+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nDown+nFront)/3.0f ); imported_normals.push_back( (nLeft+nUp+nFront)/3.0f );

    imported_normals.push_back( (nLeft+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nDown+nBack)/3.0f ); imported_normals.push_back( (nRight+nUp+nBack)/3.0f );
    imported_normals.push_back( (nRight+nUp+nBack)/3.0f ); imported_normals.push_back( (nLeft+nUp+nBack)/3.0f ); imported_normals.push_back( (nLeft+nDown+nBack)/3.0f );



    /*** Supposedely Imported Attributes  END***/


    /*   Auto Addition of Values  Supposedely Imported START*/
    std::vector<glm::vec3> positions;
    //   positions.push_back(glm::vec3( 0.5, -0.5, 0.5));positions.push_back(glm::vec3( -0.5, -0.5, -0.5));positions.push_back(glm::vec3( 0.5, 0.5, 0.0));//get all position values
    for(unsigned i=0;i<imported_positions.size();i++)
    {
        positions.push_back(glm::vec3(imported_positions[i]));
    }


    std::vector<glm::vec4> colours;
    //   colours.push_back(glm::vec4( 1,-0, 0, 1));colours.push_back(glm::vec4( 0, 1, 0, 1));colours.push_back(glm::vec4( 1,0, 1, 1));//get all colour values
    for(unsigned int i=0;i<imported_colours.size();i++)
    {
        colours.push_back(glm::vec4(imported_colours[i]));
    }


    std::vector<glm::vec2> textures;
    for(unsigned int i=0;i<imported_texureUVs.size();i++)
    {
        textures.push_back(glm::vec2(imported_texureUVs[i]));
    }


    std::vector<glm::vec3> normals;
    for(unsigned int i=0;i<imported_normals.size();i++)
    {
        normals.push_back(glm::vec3(imported_normals[i]));
    }

    /*   Auto Addition of Values  Supposedely Imported END */




    /*  Structures to the VBO */
    if(positions.size()==colours.size())
    {
        for(unsigned int i=0;i<positions.size();i++)//for all vertices imported
        {
            vertices.push_back(VertexStructure(positions[i], colours[i], glm::vec2(0,0), normals[i], glm::vec3(0,0,0), glm::vec3(0,0,0)));//each time add a VertexStructure of the retreived position and colour value
    //           std::cout<<positions[i][1]<<","<<colours[i][1]<<std::endl;
        }
    }

    cube2Vertices=positions.size();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStructure) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    //addition of positions

    posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or '0' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)0);

    //addition of colours

    colAttrib = glGetAttribLocation(m_shaderProgramId, "in_color");//or '1' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)12);// 3 coordinate element vertices * 4 byte float each one

    //addition of texture uvs

    texAttrib = glGetAttribLocation(m_shaderProgramId, "in_uv");//or '2' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)28);// 4 coordinate element vertices * 4 byte float each one so.... 12 byte which is the current offset +..16 = 28
                                                                                                                                                                                  //bytes offset for the uvs
    //addition of normals

    normAttrib = glGetAttribLocation(m_shaderProgramId, "in_normal");//or '3' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(normAttrib);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)36);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36
                                                                                                                                                                                  //bytes offset for the normals
    //addition of bitangents

    bitanAttrib = glGetAttribLocation(m_shaderProgramId, "in_bitangent");//or '3' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(bitanAttrib);
    glVertexAttribPointer(bitanAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)48);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36

    //addition of binormals

    binorAttrib = glGetAttribLocation(m_shaderProgramId, "in_binormal");//or '3' instead of retrieving the reference to the attribute "position input"
    glEnableVertexAttribArray(binorAttrib);
    glVertexAttribPointer(binorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)60);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36


    Model myModel;                            //is allocated on Stack
    myModel.vao = vao;                        //add vao
    myModel.vbos.push_back(vbo);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map

}


void ModelLoader::CreateGrid(const std::string& gameModelName)
{
    struct point
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

    point vertices[50][50][4];

    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            vertices[i][j].x = -5+j/2;
            vertices[i][j].y = 0;
            vertices[i][j].z = i/2.0;
        }
    }


    unsigned int vao;
//    unsigned int Gridvbo,vbo2;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &Gridvbo);
    glBindBuffer(GL_ARRAY_BUFFER,Gridvbo);

    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    Model myModel;                            //is allocated on Stack
    myModel.vao = vao;                        //add vao
    myModel.vbos.push_back(Gridvbo);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map

}


void ModelLoader::createVBOgrid(const std::string & gameModelName )
{
    unsigned int vaoID;
    unsigned int vboID;

    glGetError();

    struct point
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };


    std::vector<point> Vertices;
    Vertices.reserve(3200);

    GLint gridLines = 40;
    float gridMinus = gridLines / 2;
    point Vertices1[40][40];

    for (int i = 0; i < gridLines; i++)
    {
        for (int j = 0; j < gridLines; j++)
        {
            Vertices1[i][j].x = (i-gridMinus);
            Vertices1[i][j].y = 0;
            Vertices1[i][j].z = j ;

            Vertices.push_back(Vertices1[i][j]);

//            std::cout<<" Vertices1[i][j].z ="<< Vertices1[i][j].z <<std::endl;
        }
    }


    point Vertices2[40][40];


    for (int j = 0; j < gridLines; j++)
    {
        for (int i = 0; i < gridLines; i++)
        {
            Vertices2[i][j].x = (i-gridMinus);
            Vertices2[i][j].y = 0;
            Vertices2[i][j].z = (j*gridMinus)/20;

            Vertices.push_back(Vertices2[i][j]);

//            std::cout<<" Vertices2[i][j].z ="<< Vertices2[i][j].z <<std::endl;
        }
    }




    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    std::cout<<"Vertices of Grid"<<Vertices.size()<<std::endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(point)*Vertices.size(),  &Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or 'zero' instead of retrieving the reference to the attribute "position input"

    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glEnableVertexAttribArray(0);

    Model myModel;                            //is allocated on Stack
    myModel.vao = vaoID;                        //add vao
    myModel.vbos.push_back(vboID);              //add vbo
    GameModelList[gameModelName] = myModel;  //add to std::map

}




void ModelLoader::DeleteModel(const std::string& gameModelName)
{
   Model model = GameModelList[gameModelName];
   unsigned int p = model.vao;
   glDeleteVertexArrays(1, &p);
   glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
   model.vbos.clear();
   GameModelList.erase(gameModelName);

}

unsigned int ModelLoader::GetModel(const std::string& gameModelName)
{
   return GameModelList[gameModelName].vao;
}




void ModelLoader::CreateWarriorModel(const std::string& gameModelName)
{
   //make sure we clear for each model we load, to guaranteed vboMesh refers to each model loading everytime. in ex. vboMesh.size_t() should be different for Warrrior or Cube
   vboMesh.clear();

   unsigned int vao;
   unsigned int vbo;

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);


   objLoader *objData = new objLoader();
   objData->load("models/zbrushModel/ImrodLowPolyTriangulated.obj");

   printf("Number of vertices: %i\n", objData->vertexCount);
   printf("Number of vertex normals: %i\n", objData->normalCount);
   printf("Number of texture coordinates: %i\n", objData->textureCount);
   printf("\n");


     std::cout<<"got mesh data\n";
     // now we are going to process and pack the mesh into an ngl::VertexArrayObject

     VertexStructure d(glm::vec3(0,0,0), glm::vec4(0,0,0,0), glm::vec2(0,0), glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(0,0,0));
     unsigned int nFaces=objData->faceCount;
     unsigned int nNorm=objData->normalCount;
     unsigned int nTex=objData->textureCount;
     // loop for each of the faces
     for(unsigned int i=0;i<nFaces;++i)
     {
         // now for each triangle in the face (remember we ensured tri above)
         for(int j=0;j<3;++j)
         {
             // pack in the vertex data first

             d.position.x= objData->vertexList [objData->faceList[i]->vertex_index[j]]->e[0];
             d.position.y= objData->vertexList [objData->faceList[i]->vertex_index[j]]->e[1];
             d.position.z= objData->vertexList [objData->faceList[i]->vertex_index[j]]->e[2];


             //add white color to cube
             d.color.r=1.0f;d.color.g=1.0f;d.color.b=1.0f;d.color.a=1.0f;


             // now if we have norms of tex (possibly could not) pack them as well
             if(nNorm >0 && nTex > 0)
             {
                 d.normal.x=objData->normalList [objData->faceList[i]->normal_index[j]]->e[0];
                 d.normal.y=objData->normalList [objData->faceList[i]->normal_index[j]]->e[1];
                 d.normal.z=objData->normalList [objData->faceList[i]->normal_index[j]]->e[2];


                 d.textureUV.x=objData->textureList [objData->faceList[i]->texture_index[j]]->e[0];
                 d.textureUV.y=objData->textureList [objData->faceList[i]->texture_index[j]]->e[1];

             }
             // now if neither are present (only verts like Zbrush models)
             else if(nNorm ==0 && nTex==0)
             {
                 d.normal.x=0;
                 d.normal.y=0;
                 d.normal.z=0;
                 d.textureUV.x=0;
                 d.textureUV.y=0;
             }
             // here we've got norms but not tex
             else if(nNorm >0 && nTex==0)
             {
                 d.normal.x=objData->normalList [objData->faceList[i]->normal_index[j]]->e[0];
                 d.normal.y=objData->normalList [objData->faceList[i]->normal_index[j]]->e[1];
                 d.normal.z=objData->normalList [objData->faceList[i]->normal_index[j]]->e[2];

                 d.textureUV.x=0;
                 d.textureUV.y=0;

             }
             // here we've got tex but not norm least common
             else if(nNorm ==0 && nTex>0)
             {
                 d.normal.x=0;
                 d.normal.y=0;
                 d.normal.z=0;
                 d.textureUV.x=objData->textureList [objData->faceList[i]->texture_index[j]]->e[0];
                 d.textureUV.y=objData->textureList [objData->faceList[i]->texture_index[j]]->e[1];
             }



             // now we calculate the tangent / bi-normal (tangent) based on the article here
             // http://www.terathon.com/code/tangent.html

             glm::vec3 tmp= glm::vec3(objData->normalList [objData->faceList[i]->normal_index[j]]->e[0], objData->normalList [objData->faceList[i]->normal_index[j]]->e[1], objData->normalList [objData->faceList[i]->normal_index[j]]->e[2]);

             glm::vec3 c1 = glm::cross(tmp,(glm::vec3(0.0, 0.0, 1.0)));
             glm::vec3 c2 =  glm::cross(tmp,(glm::vec3(0.0, 1.0, 0.0)));
             glm::vec3 tangent;
             glm::vec3 binormal;
             if(c1.length()>c2.length())
             {
                 tangent = c1;
             }
             else
             {
                 tangent = c2;
             }
             // now we normalize the tangent so we don't need to do it in the shader
             glm::normalize(tangent);
             // now we calculate the binormal using the model normal and tangent (cross)
             binormal = glm::cross(tmp,tangent);
             // normalize again so we don't need to in the shader
             glm::normalize(binormal);
             d.bitangent.x=tangent.x;
             d.bitangent.y=tangent.y;
             d.bitangent.z=tangent.z;
             d.binormal.x=binormal.x;
             d.binormal.y=binormal.y;
             d.binormal.z=binormal.z;

             vboMesh.push_back(d);
         }
     }


   //Create a temporary vector and copy over the data loaded from vboMesh

   std::vector<VertexStructure> vertices;//our vertex positions & colors

   vertices.resize(vboMesh.size());
   std::copy(vboMesh.begin(), vboMesh.end(), vertices.begin());

   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(VertexStructure) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

   //addition of positions

   posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or 'zero' instead of retrieving the reference to the attribute "position input"
   glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)0);
   glEnableVertexAttribArray(posAttrib);

   //addition for colours

   colAttrib = glGetAttribLocation(m_shaderProgramId, "in_color");//or 'one' instead of retrieving the reference to the attribute "position input"
   glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)12);// 3 coordinate element vertices * 4 byte float each one
   glEnableVertexAttribArray(colAttrib);

   //addition of texture uvs

   texAttrib = glGetAttribLocation(m_shaderProgramId, "in_uv");//or '2' instead of retrieving the reference to the attribute "position input"
   glEnableVertexAttribArray(texAttrib);
   glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)28);// 4 coordinate element vertices * 4 byte float each one so.... 12 byte which is the current offset +..16 = 28

   //addition of normals

   normAttrib = glGetAttribLocation(m_shaderProgramId, "in_normal");//or '3' instead of retrieving the reference to the attribute "position input"
   glEnableVertexAttribArray(normAttrib);
   glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)36);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36
                                                                                                                                                                       //bytes offset for the normals
   //addition of bitangents

   bitanAttrib = glGetAttribLocation(m_shaderProgramId, "in_bitangent");//or '3' instead of retrieving the reference to the attribute "position input"
   glEnableVertexAttribArray(bitanAttrib);
   glVertexAttribPointer(bitanAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)48);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36

   //addition of binormals

   binorAttrib = glGetAttribLocation(m_shaderProgramId, "in_binormal");//or '3' instead of retrieving the reference to the attribute "position input"
   glEnableVertexAttribArray(binorAttrib);
   glVertexAttribPointer(binorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructure), (void*)60);// 2 coordinate element vertices * 4 byte float each one so.... 8 byte which is the current offset +..8 = 36


   Model myModel;                            //is allocated on Stack
   myModel.vao = vao;                        //add vao
   myModel.vbos.push_back(vbo);              //add vbo
   GameModelList[gameModelName] = myModel;   //add to std::map


}
