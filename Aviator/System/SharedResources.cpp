//
// Created by toast on 15. 10. 30.
//

#include "../Util/Logger.h"
#include "SharedResources.h"

const std::string SharedResources::_SharedResources = "SharedResources";

void SharedResources::RegisterResource(std::string strObjectName, Object *pObject)
{
    try{
        m_mapResources.at(RES_COMP_RENDERING);
    }
    catch(std::out_of_range){
        PostLog(LOG_TYPE::LOG_WARNING, _SharedResources, "Already allocated object string.");
    }

    m_mapResources[strObjectName] = pObject;
}

const Object* SharedResources::SearchResource(std::string strObjectName)
{
    Object* object = nullptr;
    try{
        object = m_mapResources.at(RES_COMP_RENDERING);
    }
    catch(std::out_of_range){
        PostLog(LOG_TYPE::LOG_WARNING, _SharedResources, "Unregistered Resource!");
    }

    return object;
}

void SharedResources::DeleteResourceByPtr(Object *pObject)
{
    for(auto itr : m_mapResources){
        if(itr.second == pObject){
            m_mapResources.erase(itr.first);
            return;
        }
    }

    PostLog(LOG_TYPE::LOG_WARNING, _SharedResources, "Unregistered Resource!");
}

void SharedResources::DeleteResourceByName(std::string strObjectName)
{
    m_mapResources.erase(strObjectName);
}