//
// Created by toast on 10/24/15.
//

#include <thread>
#include "GLPro.h"

GLPro::GLPro()
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

    std::thread thr = std::thread([](){
        Display* pDisp = display;
        Window tTarget = target;
        XEvent event;
        while(true)
        {
            XNextEvent(pDisp, &event);
            switch(event.type)
            {
                case Expose:
                    break;
                case KeyPress:
                    glXMakeCurrent(pDisp, tTarget, context);
                    glXDestroyContext(pDisp, context);
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