//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_SINGLETON_H
#define PROJECTPILOT_SINGLETON_H

template <typename T>
class Singleton
{
public:
    Singleton<T>();
    ~Singleton<T>();
private:
    static T* m_pInstance;
public:
    static T* getInstance();
};


#endif //PROJECTPILOT_SINGLETON_H
