#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Shader
{
public:
    Shader(const std::string &filename);
    Shader();
    virtual ~Shader();

    void bind();

    static std::string LoadShader(const std::string& fileName)
    {
        std::ifstream file;
        file.open((fileName).c_str());

        std::string output; std::string line;

        if(file.is_open())
        {
            while(file.good())
            {
                getline(file,line);
                output.append(line+"\n");
            }
            file.close();
        }
        else
        {
            std::cerr<<"Unable to Load Shader"<<std::endl;
        }


        std::cout<<output<<std::endl;

        return output;
    }


    void InitShaders(std::string strVertex, std::string strFragment);
    void Release();

    GLuint getVertexShaderId(){return m_hVertexShader;}
    GLuint getFragmaneShaderId(){return m_hFragmentShader;}
    GLuint getProgramShaderId(){return m_hProgramObject;}




protected:

private:

//    static const unsigned int NUM_SHADERS=2;
    Shader (const Shader & filename){}
    void operator = (const Shader & shader){}

//    GLuint m_program;
//    GLuint m_shaders[NUM_SHADERS];

    GLuint m_hVertexShader, m_hFragmentShader, m_hProgramObject;


};

#endif // SHADER_H
