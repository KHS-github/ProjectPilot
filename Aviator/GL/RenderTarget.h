//
// Created by toast on 15. 10. 31.
//

#ifndef PROJECTPILOT_RENDERTARGET_H
#define PROJECTPILOT_RENDERTARGET_H

#include <vector>

#include "Renderer.h"
#include "../Util/Rect.hpp"
#include "../System/Object.h"

class RenderTarget : public Object
{
private:
    const static std::string _RenderTarget;
public:
    RenderTarget(Object* pParent);
    ~RenderTarget();
protected:
    std::vector<RenderTarget*> m_childRT;
    Renderable* m_pRenderer;

    Rect<int> m_ObjectSize;

    void RemoveTarget(RenderTarget* target);
public:
    virtual void RegisterChildObj(std::string name, Object* child);
    void Render();

    const Renderable* GetRenderable();
    Rect<int>& GetObjectSize();
};


#endif //PROJECTPILOT_RENDERTARGET_H
