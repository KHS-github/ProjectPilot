//
// Created by toast on 15. 10. 29.
//


#ifndef PROJECTPILOT_IMAGE_H
#define PROJECTPILOT_IMAGE_H

#include <string>

#include "../../GL/RenderTarget.hpp"


class ImageRenderer : public Renderable
{
public:
    ImageRenderer();
    ~ImageRenderer();
private:
public:
    virtual void Initialize();
    virtual void Render();
};

class Image : public RenderTarget<ImageRenderer>
{
public:
    Image(Object* pParent, std::wstring strFileName, int x, int y, int width, int height);
public:
    virtual void ReadMessage(Message& message);
private:
    std::wstring m_strFileName;
protected:
    virtual void OnInitialize();
};

#endif //PROJECTPILOT_IMAGE_H
