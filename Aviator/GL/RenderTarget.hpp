//
// Created by toast on 15. 10. 31.
//

#ifndef PROJECTPILOT_RENDERTARGET_H
#define PROJECTPILOT_RENDERTARGET_H

#include <vector>
#include <typeinfo>
#include <algorithm>

#include "Renderer.h"
#include "../Util/Rect.hpp"
#include "../System/Object.h"
#include "../Util/Logger.h"

template <typename T>
class RenderTarget : public Object
{
private:
public:
    RenderTarget(Object* pParent) : Object(pParent), m_pRenderer(nullptr), m_bEnabled(true)
    {
    }
    ~RenderTarget()
    {
        if(!m_pRenderer)
        {
            delete m_pRenderer;
            m_pRenderer = nullptr;
        }
    }
private:
    bool m_bEnabled;
protected:
    std::vector<RenderTarget*> m_childRT;
    Renderable* m_pRenderer;

    Rect<int> m_ObjectSize;

    void RemoveTarget(RenderTarget* target)
    {
        auto found = std::find(m_childRT.begin(), m_childRT.end(), target);
        if(found != m_childRT.end())
            m_childRT.erase(found);
        else{
            PostLog(LOG_TYPE::LOG_WARNING, "RenderTarget", "You tried to delete not existing render target cache.");
        }
    }
public:
    virtual void OnInitialize()
    {
        Object::OnInitialize();
        m_pRenderer = new T();
    }
    virtual void RegisterChildObj(std::string name, Object* child)
    {
        Object::RegisterChildObj(name, child);
        RenderTarget* target = dynamic_cast<RenderTarget*>(child);
        if(target != NULL)
            m_childRT.push_back(target);
    }
    void Render()
    {
        if(m_bEnabled) {
            if (!m_pRenderer) {
                PostLog(LOG_TYPE::LOG_WARNING, "RenderTarget",
                        "You tried to use undefined Renderer object. This RenderTarget object will be disabled.");
                m_bEnabled = false;
            }
            else
                m_pRenderer->Render();

            for (auto target : m_childRT) {
                target->Render();
            }
        }
    }

    const Renderable* GetRenderable()
    {
        return m_pRenderer;
    }

    Rect<int>& GetObjectSize()
    {
        return m_ObjectSize;
    }
};


#endif //PROJECTPILOT_RENDERTARGET_H
