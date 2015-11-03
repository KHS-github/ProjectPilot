//
// Created by toast on 15. 10. 31.
//

#ifndef PROJECTPILOT_RENDERER_H
#define PROJECTPILOT_RENDERER_H

class Renderable
{
public:
    Renderable();
    ~Renderable();
public:
    virtual void Initialize() = 0;
    virtual void Render() = 0;
};

#endif //PROJECTPILOT_RENDERER_H
