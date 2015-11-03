#include <string>
#include <string.h>
#include "../Util/Cache.hpp"
#include "../Util/Logger.h"

#include "Object.h"
#include "PostOffice.h"

#include "../main.h"

using namespace std::chrono_literals;

int PostOffice::m_createdObject = 0;


std::mutex PostOffice::_queueCheck;
std::mutex PostOffice::_cacheCheck;
std::condition_variable PostOffice::_queueChecker;

PostOffice::PostOffice(Cache<Object*>* cacheObject) : _cacheObject(cacheObject), _bOfficerGetOffed(false), _bNotified(false)
{
    if(m_createdObject == 1){
        PostLog(LOG_TYPE::LOG_WARNING, "PostOffice.cpp", "PostOffice can't be created twice.");
        return;
    }
    m_createdObject++;
}

PostOffice::~PostOffice()
{
    Release();
}

void PostOffice::WorkingOfficer()
{
    _bOfficerGetOffed = true;
    _control = new std::thread([&](){
        while(_bOfficerGetOffed)
        {
            std::unique_lock<std::mutex> locker(_queueCheck);
            while(!_bNotified)
            {
                _queueChecker.wait(locker);
            }

            std::unique_lock<std::mutex> locker0(_cacheCheck);
            while(_queueMessage.size() > 0 && _cacheObject != nullptr)
            {
                Message *message = _queueMessage.front();
                Object *object = _cacheObject->searchData(message->destName);
                object->ReadMessage(*message);
                delete message;
                _queueMessage.pop();
            }

            _bNotified = false;
        }
    });
}

void PostOffice::PostMail(int header, std::string srcName, std::string destName, char *packet, int size)
{
    Message* message = new Message;
    message->header = header;
    message->srcName = srcName;
    message->destName = destName;
    memcpy((void*)&message->packet, packet, sizeof(char) * size);

    std::unique_lock<std::mutex> locker(_queueCheck);
    getMainLoader()->GetOfficer()._queueMessage.push(message);
    getMainLoader()->GetOfficer()._bNotified = true;
    getMainLoader()->GetOfficer()._queueChecker.notify_one();
}

void PostOffice::SetTargetObjects(Cache<Object *> *cache)
{
    _cacheObject = cache;
}

void PostOffice::Release()
{
    if(_control != nullptr)
    {
        _bOfficerGetOffed = false;
        _control->join();
        delete _control;
        _control = nullptr;
    }
}