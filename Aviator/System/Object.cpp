//
// Created by toast on 10/25/15.
//

#include "Object.h"

Object::Object(Object* pParent) : m_pParent(pParent)
{
}

Object::~Object()
{
}

void Object::RegisterChildObj(std::string name, Object *child)
{
    m_mapChilds[name] = child;
}

Object* Object::getParent()
{
    return m_pParent;
}