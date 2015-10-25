//
// Created by toast on 10/24/15.
//

#include <thread>
#include "ProgramLoader.h"
#include "../GL/GLPro.h"

void startLogger();
void startOffice(Cache<Object*>* cacheObjects);

ProgramLoader::ProgramLoader()
{
    startLogger();
    startOffice(&m_cacheObj);
}

ProgramLoader::~ProgramLoader()
{
}

void ProgramLoader::LoadFromFile(std::string strFileName)
{
}

void ProgramLoader::Initialize()
{
    GLPro* glEngine = new GLPro();
    glEngine->startGLPro(m_pDisplay, m_pVInfo, m_targetWindow);
    m_cacheObj.RegisterData("glPro", glEngine);
    m_cacheObj.RegisterData("main", this);
}

void ProgramLoader::MainLoop()
{
    while(true)
    {
    }
}

void ProgramLoader::Process()
{
}


void ProgramLoader::SetX(int X) {m_nX = X;}
void ProgramLoader::SetY(int Y) {m_nY = Y;}
void ProgramLoader::SetHeight(int height) {m_nHeight = height;}
void ProgramLoader::SetWidth(int width) {m_nWidth = width;}
void ProgramLoader::SetName(std::string name) {m_strName = name;}