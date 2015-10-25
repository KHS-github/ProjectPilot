//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_POSTOFFICE_H
#define PROJECTPILOT_POSTOFFICE_H

#include "../Util/Cache.h"

class Object;

typedef struct _MESSAGE
{
    std::string srcName;
    std::string destName;

    int header;
    char packet[2500];

} Message;


#include "../System/Object.h"

void PostMessage(int header, std::string srcName, std::string destName, char* packet, int size);
void SetupTargetObjects(Cache<Object*>* cache);

#endif //PROJECTPILOT_POSTOFFICE_H
