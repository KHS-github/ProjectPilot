//
// Created by toast on 15. 11. 2.
//


#include "main.h"

ProgramLoader* g_loader;

Main::Main() : _loader(nullptr)
{
}

Main::~Main()
{
}

void Main::StartApp(int argc, char** argv)
{
    _loader = new Aviator();

    g_loader = _loader;

    ((Aviator*)_loader)->OnInitialize();
    _loader->MainLoop();
}

ProgramLoader* getMainLoader()
{
    return g_loader;
}

int main(int argc, char** argv)
{
    Main I;
    I.StartApp(argc, argv);
    return 0;
}