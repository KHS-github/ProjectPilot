//
// Created by toast on 15. 10. 29.
//

#include <GL/glew.h>
#include "CoverStage.h"
#include "../../main.h"

CoverStage::CoverStage(ProgramLoader* pParent) : Stage(pParent), m_nWidth(getMainLoader()->GetWindow().GetWindowSize().GetWidth()),
                                                 m_nHeight(getMainLoader()->GetWindow().GetWindowSize().GetHeight())
{
}

void CoverStage::OnInitialize()
{
    Object::OnInitialize();
}

void CoverStage::ReadMessage(Message &message)
{
}