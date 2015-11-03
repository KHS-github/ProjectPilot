//
// Created by toast on 15. 11. 2.
//

#ifndef PROJECTPILOT_CAMERA_H
#define PROJECTPILOT_CAMERA_H

#include "../System/PostOffice.h"
#include "../System/Function.h"
#include "../System/Object.h"

class Camera : public Object
{
public:
    Camera();
    ~Camera();
private:
public:
    virtual void OnInitialize();
    virtual void ReadMessage(Message& message);
};

#endif //PROJECTPILOT_CAMERA_H
