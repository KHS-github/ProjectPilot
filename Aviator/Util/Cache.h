//
// Created by toast on 10/25/15.
//

#ifndef PROJECTPILOT_CACHE_H
#define PROJECTPILOT_CACHE_H

#include <unordered_map>

template <typename T>
class Cache
{
public:
    Cache();
    ~Cache();
private:
    std::unordered_map<std::string, T> m_mapCache;
public:
    void RegisterData(std::string name, T data);
};

#endif //PROJECTPILOT_CACHE_H
