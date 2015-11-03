//
// Created by toast on 15. 10. 30.
//

#ifndef PROJECTPILOT_SHAREDRESOURCES_H
#define PROJECTPILOT_SHAREDRESOURCES_H

#include <unordered_map>
#include <string>
#include "../Util/Singleton.hpp"
#include "Object.h"

#define RES_COMP_RENDERING "Rendering"

class SharedResources : public Singleton<SharedResources>
{
public:
    const static std::string _SharedResources;
    SharedResources();
    ~SharedResources();
private:
    std::unordered_map<std::string, Object*> m_mapResources;
public:
    void RegisterResource(std::string strObjectName, Object* pObject);
    void DeleteResourceByPtr(Object* pObject);
    void DeleteResourceByName(std::string strObjectName);
    const Object* SearchResource(std::string strObjectName);
};

#endif //PROJECTPILOT_SHAREDRESOURCES_H
