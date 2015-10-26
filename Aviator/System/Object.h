#ifndef PROJECTPILOT_OBJECT_H
#define PROJECTPILOT_OBJECT_H

struct Message;

#include <unordered_map>

class Object
{
public:
    Object(Object* pParent);
    ~Object();
private:
    Object* m_pParent;
    std::unordered_map<std::string, Object*> m_mapChilds;
protected:
    void RegisterChildObj(std::string name, Object* child);
public:
    virtual void ReadMessage(Message& message) = 0;

    Object* getParent();
};


#include "PostOffice.h"

#endif