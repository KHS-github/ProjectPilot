//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_AVIATOR_H
#define PROJECTPILOT_AVIATOR_H

#include "./System/ProgramLoader.h"

class Aviator : public ProgramLoader
{
public:
    Aviator();
    ~Aviator();
private:
public:
    virtual void Initialize();
protected:
    virtual void Process();
};

#endif //PROJECTPILOT_AVIATOR_H
