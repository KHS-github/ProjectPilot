//
// Created by toast on 10/24/15.
//

#include <thread>
#include "ProgramLoader.h"
#include "../GL/GLPro.h"

void startLogger();

ProgramLoader::ProgramLoader() : Object(NULL), m_Worker(&m_cacheObj)
{
    startLogger();
}

ProgramLoader::~ProgramLoader()
{
}

void ProgramLoader::LoadFromFile(std::string strFileName)
{
}

void ProgramLoader::Initialize()
{
    GLPro* glEngine = new GLPro(this);
    glEngine->startGLPro(m_pDisplay, m_pVInfo, m_targetWindow);
    m_cacheObj.RegisterData("glPro", glEngine);
    m_cacheObj.RegisterData("main", this);
}

void ProgramLoader::MainLoop()
{
    m_Worker.WorkingOfficer();
}

void ProgramLoader::Process()
{
}


void ProgramLoader::SetX(int X) { m_nX = X; }
void ProgramLoader::SetY(int Y) { m_nY = Y; }
void ProgramLoader::SetHeight(int height) { m_nHeight = height; }
void ProgramLoader::SetWidth(int width) { m_nWidth = width; }
void ProgramLoader::SetName(std::string name) { m_strName = name; }

int ProgramLoader::GetX() { return m_nX; }
int ProgramLoader::GetY() { return m_nY; }
int ProgramLoader::GetWidth() { return m_nWidth; }
int ProgramLoader::GetHeight() { return m_nHeight; }
std::string ProgramLoader::GetName() { return m_strName; }
PostOffice& ProgramLoader::GetOfficer() { return m_Worker; }