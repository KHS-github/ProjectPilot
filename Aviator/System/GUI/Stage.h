//
// Created by toast on 10/25/15.
//

#ifndef PROJECTPILOT_STAGE_H
#define PROJECTPILOT_STAGE_H

#include "../../GL/RenderTarget.hpp"

class ProgramLoader;


class StageRenderer : public Renderable{
public:
    StageRenderer();
    ~StageRenderer();
private:
public:
    virtual void Initialize();
    virtual void Render();
};

class Stage : public RenderTarget<StageRenderer>
{
private:
public:
    Stage(ProgramLoader* pParent);
    ~Stage();
private:
public:
    virtual void ReadMessage(Message& message);
    virtual void OnInitialize() = 0;
};



#endif //PROJECTPILOT_STAGE_H
