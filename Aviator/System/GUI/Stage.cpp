//
// Created by toast on 10/25/15.
//
#include <GL/glew.h>
#include "../PostOffice.h"
#include "../../GL/BufferSwitcher.h"
#include "../XWindow.h"
#include "../../Util/Cache.hpp"
#include "../ProgramLoader.h"
#include "Stage.h"
#include "../../main.h"


#define CUBE_SIZE       1.0f
#define CUBE_SIZE_HALF (CUBE_SIZE * 0.5f)


float               g_cameraPos[3] = {0.0f, 0.0f, CUBE_SIZE * 2.0f};
float               g_targetPos[3];

struct Vertex
{
    float pos[3];
    float normal[3];
};

static Vertex g_cube[24] =
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


StageRenderer::StageRenderer()
{
}

StageRenderer::~StageRenderer()
{
}


void StageRenderer::Initialize()
{
}

void StageRenderer::Render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f,
                   static_cast<float>(getMainLoader()->GetWindow().GetWindowSize().GetWidth()) / static_cast<float>(getMainLoader()->GetWindow().GetWindowSize().GetHeight()),
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glRotatef(45.f, 0.0f, 0.0f, 1.0f);

    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glNormalPointer(GL_FLOAT, sizeof(Vertex), g_cube[0].normal);
    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), g_cube[0].pos);

    glDrawArrays(GL_QUADS, 0, sizeof(g_cube) / sizeof(g_cube[0]));

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

Stage::Stage(ProgramLoader* pParent) : RenderTarget(pParent)
{
}

Stage::~Stage()
{
}

void Stage::ReadMessage(Message &message)
{
}