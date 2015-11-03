//
// Created by toast on 10/25/15.
//

#ifndef PROJECTPILOT_STAGE_H
#define PROJECTPILOT_STAGE_H

#include "../../GL/RenderTarget.h"

class ProgramLoader;

class Stage : public RenderTarget
{
public:
    Stage(ProgramLoader* pParent);
    ~Stage();
private:
public:
    virtual void ReadMessage(Message& message);
    virtual void OnInitialize() = 0;
};



#endif //PROJECTPILOT_STAGE_H
