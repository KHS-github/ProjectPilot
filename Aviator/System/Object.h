#ifndef PROJECTPILOT_OBJECT_H
#define PROJECTPILOT_OBJECT_H

#include "PostOffice.h"

class Object
{
public:
    Object();
    ~Object();
private:
    Object* m_pParent;
public:
    virtual void ReadMessage(Message& message);

    Object* getParent();
};

#endif