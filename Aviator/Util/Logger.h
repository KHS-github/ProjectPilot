//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_LOGGER_H
#define PROJECTPILOT_LOGGER_H

#include <string>

enum class LOG_TYPE{
    LOG_INFO, LOG_WARNING, LOG_FATAL
};

typedef struct _LOG
{
    LOG_TYPE type;
    std::string owner;
    std::string message;
} Log;

void PostLog(LOG_TYPE type, std::string owner, std::string message);

#endif //PROJECTPILOT_LOGGER_H
