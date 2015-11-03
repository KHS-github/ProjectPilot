//
// Created by toast on 10/24/15.
//

#ifndef PROJECTPILOT_PROGRAMLOADER_H
#define PROJECTPILOT_PROGRAMLOADER_H

#include <unordered_map>
#include "Object.h"

class Stage;
class PostOffice;
class BufferSwitcher;
template <typename T> class Cache;
class XWindow;

#define LOADER_DEFAULT_INIT 0
#define LOADER_DEFAULT_DELETE 1

class ProgramLoader : public Object
{
public:
    ProgramLoader();
    ~ProgramLoader();
private:
    PostOffice m_Worker;
    BufferSwitcher m_switcher;
protected:
    std::unordered_map<std::string, Stage*> m_mapStages;
    Cache<Object*> m_cacheObj;
    XWindow m_targetWindow;
    bool m_bDone;
protected:
    void Process();
private:
    void EndupAll();
public:
    void LoadFromFile(std::string strFileName);
    PostOffice& GetOfficer();
    XWindow& GetWindow();

    virtual void OnInitialize();
    void MainLoop();

    virtual void ReadMessage(Message& message) = 0;
};

#endif //PROJECTPILOT_PROGRAMLOADER_H
