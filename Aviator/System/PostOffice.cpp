#include <string>
#include <thread>
#include <queue>
#include <string.h>
#include "../Util/Cache.hpp"

#include "PostOffice.h"

using namespace std::chrono_literals;

PostOffice::PostOffice(Cache<Object*>* cacheObject) : _cacheObject(cacheObject), _bOfficerGetOffed(false)
{
}

PostOffice::~PostOffice()
{
}

void PostOffice::WorkingOfficer()
{
    _bOfficerGetOffed = true;
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
            std::this_thread::__sleep_for(15ms);
    }
}

void PostOffice::PostMail(int header, std::string srcName, std::string destName, char *packet, int size)
{
    Message* message = new Message;
    message->header = header;
    message->srcName = srcName;
    message->destName = destName;
    memcpy((void*)&message->packet, packet, sizeof(char) * size);

    _queueMessage.push(message);
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
