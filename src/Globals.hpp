
#pragma once

#include "Unlocks.hpp"

#include <PixelPerfect.hpp>
#include <raylib.h>
#include <string>
#include <memory>
#include <unordered_map>

namespace Globals {
    // render can be accessed from anywhere
    extern std::shared_ptr<PixelPerfect> pixel_render;
    extern std::unordered_map<std::string, Texture2D> textures;
    extern std::unordered_map<int, Unlock> unlocks;

    void SetupUnlocks();

    void LoadTextures();
    void UnloadTextures();
}