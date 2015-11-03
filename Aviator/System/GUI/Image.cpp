//
// Created by toast on 15. 10. 29.
//


#include "Image.h"

Image::Image(Object* pParent, std::wstring strFileName, int x, int y, int width, int height) : RenderTarget(pParent), m_strFileName(strFileName)
{
    m_ObjectSize = Rect<int>(x, y, x + width, y + height);
}

void Image::OnInitialize()
{
    Object::OnInitialize();
}

void Image::ReadMessage(Message &message)
{
}