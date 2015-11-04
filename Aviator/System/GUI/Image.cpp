//
// Created by toast on 15. 10. 29.
//


#include "Image.h"


ImageRenderer::ImageRenderer()
{
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Initialize()
{
}

void ImageRenderer::Render()
{
}

Image::Image(Object* pParent, std::wstring strFileName, int x, int y, int width, int height) : RenderTarget(pParent), m_strFileName(strFileName)
{
    m_ObjectSize = Rect<int>(x, y, x + width, y + height);
}

void Image::OnInitialize()
{
    RenderTarget::OnInitialize();
}

void Image::ReadMessage(Message &message)
{
}