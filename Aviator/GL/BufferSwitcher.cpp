//
// Created by toast on 15. 11. 2.
//

#include <GL/glew.h>
#include "BufferSwitcher.h"
#include "../main.h"

const std::string BufferSwitcher::_BufferSwitcher = "BufferSwitcher";

BufferSwitcher::BufferSwitcher()
{
}

BufferSwitcher::~BufferSwitcher()
{
}

void BufferSwitcher::CheckFrameBufferStatus()
{
    switch (glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT))
    {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            break;

        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Unsupported framebuffer format.");

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Missing attachment.");

        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Duplicate attachment.");

        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Attached images must have the same dimensions.");

        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Attached images must have the same format.");

        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Missing draw buffer.");

        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Missing read buffer.");

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Attached images must have the same number of samples.");

        default:
            PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "Setup FBO failed. Fatal error.");
    }
}

void BufferSwitcher::Initialize()
{
    int width = getMainLoader()->GetWindow().GetWindowSize().GetWidth();
    int height = getMainLoader()->GetWindow().GetWindowSize().GetHeight();
    // Create the FBO and bind it. We're not supporting multisample rendering
    // here. So that means two things: we only need a single FBO and everything
    // attaches directly to that single FBO.

    glGenFramebuffersEXT(1, &_fbo);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbo);

    // Create a texture for the FBO to render to. Since this is for offscreen
    // rendering we don't need mipmaps and we clamp the texture at its edges.

#if defined(USE_GL_ARB_TEXTURE_NON_POWER_OF_TWO)
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &g_offscreenTexture);
    glBindTexture(GL_TEXTURE_2D, g_offscreenTexture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_fboWidth, g_fboHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, g_offscreenTexture, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
#else
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glGenTextures(1, &_offscreenTex);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, _offscreenTex);
    glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_RECTANGLE_ARB, _offscreenTex, 0);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, 0);
    glDisable(GL_TEXTURE_RECTANGLE_ARB);
#endif

    // Create a depth render buffer image for the FBO.

    glGenRenderbuffersEXT(1, &_fboDepthBuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _fboDepthBuffer);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _fboDepthBuffer);

    // Verify that the FBO is 'complete'.
    // Once the FBO is complete it is ready for us to render to.

    CheckFrameBufferStatus();

    // Verify that the FBO dimensions are of the expected size.

    int actualWidth = 0;
    int actualHeight = 0;

    glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_WIDTH_EXT, &actualWidth);
    glGetRenderbufferParameterivEXT(GL_RENDERBUFFER_EXT, GL_RENDERBUFFER_HEIGHT_EXT, &actualHeight);

    if(actualWidth != width)
        PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "ActualWidth is not corresponded with width!");


    if(actualHeight != height)
        PostLog(LOG_TYPE::LOG_FATAL, _BufferSwitcher, "ActualHeight is not corresponded with height!");

    // Unbind the FBO and switch back to normal window rendering.

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void BufferSwitcher::StageRendering()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

void BufferSwitcher::UIRendering()
{
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fbo);
}