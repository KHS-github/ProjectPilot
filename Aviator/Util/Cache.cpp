//
// Created by toast on 10/25/15.
//

#include "Cache.h"

template <typename T>
Cache::Cache<T>()
{
}

template <typename T>
Cache::~Cache<T>()
{
}

template <typename T>
void Cache<T>::RegisterData(std::string name, T data)
{
    m_mapCache[name] = data;
}

