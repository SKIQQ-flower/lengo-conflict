#pragma once

#include "raylib.h"

namespace globals
{
    extern Texture2D ContainerNPatchTexture;
    extern Color PointerColor;

    void InitializeGlobals();
    void UnloadGlobals();
}
