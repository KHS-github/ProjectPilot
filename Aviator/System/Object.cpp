//
// Created by toast on 10/25/15.
//

#include "Function.h"
#include "Object.h"

#include "PostOffice.h"

Object::Object(Object* pParent) : m_pParent(pParent)
{
}

Object::~Object()
{
}

void Object::OnInitialize()
{
    for(auto child : m_mapChilds)
    {
        ((Object*)child.second)->OnInitialize();
    }
}

void Object::RegisterChildObj(std::string name, Object *child)
{
    m_mapChilds[name] = child;
}

void Object::ReadMessage(Message &message)
{
    ReadStream stream(message.packet);
    m_mapFunc[message.header]->execute(stream);
}

Object* Object::getParent()
{
    return m_pParent;
}