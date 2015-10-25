//
// Created by toast on 10/24/15.
//

#include "ProgramLoader.h"

void startLogger();
void startOffice();

ProgramLoader::ProgramLoader()
{
    startLogger();
    startOffice();
}

ProgramLoader::~ProgramLoader()
{
}

void ProgramLoader::Initialize()
{
    m_cacheObj.RegisterData("main", this);
}

void ProgramLoader::MainLoop()
{
    while(true)
    {
        Process();
    }
}

void ProgramLoader::Process()
{
}