#include "shader.h"


Shader::Shader()
{

}

Shader::Shader(const std::string &filename)
{

}

Shader::~Shader()
{

    // If our vertex shader pointer is valid, free it
        if(m_hVertexShader)
        {
            glDetachShader(m_hProgramObject, m_hVertexShader);
            glDeleteShader(m_hVertexShader);
            m_hVertexShader = 0;
        }

        // If our fragment shader pointer is valid, free it
        if(m_hFragmentShader)
        {
            glDetachShader(m_hProgramObject, m_hFragmentShader);
            glDeleteShader(m_hFragmentShader);
            m_hFragmentShader = 0;
        }

        // If our program object pointer is valid, free it
        if(m_hProgramObject)
        {
            glDeleteShader(m_hProgramObject);
            m_hProgramObject = 0;
        }
}





///////////////////////////////// INIT SHADERS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function loads a vertex and fragment shader file
/////
///////////////////////////////// INIT SHADERS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void Shader::InitShaders(std::string strVertex, std::string strFragment)
{
    // This function actually loads and starts our shaders.  Basically,
    // we create some pointers for shaders, then load in text files for
    // each shader, then compile the shader.  We also need to create a
    // program object that represents all of our shaders.  We link the
    // loaded shaders to our program object and then turn our shader on.

    // These will hold the shader's text file data
    string strVShader, strFShader;

    // Make sure the user passed in a vertex and fragment shader file
    if(!strVertex.length() || !strFragment.length())
        return;

    // If any of our shader pointers are set, let's free them first.
    if(m_hVertexShader || m_hFragmentShader || m_hProgramObject)
        Release();

    // Here we get a pointer to our vertex and fragment shaders
    m_hVertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_hFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Now we load the shaders from the respective files and store it in a string.
    strVShader = LoadShader(strVertex.c_str());
    strFShader = LoadShader(strFragment.c_str());

    // Do a quick switch so we can do a double pointer below
    const char *szVShader = strVShader.c_str();
    const char *szFShader = strFShader.c_str();

    // Now this assigns the shader text file to each shader pointer
    glShaderSource(m_hVertexShader, 1, &szVShader, NULL);
    glShaderSource(m_hFragmentShader, 1, &szFShader, NULL);

    // Now we actually compile the shader's code
    glCompileShader(m_hVertexShader);
    glCompileShader(m_hFragmentShader);

    // Next we create a program object to represent our shaders
    m_hProgramObject = glCreateProgram();

    // We attach each shader we just loaded to our program object
    glAttachShader(m_hProgramObject, m_hVertexShader);
    glAttachShader(m_hProgramObject, m_hFragmentShader);

    // Our last init function is to link our program object with OpenGL
    glLinkProgram(m_hProgramObject);

    // Now, let's turn on our current shader.  Passing 0 will turn OFF a shader.
    glUseProgram(m_hProgramObject);
}



void Shader::Release()
{
    // To free a shader we need to detach the vertex and fragment
    // shader pointers from the program object, then free each one.
    // Once that is done we can finally delete the program object.

    // If our vertex shader pointer is valid, free it
    if(m_hVertexShader)
    {
        glDetachShader(m_hProgramObject, m_hVertexShader);
        glDeleteShader(m_hVertexShader);
        m_hVertexShader = NULL;
    }

    // If our fragment shader pointer is valid, free it
    if(m_hFragmentShader)
    {
        glDetachShader(m_hProgramObject, m_hFragmentShader);
        glDeleteShader(m_hFragmentShader);
        m_hFragmentShader = NULL;
    }

    // If our program object pointer is valid, free it
    if(m_hProgramObject)
    {
        glDeleteShader(m_hProgramObject);
        m_hProgramObject = NULL;
    }
}
