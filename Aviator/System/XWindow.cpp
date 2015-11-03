//
// Created by toast on 15. 10. 31.
//

//Root Components of XWindow class
#include <GL/glx.h>
#include "XWindow.h"

//Component for implement
#include "../Util/Logger.h"


static int attrListSgl[] = {
        GLX_RGBA, GLX_RED_SIZE, 4,
        GLX_GREEN_SIZE, 4,
        GLX_BLUE_SIZE, 4,
        GLX_DEPTH_SIZE, 16,
        None
};

static int attrListDbl[] = {
        GLX_RGBA, GLX_DOUBLEBUFFER,
        GLX_RED_SIZE, 4,
        GLX_GREEN_SIZE, 4,
        GLX_BLUE_SIZE, 4,
        GLX_DEPTH_SIZE, 16,
        None
};


const std::string XWindow::_XWindow = "XWindow";

XWindow::XWindow()
{
}

XWindow::~XWindow()
{
}

void XWindow::Initialize(std::string strWindowName, bool bFullScreen, int x, int y, int nWidth, int nHeight)
{
    m_strWindowName = strWindowName;
    m_bFullScreen = bFullScreen;
    m_WindowSize = Rect<int>(x, y, x+nWidth, y+nHeight);

    XVisualInfo* vi = nullptr;
    Colormap colormap;
    int i, dpyWidth, dpyHeight;
    int glxMajor, glxMinor, vmMajor, vmMinor;
    XF86VidModeModeInfo **modes;
    int modeNum, bestMode;
    Atom wmDelete;
    unsigned int borderDummy;

    int scwidth, scheight;

    bestMode = 0;
    m_pDisplay = XOpenDisplay(NULL);
    m_Screen = DefaultScreen(m_pDisplay);
    XF86VidModeQueryVersion(m_pDisplay, &vmMajor, &vmMinor);
    std::string message("XF86 VideoMode extension version : ");
    message.append(vmMajor + "." + vmMinor);
    PostLog(LOG_TYPE::LOG_INFO, _XWindow, message);
    XF86VidModeGetAllModeLines(m_pDisplay, m_Screen, &modeNum, &modes);
    m_DesktopMode = *modes[0];
    scwidth = DefaultScreenOfDisplay(m_pDisplay)->width;
    scheight = DefaultScreenOfDisplay(m_pDisplay)->height;
    /* look for mode with requested resolution */

    for (i = 0; i < modeNum; i++)
    {
        if ((modes[i]->hdisplay == scwidth) && (modes[i]->vdisplay == scheight))
            bestMode = i;
    }
    /* get an appropriate visual */
    vi = glXChooseVisual(m_pDisplay, m_Screen, attrListDbl);
    if (vi == NULL)
    {
        vi = glXChooseVisual(m_pDisplay, m_Screen, attrListSgl);
        m_bDoubleBuffered = False;
        PostLog(LOG_TYPE::LOG_INFO, _XWindow, "singlebuffered rendering will be used, no doublebuffering available");
    }
    else
    {
        m_bDoubleBuffered = True;
        PostLog(LOG_TYPE::LOG_INFO, _XWindow, "doublebuffered rendering available");
    }
    glXQueryVersion(m_pDisplay, &glxMajor, &glxMinor);
    message.clear();
    message.append("GLX-Version : ").append(glxMajor + "." + glxMinor);
    PostLog(LOG_TYPE::LOG_INFO, _XWindow, message);
    /* create a GLX context */
    m_context = glXCreateContext(m_pDisplay, vi, 0, GL_TRUE);
    /* create a color map */
    colormap = XCreateColormap(m_pDisplay, RootWindow(m_pDisplay, vi->screen),
                           vi->visual, AllocNone);
    m_WindowAttr.colormap = colormap;
    m_WindowAttr.border_pixel = 0;

    if (m_bFullScreen)
    {
        /* switch to fullscreen */
        XF86VidModeSwitchToMode(m_pDisplay, m_Screen, modes[bestMode]);
        XF86VidModeSetViewPort(m_pDisplay, m_Screen, 0, 0);
        dpyWidth = modes[bestMode]->hdisplay;
        dpyHeight = modes[bestMode]->vdisplay;
        std::string message("resolution ");
        message.append(dpyWidth + "x" + dpyHeight);
        PostLog(LOG_TYPE::LOG_INFO, _XWindow, message);
        XFree(modes);

        /* set m_targetWindow attributes */
        m_WindowAttr.override_redirect = True;
        m_WindowAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
                             StructureNotifyMask;
        m_targetWindow = XCreateWindow(m_pDisplay, RootWindow(m_pDisplay, vi->screen),
                               0, 0, dpyWidth, dpyHeight, 0, vi->depth, InputOutput, vi->visual,
                               CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect,
                               &m_WindowAttr);
        XWarpPointer(m_pDisplay, None, m_targetWindow, 0, 0, 0, 0, 0, 0);
        XMapRaised(m_pDisplay, m_targetWindow);
        XGrabKeyboard(m_pDisplay, m_targetWindow, True, GrabModeAsync,
                      GrabModeAsync, CurrentTime);
        XGrabPointer(m_pDisplay, m_targetWindow, True, ButtonPressMask,
                     GrabModeAsync, GrabModeAsync, m_targetWindow, None, CurrentTime);
    }
    else
    {
        /* create a m_targetWindow in m_targetWindow mode*/
        m_WindowAttr.event_mask = ExposureMask | KeyPressMask | ButtonPressMask |
                             StructureNotifyMask;
        m_targetWindow = XCreateWindow(m_pDisplay, RootWindow(m_pDisplay, vi->screen),
                               m_WindowSize.m_LUx, m_WindowSize.m_LUy, (unsigned int)m_WindowSize.GetWidth(), (unsigned int)m_WindowSize.GetHeight(), 0,
                                       vi->depth, InputOutput, vi->visual,
                               CWBorderPixel | CWColormap | CWEventMask, &m_WindowAttr);
        /* only set window title and handle wm_delete_events if in windowed mode */
        wmDelete = XInternAtom(m_pDisplay, "WM_DELETE_WINDOW", True);
        XSetWMProtocols(m_pDisplay, m_targetWindow, &wmDelete, 1);
        XSetStandardProperties(m_pDisplay, m_targetWindow, m_strWindowName.c_str(),
                               m_strWindowName.c_str(), None, NULL, 0, NULL);
        XMapRaised(m_pDisplay, m_targetWindow);
    }
    /* connect the glx-context to the m_targetWindow */
    glXMakeCurrent(m_pDisplay, m_targetWindow, m_context);
    if (glXIsDirect(m_pDisplay, m_context))
        PostLog(LOG_TYPE::LOG_INFO, _XWindow, "DRI enabled");
    else
        PostLog(LOG_TYPE::LOG_INFO, _XWindow, "no DRI available");
}

void XWindow::Release()
{
    if(m_context)
    {
        if(!glXMakeCurrent(m_pDisplay, None, m_context)){
            PostLog(LOG_TYPE::LOG_FATAL, _XWindow, "Could not release drawing context.");
        }
        glXDestroyContext(m_pDisplay, m_context);
        m_context = NULL;
    }

    if(m_bFullScreen)
    {
        XF86VidModeSwitchToMode(m_pDisplay, m_Screen, &m_DesktopMode);
        XF86VidModeSetViewPort(m_pDisplay, m_Screen, 0, 0);
    }
    XCloseDisplay(m_pDisplay);
}

Display*                XWindow::GetDisplay() const {return m_pDisplay;         }
int                     XWindow::GetScreen()  const {return m_Screen;           }
GLXContext              XWindow::GetGLContext()     {return m_context;          }
Window                  XWindow::GetTargetWindow()  {return m_targetWindow;     }
XSetWindowAttributes&   XWindow::GetWindowAttr()    {return m_WindowAttr;       }
bool                    XWindow::isFullScreen()     {return m_bFullScreen;      }
bool                    XWindow::isDoubleBuffered() {return m_bDoubleBuffered;  }
std::string             XWindow::GetWindowName()    {return m_strWindowName;    }
Rect<int>&              XWindow::GetWindowSize()    {return m_WindowSize;       }