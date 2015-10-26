//
// Created by toast on 10/24/15.
//

#include <thread>
#include "GLPro.h"

GLPro::GLPro(Object* pParent) : Object(pParent)
{
}

GLPro::~GLPro()
{
    endGLPro();
}

void GLPro::startGLPro(Display* display, XVisualInfo* info, Window target)
{
    context = glXCreateContext(display, info, NULL, GL_TRUE);
    glXMakeCurrent(display, target, context);

    glEnable(GL_DEPTH_TEST);

    std::thread([display, info, target, this](){
        XEvent event;
        while(true)
        {
            XNextEvent(display, &event);
            switch(event.type)
            {
                case Expose:
                    break;
                case KeyPress:
                    glXMakeCurrent(display, target, context);
                    glXDestroyContext(display, context);
                    return;
            }
        }
    });
}

void GLPro::ReadMessage(Message& message)
{
    switch(message.header)
    {
    }
}

void GLPro::endGLPro()
{
}