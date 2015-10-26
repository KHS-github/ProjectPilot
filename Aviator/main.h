//
// Created by toast on 10/26/15.
//

#ifndef PROJECTPILOT_MAIN_H
#define PROJECTPILOT_MAIN_H

#include "Util/Logger.h"
#include "System/ProgramLoader.h"
#include "Aviator/Aviator.h"

class Main
{
public:
    Main();
    ~Main();
private:
    ProgramLoader* _loader;
public:
    void StartApp(int argc, char** argv);
};


ProgramLoader* getMainLoader();

#endif //PROJECTPILOT_MAIN_H
