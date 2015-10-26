//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_POSTOFFICE_H
#define PROJECTPILOT_POSTOFFICE_H

#include "../Util/Cache.hpp"

class Object;

struct Message
{
    std::string srcName;
    std::string destName;

    int header;
    char packet[2500];

};


#include "Object.h"
#include <queue>

class PostOffice
{
private:
    static int m_createdObject;
public:
    PostOffice(Cache<Object*>* cacheObject);
    ~PostOffice();
private:
    std::queue<Message*> _queueMessage;
    Cache<Object*>* _cacheObject = nullptr;

    bool _bOfficerGetOffed;
public:
    void WorkingOfficer();
    void SetTargetObjects(Cache<Object*>* cache);

    static void PostMail(int header, std::string srcName, std::string destName, char* packet, int size);
};


#endif //PROJECTPILOT_POSTOFFICE_H
