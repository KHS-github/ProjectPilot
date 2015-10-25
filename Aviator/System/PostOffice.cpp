#include <string>
#include <thread>
#include <queue>
#include <string.h>
#include "../Util/Cache.hpp"

#include "PostOffice.h"

using namespace std::chrono_literals;

std::queue<Message*> _queueMessage;
Cache<Object*>* _cacheObject = nullptr;

static bool thrState = false;

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
}

void PostMessage(int header, std::string srcName, std::string destName, char* packet, int size)
{
    Message* message = new Message;
    message->header = header;
    message->srcName = srcName;
    message->destName = destName;
    memcpy((void*)&message->packet, packet, sizeof(char) * size);

    _queueMessage.push(message);
}

void SetupTargetObjects(Cache<Object*>* cacheObject)
{
    _cacheObject = cacheObject;
}