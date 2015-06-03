#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
    Display(int width, int height, const std::string &title);

    bool isClosed() ;

    void clear(float r,float g,float b, float a);

    void update();

    virtual ~Display();

    bool m_flagLocalX=false;bool m_flagLocalY=false;bool m_flagLocalZ=false;
    int m_angleX=0;int m_angleY=0;int m_angleZ=0;

protected:


private:
    Display(const Display & display){}
    Display& operator=(const Display & display){}

    SDL_Window *m_window;
    SDL_GLContext m_glcontext;
    bool m_isClosed;


};

#endif // DISPLAY_H
