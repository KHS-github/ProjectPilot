//
// Created by toast on 15. 11. 2.
//

#ifndef PROJECTPILOT_BUFFERSWITCHER_H
#define PROJECTPILOT_BUFFERSWITCHER_H

#include <GL/glew.h>
#include <string>

class BufferSwitcher
{
private:
    const static std::string _BufferSwitcher;
public:
    BufferSwitcher();
    ~BufferSwitcher();
private:
    GLuint _fbo, _offscreenTex; //#include <GL/glew.h>
    GLuint _fboDepthBuffer;
private:
    void CheckFrameBufferStatus();
public:
    void Initialize();
    void StageRendering();
    void UIRendering();
};

#endif //PROJECTPILOT_BUFFERSWITCHER_H
