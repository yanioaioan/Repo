#ifndef SINGLETON_H
#define SINGLETON_H
#include <stdio.h>
#include <QtCore/QMutexLocker>

template<class T>
class Singleton
{
public:

    static T* Singleton<T>::instance(int shaderProgramId)
    {
        //force thread safety
        QMutex m;
        QMutexLocker locker(&m);

        if ( ! m_instance )//Create a new object of type T only when m_instance hasn't been created previously
        {
            m_instance = new T(shaderProgramId);
        }

        return m_instance;
    }


    static void DestroySingleton()
    {
        if (m_instance)
        {
            delete m_instance;
            m_instance = NULL;
        }
    }


protected:
    static T* m_instance;

    Singleton(){}
    virtual ~Singleton() {}
    Singleton (const Singleton & ){}
    Singleton& operator= (const Singleton & ){}

};


template<typename T>
T* Singleton<T>::m_instance = NULL;


#endif // SINGLETON_H



//https://www.google.co.uk/url?sa=t&rct=j&q=&esrc=s&source=web&cd=26&cad=rja&uact=8&ved=0CEAQtwIwBTgUahUKEwjA8dWP05bGAhWM7BQKHe1JAlU&url=http%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3D8P8fVSFJ35Q&ei=TV2BVYCXNYzZU-2TiagF&usg=AFQjCNG2MLdxq6wgczG7fkck8rQpAzmiBg
