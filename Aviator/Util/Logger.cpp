//
// Created by toast on 10/24/15.
//

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "Logger.h"

using namespace std::chrono_literals;

std::queue<Log*> _queueLog;
FILE* log;

std::mutex _lockState;
std::mutex _lockQueue;
std::mutex _lockFile;

std::condition_variable _queueWait;

std::thread* thr;

bool thrState = false;

void WriteLog(Log& data);


void startLogger()
{
    std::string strFileName;

    time_t rawtime;
    struct tm * timeinfo;
    char strTime[50];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(strTime, 50, ("Log/%Y %m %d Log.txt"), timeinfo);
    strFileName = std::string(strTime);

    thrState = true;
    log = fopen(strFileName.c_str(), "a+");
    if(log == NULL) {
        log = fopen(strFileName.c_str(), "w");
    }

    thr = new std::thread([&](){
        {
            std::unique_lock<std::mutex> ulockFile(_lockFile);
            fprintf(log, "-------------------<Start Manager>-------------------\n");
        }
        while(true)
        {
            std::unique_lock<std::mutex> ulockState(_lockState);
            if(!thrState)break;

            std::unique_lock<std::mutex> ulockQueue(_lockQueue);
            _queueWait.wait(ulockQueue);

            while(!_queueLog.empty()) {
                Log *logM = _queueLog.front();
                WriteLog(*logM);
                delete logM;
                _queueLog.pop();
            }
        }

        {
            std::unique_lock<std::mutex> ulockFile(_lockFile);
            fprintf(log, "\n\n");
            fclose(log);
        }
    });
}

void WriteLog(Log& data)
{
    std::string strBaseMessage = "[" + data.owner + "] " + data.message + "\n";
    char* strMessage;
    switch(data.type)
    {
        case LOG_TYPE::LOG_INFO:
            strMessage = (char*)("[INFO]" + strBaseMessage).c_str();
            break;
        case LOG_TYPE::LOG_WARNING:
            strMessage = (char*)("[WARNING]" + strBaseMessage).c_str();
            break;
        case LOG_TYPE::LOG_FATAL:
            strMessage = (char*)("[FATAL]" + strBaseMessage).c_str();
            thrState = false;
            break;
    }

    std::unique_lock<std::mutex> ulockFile(_lockFile);
    fprintf(log, strMessage);
    printf(strMessage);
}

void Endup()
{
    thrState = false;
    thr->join();
}

void PostLog(LOG_TYPE type, std::string owner, std::string message)
{
    Log* logM = new Log;
    logM->type = type;
    logM->owner = owner;
    logM->message = message;

    std::unique_lock<std::mutex> ulockQueue(_lockQueue);
    _queueLog.push(logM);
    _queueWait.notify_one();
}