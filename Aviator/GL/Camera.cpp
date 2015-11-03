//
// Created by toast on 15. 11. 2.
//

#include "Camera.h"
#include "../main.h"

Camera::Camera() : Object(getMainLoader())
{
}

Camera::~Camera()
{
}

void Camera::OnInitialize()
{
}

void Camera::ReadMessage(Message &message)
{
    switch(message.header)
    {
    }
}