//
// Created by toast on 15. 10. 31.
//

#ifndef PROJECTPILOT_WINDOW_H
#define PROJECTPILOT_WINDOW_H

#include <string>
#include "../Util/Rect.hpp"
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>

class XWindow
{
private:
    const static std::string _XWindow;
public:
    XWindow();

    ~XWindow();

private:
    Display *m_pDisplay;
    int m_Screen;
    GLXContext m_context;
    Window m_targetWindow;
    XSetWindowAttributes m_WindowAttr;
    bool m_bFullScreen;
    bool m_bDoubleBuffered;
    XF86VidModeModeInfo m_DesktopMode;
    std::string m_strWindowName;
    Rect<int> m_WindowSize;
    int m_depth;
public:
    void Initialize(std::string strWindowName, bool bFullScreen, int x, int y, int nWidth, int nHeight);
    void Release();

    Display* GetDisplay() const;
    int GetScreen() const;
    GLXContext GetGLContext();
    Window GetTargetWindow();
    XSetWindowAttributes& GetWindowAttr();
    bool isFullScreen();
    bool isDoubleBuffered();
    std::string GetWindowName();
    Rect<int>& GetWindowSize();
};

#endif //PROJECTPILOT_WINDOW_H
