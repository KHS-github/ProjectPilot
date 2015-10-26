//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_PROGRAMLOADER_H
#define PROJECTPILOT_PROGRAMLOADER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "../Util/Cache.hpp"
#include "../Util/Singleton.hpp"

#include "Object.h"
#include "Stage.h"
#include "PostOffice.h"

class ProgramLoader : public Object
{
public:
    ProgramLoader();
    ~ProgramLoader();
private:
    std::unordered_map<std::string, Stage*> m_mapStages;
    Cache<Object*> m_cacheObj;
    PostOffice m_Worker;
protected:
    Display* m_pDisplay;
    XVisualInfo* m_pVInfo;
    Window m_targetWindow;
protected:
    int m_nX;
    int m_nY;
    int m_nWidth;
    int m_nHeight;

    std::string m_strName;

protected:
    virtual void Process() = 0;
public:
    void LoadFromFile(std::string strFileName);

    void SetX(int X);
    void SetY(int Y);
    void SetWidth(int width);
    void SetHeight(int height);
    void SetName(std::string strName);

    int GetX();
    int GetY();
    int GetWidth();
    int GetHeight();
    std::string GetName();
    PostOffice& GetOfficer();

    virtual void Initialize() = 0;
    void MainLoop();

    virtual void ReadMessage(Message& message) = 0;
};

#endif //PROJECTPILOT_PROGRAMLOADER_H
