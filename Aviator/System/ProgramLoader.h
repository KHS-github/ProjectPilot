//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_PROGRAMLOADER_H
#define PROJECTPILOT_PROGRAMLOADER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "Object.h"
#include "../Util/Cache.h"

class ProgramLoader : public Object
{
public:
    ProgramLoader();
    ~ProgramLoader();
private:
    Cache<Object*> m_cacheObj;
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

    virtual void Initialize() = 0;
    void MainLoop();
};

#endif //PROJECTPILOT_PROGRAMLOADER_H
