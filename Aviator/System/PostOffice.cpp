#include <string>
#include <thread>
#include <queue>
#include "../Util/Cache.h"

#include "PostOffice.h"

using namespace std::chrono_literals;

std::queue<Message*> _queueMessage;
Cache<Object*> _cacheObject; = nullptr;

bool threadState = false;

void startOffice()
{
    threadState = true;
    std::thread office = std::thread([]() {
       while(threadState)
       {
           if(_queueMessage.size() > 0){
               Message* message = _queueMessage.front();
               Object* object = nullptr;
               object->ReadMessage(*message);
               _queueMessage.pop();
           }
           else
               std::this_thread::sleep_for(15ms);
       }
    });
}

void PostMessage(int header, std::string srcName, std::string destName, )