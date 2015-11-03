//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_AVIATOR_H
#define PROJECTPILOT_AVIATOR_H

#include "../System/GUI/Stage.h"
#include "../System/PostOffice.h"
#include "../GL/BufferSwitcher.h"
#include "../System/XWindow.h"
#include "../Util/Cache.hpp"
#include "../System/ProgramLoader.h"

class Aviator : public ProgramLoader
{
public:
    Aviator();
    ~Aviator();
private:
public:
    virtual void OnInitialize();
    virtual void ReadMessage(Message& message);
protected:
};

#endif //PROJECTPILOT_AVIATOR_H
