#include "GameModels.h"
#include <iostream>

using namespace Models;

GameModels::GameModels(GLuint shaderProgramId)
{
    //introduce the m_shaderProgramId to the GameModels Class
    m_shaderProgramId = shaderProgramId;
}

GameModels::~GameModels()
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


void GameModels::CreateCubeModel(const std::string& gameModelName)
{
   unsigned int vao;
   unsigned int vbo;

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);

   std::vector<VertexFormat> vertices;//our vertex positions & colors

/*   Manual Addition of Values   */
//   vertices.push_back(VertexFormat(glm::vec3( 0.5, -0.5, 0.5), glm::vec4( 1,-0, 0, 1)));
//   vertices.push_back(VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec4( 0, 1, 0, 1)));
//   vertices.push_back(VertexFormat(glm::vec3( 0.5, 0.5, 0.0),  glm::vec4( 1, 0, 1, 1)));



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



   /*   Auto Addition of Values  Supposedely Imported START*/
   std::vector<glm::vec3> positions;
   //   positions.push_back(glm::vec3( 0.5, -0.5, 0.5));positions.push_back(glm::vec3( -0.5, -0.5, -0.5));positions.push_back(glm::vec3( 0.5, 0.5, 0.0));//get all position values
   for(int i=0;i<imported_positions.size();i++)
   {
       positions.push_back(glm::vec3(imported_positions[i]));
   }


   std::vector<glm::vec4> colours;
   //   colours.push_back(glm::vec4( 1,-0, 0, 1));colours.push_back(glm::vec4( 0, 1, 0, 1));colours.push_back(glm::vec4( 1,0, 1, 1));//get all colour values
   for(int i=0;i<imported_colours.size();i++)
   {
       colours.push_back(glm::vec4(imported_colours[i]));
   }
   /*   Auto Addition of Values  Supposedely Imported END*/


   /*  Structures to the VBO */
   if(positions.size()==colours.size())
   {
       for(int i=0;i<positions.size();i++)//for all vertices imported
       {
           vertices.push_back(VertexFormat(positions[i],colours[i]));//each time add a VertexFormat of the retreived position and colour value
//           std::cout<<positions[i][1]<<","<<colours[i][1]<<std::endl;
       }
   }



   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
   glEnableVertexAttribArray(0);
   posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or 'zero' instead of retrieving the reference to the attribute "position input"

   glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

   //addition for colours
   glEnableVertexAttribArray(1);

   colAttrib = glGetAttribLocation(m_shaderProgramId, "in_color");//or 'one' instead of retrieving the reference to the attribute "position input"
   glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);// 3 coordinate element vertices * 4 byte float each one

   Model myModel;                            //is allocated on Stack
   myModel.vao = vao;                        //add vao
   myModel.vbos.push_back(vbo);              //add vbo
   GameModelList[gameModelName] = myModel;  //add to std::map

}

void GameModels::CreateCubeModel2(const std::string& gameModelName)
{
unsigned int vao;
unsigned int vbo;

glGenVertexArrays(1, &vao);
glBindVertexArray(vao);

std::vector<VertexFormat> vertices;//our vertex positions & colors

/*   Manual Addition of Values   */
//   vertices.push_back(VertexFormat(glm::vec3( 0.5, -0.5, 0.5), glm::vec4( 1,-0, 0, 1)));
//   vertices.push_back(VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec4( 0, 1, 0, 1)));
//   vertices.push_back(VertexFormat(glm::vec3( 0.5, 0.5, 0.0),  glm::vec4( 1, 0, 1, 1)));



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
/*** Supposedely Imported Attributes  END***/




/*   Auto Addition of Values  Supposedely Imported START*/
std::vector<glm::vec3> positions;
//   positions.push_back(glm::vec3( 0.5, -0.5, 0.5));positions.push_back(glm::vec3( -0.5, -0.5, -0.5));positions.push_back(glm::vec3( 0.5, 0.5, 0.0));//get all position values
for(int i=0;i<imported_positions.size();i++)
{
    positions.push_back(glm::vec3(imported_positions[i]));
}


std::vector<glm::vec4> colours;
//   colours.push_back(glm::vec4( 1,-0, 0, 1));colours.push_back(glm::vec4( 0, 1, 0, 1));colours.push_back(glm::vec4( 1,0, 1, 1));//get all colour values
for(int i=0;i<imported_colours.size();i++)
{
    colours.push_back(glm::vec4(imported_colours[i]));
}
/*   Auto Addition of Values  Supposedely Imported END*/



/*  Structures to the VBO */
if(positions.size()==colours.size())
{
    for(int i=0;i<positions.size();i++)//for all vertices imported
    {
        vertices.push_back(VertexFormat(positions[i],colours[i]));//each time add a VertexFormat of the retreived position and colour value
//           std::cout<<positions[i][1]<<","<<colours[i][1]<<std::endl;
    }
}


glGenBuffers(1, &vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
posAttrib = glGetAttribLocation(m_shaderProgramId, "in_position");//or 'zero' instead of retrieving the reference to the attribute "position input"

glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

//addition for colours
glEnableVertexAttribArray(1);

colAttrib = glGetAttribLocation(m_shaderProgramId, "in_color");//or 'one' instead of retrieving the reference to the attribute "position input"
glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)12);// 3 coordinate element vertices * 4 byte float each one



Model myModel;                            //is allocated on Stack
myModel.vao = vao;                        //add vao
myModel.vbos.push_back(vbo);              //add vbo
GameModelList[gameModelName] = myModel;  //add to std::map

}


void GameModels::CreateGrid(const std::string& gameModelName)
{
    struct point
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

    point vertices[50][50];

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


void GameModels::createVBOgrid(const std::string & gameModelName )
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




void GameModels::DeleteModel(const std::string& gameModelName)
{
   Model model = GameModelList[gameModelName];
   unsigned int p = model.vao;
   glDeleteVertexArrays(1, &p);
   glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
   model.vbos.clear();
   GameModelList.erase(gameModelName);

}

unsigned int GameModels::GetModel(const std::string& gameModelName)
{
   return GameModelList[gameModelName].vao;
}
