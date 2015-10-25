#include <string>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

#include "Aviator.h"


Aviator::Aviator() : ProgramLoader()
{
}

Aviator::~Aviator()
{
}

void Aviator::Initialize()
{
    Display* display = nullptr;
    Window root, aviatorWnd;
    XWindowAttributes windowAttr;
    XVisualInfo* info = nullptr;
    Colormap colormap;
    int attr[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

    display = XOpenDisplay(NULL);

    root = XDefaultRootWindow(display);

    XGetWindowAttributes(display, root, &windowAttr);

    info = glXChooseVisual(display, 0, attr);

    colormap = XCreateColormap(display, root, info->visual, AllocNone);

    XSetWindowAttributes aviatorAttr;
    aviatorAttr.colormap = colormap;
    aviatorAttr.event_mask = ExposureMask | KeyPressMask;

    aviatorWnd = XCreateWindow(display, root, windowAttr.x, windowAttr.y, windowAttr.width, windowAttr.height, 0, 0, InputOnly, info->visual
            , CWColormap | CWEventMask, &aviatorAttr);

    XMapWindow(display, aviatorWnd);
    XStoreName(display, aviatorWnd, "User friendly GUI Environment and Development");

    m_pDisplay = display;
    m_targetWindow = aviatorWnd;
    m_pVInfo = info;
    m_nX = windowAttr.x;
    m_nY = windowAttr.y;
    m_nWidth = windowAttr.width;
    m_nHeight = windowAttr.height;
    m_strName = "Aviator";
}

void Aviator::Process()
{
    ProgramLoader::Process();
}

void Aviator::ReadMessage(Message& message)
{
}

int main(int argc, char** argv)
{
    Aviator* pTest = new Aviator();
    pTest->Initialize();

    pTest->MainLoop();

    return 0;
}