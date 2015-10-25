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
    Cache() {}
    ~Cache() {m_mapCache.clear();}
private:
    std::unordered_map<std::string, T> m_mapCache;
public:
    void RegisterData(std::string name, T data)
    {
        int flag = 0;
        for(auto mapData : m_mapCache)
        {
            if(mapData.second == data)
            {
                flag = 1;
            }
        }
        if(flag != 1)
            m_mapCache[name] = data;
    }
    T searchData(std::string name)
    {
        return m_mapCache[name];
    }
    void clearCache()
    {
        m_mapCache.clear();
    }
};

#endif //PROJECTPILOT_CACHE_H
