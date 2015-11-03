#ifndef PROJECTPILOT_OBJECT_H
#define PROJECTPILOT_OBJECT_H

#include <unordered_map>
#include <string>

struct Message;
class Function;

class Object
{
    enum class OBJECT_HEADER : int
    {
        INIT = 0,
    };
public:
    Object(Object* pParent);
    ~Object();
private:
protected:
    Object* m_pParent;
    std::unordered_map<std::string, Object*> m_mapChilds;
    std::unordered_map<int, Function*> m_mapFunc;
protected:
    virtual void OnInitialize();
public:
    virtual void RegisterChildObj(std::string name, Object* child);
    virtual void ReadMessage(Message& message);

    Object* getParent();
};

#include "Function.h"


#endif