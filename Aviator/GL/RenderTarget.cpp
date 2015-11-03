//
// Created by toast on 15. 10. 31.
//

#include <typeinfo>
#include <algorithm>
#include "RenderTarget.h"
#include "../Util/Logger.h"

const std::string RenderTarget::_RenderTarget = "RenderTarget";

RenderTarget::RenderTarget(Object* pParent) : Object(pParent), m_pRenderer(NULL)
{
}

RenderTarget::~RenderTarget()
{
}

const Renderable* RenderTarget::GetRenderable()
{
    return m_pRenderer;
}

void RenderTarget::RegisterChildObj(std::string name, Object *child)
{
    Object::RegisterChildObj(name, child);
    RenderTarget* target = dynamic_cast<RenderTarget*>(child);
    if(target != NULL)
        m_childRT.push_back(target);
}

void RenderTarget::RemoveTarget(RenderTarget *target)
{
    auto found = std::find(m_childRT.begin(), m_childRT.end(), target);
    if(found != m_childRT.end())
        m_childRT.erase(found);
    else{
        PostLog(LOG_TYPE::LOG_WARNING, _RenderTarget, "You tried to delete not existing render target cache.");
    }
}

void RenderTarget::Render()
{
    if(m_pRenderer)
        m_pRenderer->Render();

    for(auto target : m_childRT){
        target->Render();
    }
}

Rect<int>& RenderTarget::GetObjectSize() { return m_ObjectSize; }