//
// Created by toast on 15. 10. 30.
//

#ifndef PROJECTPILOT_FUNCTION_H
#define PROJECTPILOT_FUNCTION_H

#include <unordered_map>
#include "../Util/Stream.h"

class Object;

class Function
{
public:
    Function(Object* pParent) : m_pParent(pParent){
    }
    ~Function(){
        for(auto f : m_mapFunctions) {
            delete f.second;
        }
    }
protected:
    Object* m_pParent;
    std::unordered_map<int, Function*> m_mapFunctions;
public:
    virtual void functions() = 0;
    virtual void execute(ReadStream& stream) = 0;
};

#include "Object.h"

#endif //PROJECTPILOT_FUNCTION_H
