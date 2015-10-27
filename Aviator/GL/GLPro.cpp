//
// Created by toast on 10/24/15.
//

#include <thread>
#include "GLPro.h"
#include "../Util/Stream.h"

void Renderer(Display* display, Window target, GLXContext context)
{
    /*XEvent event;
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
    }*/
}

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
    glXMakeCurrent(display, target, context);//Error

    glEnable(GL_DEPTH_TEST);
}

void GLPro::startRenderer(Display* display, Window target)
{
    //std::thread(Renderer, display, target, context);
    XEvent event;
    while(true)
    {
        XNextEvent(display, &event);
        switch(event.type)
        {
            case Expose:
                glClearColor(0.5, 0.5, 0.5, 1.0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnd();
                break;
            case KeyPress:
                glXMakeCurrent(display, target, context);
                glXDestroyContext(display, context);
                return;
        }
    }
}

void GLPro::ReadMessage(Message& message)
{
    switch(message.header)
    {
        case 0:
        {
            ReadStream stream(message.packet);
            Display *display = (Display *) stream.ReadObjPointer();
            XVisualInfo *info = (XVisualInfo *) stream.ReadObjPointer();
            Window window = (unsigned long) stream.ReadLong();
            startGLPro(display, info, window);
            break;
        }
        case 1:
        {
            ReadStream stream(message.packet);
            Display* display = (Display*) stream.ReadObjPointer();
            Window window = (unsigned long)stream.ReadLong();
            startRenderer(display, window);
            break;
        }
    }
}

void GLPro::endGLPro()
{
}