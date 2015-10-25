//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_SINGLETON_H
#define PROJECTPILOT_SINGLETON_H

template <typename T>
class Singleton
{
public:
    Singleton<T>()
    {
    }
    ~Singleton<T>()
    {
        delete m_pInstance;
        m_pInstance = nullptr;
    }
private:
    static T* m_pInstance;
public:
    static T* getInstance()
    {
        if(m_pInstance == nullptr){
            return new T();
        }
        return m_pInstance;
    }
};


#endif //PROJECTPILOT_SINGLETON_H
