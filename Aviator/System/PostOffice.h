//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_POSTOFFICE_H
#define PROJECTPILOT_POSTOFFICE_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class Object;

struct Message
{
    std::string srcName;
    std::string destName;

    int header;
    char packet[2500];

};

template<typename T> class Cache;

class PostOffice
{
private:
    static int m_createdObject;
public:
    PostOffice(Cache<Object*>* cacheObject);
    ~PostOffice();
private:
    static std::mutex _queueCheck;
    static std::mutex _cacheCheck;
    static std::condition_variable _queueChecker;

    std::queue<Message*> _queueMessage;
    Cache<Object*>* _cacheObject = nullptr;

    bool _bOfficerGetOffed;
    bool _bNotified;

    std::thread* _control;
public:
    void WorkingOfficer();
    void SetTargetObjects(Cache<Object*>* cache);

    void Release();

    static void PostMail(int header, std::string srcName, std::string destName, char* packet, int size);
};


#endif //PROJECTPILOT_POSTOFFICE_H
