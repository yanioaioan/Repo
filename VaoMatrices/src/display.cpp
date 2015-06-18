#include "display.h"
#include <GL/glew.h>
#include <iostream>
#include <stdio.h>

Display::Display(int width,int height,const std::string & title)
{
    m_angleX=0;m_angleY=0;m_angleZ=0;
    m_flagLocalX=false;m_flagLocalY=false;m_flagLocalZ=false;

    glEnable(GL_DEPTH_TEST);

    SDL_Init(SDL_INIT_EVERYTHING);

    //initialization of colours
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32); SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);


    //window init
    m_window =SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);
    m_glcontext = SDL_GL_CreateContext(m_window);

    std::cout<<"Status: Using GLEW %s\n"<< glewGetString(GLEW_VERSION)<<std::endl;

    //****Create a GL 3.x or GL 4.x core context
    //****Make the context current (for example, on Windows you need to call wglMakeCurrent())
    //****Now let's have GL3W get the GL function pointers
    GLint GLMajorVer, GLMinorVer;
    GLenum status = glewInit();

    if(status)
    {
      std::cout<<"GLEW failed to get GL function pointers."<<std::endl;
      return;
    }
    glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVer);
    glGetIntegerv(GL_MINOR_VERSION, &GLMinorVer);
    std::cout<<GLMajorVer<<"."<<GLMinorVer<<std::endl;



    m_isClosed=false;
}

bool Display::isClosed()
{
    return m_isClosed;
}

void Display::clear(float r,float g,float b, float a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);

}

void Display::update()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;

    while(SDL_PollEvent(&e))
    {
        if(e.type==SDL_QUIT || e.key.keysym.sym==SDLK_ESCAPE)
            m_isClosed=true;


        if(e.key.keysym.sym==SDLK_UP)
        {
            m_angleX=1;
            m_flagLocalX=true;
        }
        if(e.key.keysym.sym==SDLK_DOWN)
        {
            m_angleX=-1;
            m_flagLocalX=true;
        }


        if(e.key.keysym.sym==SDLK_LEFT)
        {
            m_angleY=-1;
            m_flagLocalY=true;
        }
        if(e.key.keysym.sym==SDLK_RIGHT)
        {
            m_angleY=1;
            m_flagLocalY=true;
        }


        if(e.key.keysym.sym==SDLK_a)
        {
            m_angleZ=1;
            m_flagLocalZ=true;
        }
        if(e.key.keysym.sym==SDLK_s)
        {
            m_angleZ=-1;
            m_flagLocalZ=true;
        }


    }
}


Display::~Display()
{
    SDL_GL_DeleteContext(m_glcontext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
