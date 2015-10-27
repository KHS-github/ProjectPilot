#include <string>
#include <thread>
#include <queue>
#include <string.h>
#include "../Util/Cache.hpp"
#include "../Util/Logger.h"

#include "PostOffice.h"

#include "../main.h"

using namespace std::chrono_literals;

int PostOffice::m_createdObject = 0;

PostOffice::PostOffice(Cache<Object*>* cacheObject) : _cacheObject(cacheObject), _bOfficerGetOffed(false)
{
    if(m_createdObject == 1){
        PostLog(LOG_TYPE::LOG_WARNING, "PostOffice.cpp", "PostOffice can't be created twice.");
        return;
    }
    m_createdObject++;
}

PostOffice::~PostOffice()
{
}

void PostOffice::WorkingOfficer()
{
    _bOfficerGetOffed = true;
    PostMail(0, "System", "main", "Hello!", strlen("Hello!"));
    while(_bOfficerGetOffed)
    {
        if(_queueMessage.size() > 0 && _cacheObject != nullptr){
            Message* message = _queueMessage.front();
            Object* object =_cacheObject->searchData(message->destName);
            object->ReadMessage(*message);
            delete message;
            _queueMessage.pop();
        }
        else
            std::this_thread::sleep_for(15ms);
    }
}

void PostOffice::PostMail(int header, std::string srcName, std::string destName, char *packet, int size)
{
    Message* message = new Message;
    message->header = header;
    message->srcName = srcName;
    message->destName = destName;
    memcpy((void*)&message->packet, packet, sizeof(char) * size);

    getMainLoader()->GetOfficer()._queueMessage.push(message);
}

/*
void startOffice(Cache<Object*>* cacheObject)
{
    SetupTargetObjects(cacheObject);
    thrState = true;
    std::thread office = std::thread([]() {
       while(thrState)
       {
           if(_queueMessage.size() > 0 && _cacheObject != nullptr){
               Message* message = _queueMessage.front();
               Object* object = _cacheObject->searchData(message->destName);
               object->ReadMessage(*message);
               delete message;
               message = nullptr;
               _queueMessage.pop();
           }
           else
               std::this_thread::sleep_for(15ms);
       }
    });
}*/


void PostOffice::SetTargetObjects(Cache<Object *> *cache)
{
    _cacheObject = cache;
}
