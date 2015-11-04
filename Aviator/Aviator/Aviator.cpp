#include <GL/glew.h>
#include "Aviator.h"

#include "../System/GUI/CoverStage.h"
#include "../System/GUI/Image.h"


Aviator::Aviator() : ProgramLoader()
{
}

Aviator::~Aviator()
{
}

void Aviator::OnInitialize()
{
    m_targetWindow.Initialize("Aviator", false, 0, 0, 1024, 768);

    CoverStage* cover = new CoverStage(this);
    cover->OnInitialize();
    m_mapStages["Cover"] = cover;
    cover->RegisterChildObj("LogoImage", new Image(cover, L"./Asset/Plane.png", 0, 0, 800, 387));

    //ProgramLoader::OnInitialize();
}

void Aviator::ReadMessage(Message& message)
{
}