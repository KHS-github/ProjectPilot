//
// Created by toast on 10/24/15.
//

#include <string>
#include <thread>
#include <chrono>
#include <queue>
#include <time.h>

#include "Logger.h"

using namespace std::chrono_literals;

std::queue<Log*> _queueLog;
FILE* log;

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

    strftime(strTime, 50, ("./Log/%Y %m %d Log.txt"), timeinfo);
    strFileName = std::string(strTime);

    thrState = true;
    log = fopen(strFileName.c_str(), "a+");
    if(log == NULL) {
        log = fopen(strFileName.c_str(), "w");
    }

    std::thread logging = std::thread([](){
        while(thrState)
        {
            if(_queueLog.size() > 0){
                Log* logM = _queueLog.front();
                WriteLog(*logM);
                delete logM;
                _queueLog.pop();
            }
            else
                std::this_thread::sleep_for(15ms);
        }
        fclose(log);
    });
}

void WriteLog(Log& data)
{
    std::string strBaseMessage = "[" + data.owner + "] " + data.message;
    switch(data.type)
    {
        case LOG_TYPE::LOG_INFO:
            fprintf(log, ("[INFO]" + strBaseMessage).c_str());
            break;
        case LOG_TYPE::LOG_WARNING:
            fprintf(log, ("[WARNING]" + strBaseMessage).c_str());
            break;
        case LOG_TYPE::LOG_FATAL:
            fprintf(log, ("[FATAL]" + strBaseMessage).c_str());
            thrState = false;
            break;
    }
}

void PostLog(LOG_TYPE type, std::string owner, std::string message)
{
    Log* logM = new Log;
    logM->type = type;
    logM->owner = owner;
    logM->message = message;
    _queueLog.push(logM);
}