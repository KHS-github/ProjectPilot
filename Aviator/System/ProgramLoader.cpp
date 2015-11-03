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
#include "ProgramLoader.h"


#define CUBE_SIZE       1.0f
#define CUBE_SIZE_HALF (CUBE_SIZE * 0.5f)


void startLogger();
void Endup();

float               g_cameraPos[3] = {0.0f, 0.0f, CUBE_SIZE * 2.0f};
float               g_targetPos[3];

struct Vertex
{
    float pos[3];
    float normal[3];
};

Vertex g_cube[24] =
        {
                // +Z face
                {-CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f,  0.0f,  1.0f},
                { CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f,  0.0f,  1.0f},
                { CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f,  0.0f,  1.0f},
                {-CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f,  0.0f,  1.0f},

                // -Z face
                { CUBE_SIZE_HALF, -CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f,  0.0f, -1.0f},
                {-CUBE_SIZE_HALF, -CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f,  0.0f, -1.0f},
                {-CUBE_SIZE_HALF,  CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f,  0.0f, -1.0f},
                { CUBE_SIZE_HALF,  CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f,  0.0f, -1.0f},

                // +Y face
                {-CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f,  1.0f,  0.0f},
                { CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f,  1.0f,  0.0f},
                { CUBE_SIZE_HALF,  CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f,  1.0f,  0.0f},
                {-CUBE_SIZE_HALF,  CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f,  1.0f,  0.0f},

                // -Y face
                {-CUBE_SIZE_HALF, -CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f, -1.0f,  0.0f},
                { CUBE_SIZE_HALF, -CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   0.0f, -1.0f,  0.0f},
                { CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f, -1.0f,  0.0f},
                {-CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   0.0f, -1.0f,  0.0f},

                // +X face
                { CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   1.0f,  0.0f,  0.0f},
                { CUBE_SIZE_HALF, -CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   1.0f,  0.0f,  0.0f},
                { CUBE_SIZE_HALF,  CUBE_SIZE_HALF, -CUBE_SIZE_HALF,   1.0f,  0.0f,  0.0f},
                { CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  CUBE_SIZE_HALF,   1.0f,  0.0f,  0.0f},

                // -X face
                {-CUBE_SIZE_HALF, -CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  -1.0f,  0.0f,  0.0f},
                {-CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  -1.0f,  0.0f,  0.0f},
                {-CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  CUBE_SIZE_HALF,  -1.0f,  0.0f,  0.0f},
                {-CUBE_SIZE_HALF,  CUBE_SIZE_HALF, -CUBE_SIZE_HALF,  -1.0f,  0.0f,  0.0f}
        };


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
//    for(auto stage : m_mapStages)
//    {
//        ((Stage*)stage.second)->Render();
//    }

    //m_switcher.StageRendering();


    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f,
                   static_cast<float>(m_targetWindow.GetWindowSize().GetWidth()) / static_cast<float>(m_targetWindow.GetWindowSize().GetHeight()),
                   0.1f, 100.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(g_cameraPos[0], g_cameraPos[1], g_cameraPos[2],
              g_targetPos[0], g_targetPos[1], g_targetPos[2],
              0.0f, 1.0f, 0.0f);

    float matAmbient[4] = {0.19225f, 0.19225f, 0.19225f, 1.0f};
    float matDiffuse[4] = {0.50754f, 0.50754f, 0.50754f, 1.0f};
    float matSpecular[4] = {0.508273f, 0.508273f, 0.508273f, 1.0f};
    float matShininess = 51.2f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, matShininess);

    glRotatef(45.f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, sizeof(Vertex), g_cube[0].normal);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), g_cube[0].pos);

    glDrawArrays(GL_QUADS, 0, sizeof(g_cube) / sizeof(g_cube[0]));

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    //m_switcher.UIRendering();

    if(m_targetWindow.isDoubleBuffered()){
        glXSwapBuffers(m_targetWindow.GetDisplay(), m_targetWindow.GetTargetWindow());
    }
}


PostOffice& ProgramLoader::GetOfficer() { return m_Worker;          }
XWindow&    ProgramLoader::GetWindow()  { return m_targetWindow;    }