//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_GLPRO_H
#define PROJECTPILOT_GLPRO_H

#include <GL/gl.h>
#include <GL/glx.h>

#include "../System/Object.h"

class GLPro : public Object
{
public:
    GLPro(Object* pParent);
    ~GLPro();
private:
    GLXContext context;
public:
    void startGLPro(Display* display, XVisualInfo* info, Window target);
    void endGLPro();

    virtual void ReadMessage(Message& message);
};

#endif //PROJECTPILOT_GLPRO_H
