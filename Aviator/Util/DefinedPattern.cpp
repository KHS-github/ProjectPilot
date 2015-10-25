//
// Created by toast on 10/25/15.
//

#include "Singleton.h"


template <typename T>
T* Singleton::m_pInstance = nullptr;

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
    delete m_pInstance;
    m_pInstance = nullptr;
}

template <typename T>
T* Singleton::getInstance()
{
    if(m_pInstance == nullptr){
        return new T();
    }
    return m_pInstance;
}