//
// Created by toast on 10/25/15.
//

#include "Singleton.hpp"

template <typename T>
T* Singleton<T>::m_pInstance = nullptr;
