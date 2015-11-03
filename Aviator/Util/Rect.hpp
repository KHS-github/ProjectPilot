//
// Created by toast on 15. 10. 30.
//

#ifndef PROJECTPILOT_RECT_H
#define PROJECTPILOT_RECT_H

template <class T>
class Rect
{
public:
    Rect<T>(){}
    Rect<T>(T LUx, T LUy, T RBx, T RBy) : m_LUx(LUx), m_LUy(LUy), m_RBx(RBx), m_RBy(RBy){ }
    ~Rect<T>(){}
public:
    T m_LUx;
    T m_LUy;
    T m_RBx;
    T m_RBy;

    T GetWidth(){
        return m_RBx - m_LUx;
    }

    T GetHeight(){
        return m_RBy - m_LUy;
    }

    T GetCenterX(){
        return m_LUx + GetWidth() / 2.f;
    }

    T GetCenterY(){
        return m_LUy + GetHeight() / 2.f;
    }
};

#endif //PROJECTPILOT_RECT_H