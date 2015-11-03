//
// Created by toast on 10/25/15.
//
#include <GL/glew.h>
#include "../PostOffice.h"
#include "../../GL/BufferSwitcher.h"
#include "../XWindow.h"
#include "../../Util/Cache.hpp"
#include "../ProgramLoader.h"
#include "Stage.h"

Stage::Stage(ProgramLoader* pParent) : RenderTarget(pParent)
{
}

Stage::~Stage()
{
}

void Stage::ReadMessage(Message &message)
{
}