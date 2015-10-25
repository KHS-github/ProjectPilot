//
// Created by toast on 10/24/15.
//

#include "GLPro.h"

GLPro::GLPro()
{
}

GLPro::~GLPro()
{
}

void GLPro::startGLPro(Display* display, XVisualInfo* info, Window target)
{
    context = glXCreateContext(display, info, NULL, GL_TRUE);
    glXMakeCurrent(display, target, context);

    glEnable(GL_DEPTH_TEST);
}

void GLPro::ReadMessage(Message& message)
{
    switch(message.header)
    {
    }
}