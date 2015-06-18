#ifndef ModelLoader_H
#define ModelLoader_H

#include "Vertexformat.h"
#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>
#include "singleton.h"

//namespace Models
//{



    class ModelLoader : public Singleton<ModelLoader>
    {
       friend class Singleton<ModelLoader>;

       public:

        struct Model
        {
            unsigned int vao;
            std::vector<unsigned int> vbos;

            Model(){}
        };


        //Move here so as to be accessed using the scope resolution operator
        struct point {
          GLfloat x;
          GLfloat y;
          GLfloat z;
        };

//         ModelLoader(GLuint shaderProgramId);
//        ~ModelLoader();

         void CreateCubeModel(const std::string& gameModelName);
         void CreateCubeModel2(const std::string& gameModelName);
         void CreateGrid(const std::string& gameModelName);

         void createVBOgrid(const std::string &gameModelName);


         void DeleteModel(const std::string& gameModelName);
         unsigned int GetModel(const std::string& gameModelName);


         // Create the getter and setters for the model's position
         glm::vec3  GetPosition() { return position; }
         void SetPosition(glm::vec3 _position) { position = _position; }

         // Create the getter and setters for the model's rotation
         glm::vec3  GetRotation() { return rotation; }
         void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }

         // Create the getter and setters for the model's scale
         glm::vec3  GetScale() { return scale; }
         void SetScale(glm::vec3 _scale) { scale = _scale; }

         // This sets the view matrix
         void SetViewMatrix(glm::mat4 _viewMatrix) { viewMatrix = _viewMatrix; }
         glm::mat4 GetViewMatrix(){return viewMatrix; }

         // This sets the projection matrix
         void SetProjectionMatrix(glm::mat4 _projectionMatrix) { projectionMatrix = _projectionMatrix; }
         glm::mat4 GetProjectionMatrix(){return projectionMatrix; }


         // Shader variable positions
         GLint posAttrib;
         GLint colAttrib;
         GLint texAttrib;

         // The VBO of the grid declared globally so as to be accessed by the main class
         unsigned int Gridvbo;

         GLuint m_shaderProgramId;
      private:
        std::map<std::string, Model> GameModelList;//keep our models

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        //prevent from directly create multiple objects of ModelLoader
        ModelLoader(GLuint shaderProgramId);
       ~ModelLoader();

        //private copy constructor & assignment operator
        ModelLoader (const ModelLoader & ){}
        void operator = (const ModelLoader & ){}



    };

//}


#endif // ModelLoader_H
