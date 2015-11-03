//
// Created by toast on 15. 10. 29.
//

#ifndef PROJECTPILOT_COVERSTAGE_H
#define PROJECTPILOT_COVERSTAGE_H

#include "Stage.h"

class CoverStage : public Stage
{
public:
    CoverStage(ProgramLoader* pParent);
private:
    //Logo Image, Text Logo Image, Background

    int m_nWidth;
    int m_nHeight;
public:
    virtual void ReadMessage(Message& message);
    virtual void OnInitialize();
};


#endif //PROJECTPILOT_COVERSTAGE_H
