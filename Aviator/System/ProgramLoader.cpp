//
// Created by toast on 10/24/15.
//

#include <GL/glew.h>
#include <GL/glx.h>

//Root components of ProgramLoader

#include "PostOffice.h"
#include "../GL/BufferSwitcher.h"
#include "XWindow.h"
#include "../Util/Cache.hpp"
#include "./GUI/Stage.h"
#include "ProgramLoader.h"




void startLogger();
void Endup();


ProgramLoader::ProgramLoader() : Object(NULL), m_Worker(&m_cacheObj)
{
    startLogger();
    m_Worker.WorkingOfficer();
    m_cacheObj.RegisterData("main", this);
}

ProgramLoader::~ProgramLoader()
{
    EndupAll();
}

void ProgramLoader::OnInitialize()
{
    m_switcher.Initialize();
}

void ProgramLoader::LoadFromFile(std::string strFileName)
{
}

void ProgramLoader::MainLoop()
{
    Display* display = m_targetWindow.GetDisplay();
    while(!m_bDone)
    {
        XEvent event;
        while(XPending(display) > 0)
        {
            XNextEvent(display, &event);
            switch(event.type)
            {
                case Expose:
                    if(event.xexpose.count != 0)
                        break;
                    Process();
                    break;
                case KeyPress:
                    if(XLookupKeysym(&event.xkey, 0) == XK_Escape){
                        m_bDone = true;
                    }
                    break;
            }
        }
        Process();
    }
}

void ProgramLoader::EndupAll()
{
    m_targetWindow.Release();
    m_Worker.Release();
    Endup();
}

void ProgramLoader::Process()
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for(auto stage : m_mapStages)
    {
        ((Stage*)stage.second)->Render();
    }


    if(m_targetWindow.isDoubleBuffered()){
        glXSwapBuffers(m_targetWindow.GetDisplay(), m_targetWindow.GetTargetWindow());
    }
}


PostOffice& ProgramLoader::GetOfficer() { return m_Worker;          }
XWindow&    ProgramLoader::GetWindow()  { return m_targetWindow;    }