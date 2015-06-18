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

    bool m_flagLocalX;
    bool m_flagLocalY;
    bool m_flagLocalZ;
    int m_angleX;
    int m_angleY;
    int m_angleZ;

protected:


private:
    Display(const Display & ){}
    void operator=(const Display & ){}

    SDL_Window *m_window;
    SDL_GLContext m_glcontext;
    bool m_isClosed;


};

#endif // DISPLAY_H
