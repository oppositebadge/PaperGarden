
#pragma once

#include "Achievements.hpp"

#include <PixelPerfect.hpp>
#include <raylib.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <set>

namespace Globals {
    // render can be accessed from anywhere
    extern std::shared_ptr<PixelPerfect> pixel_render;
    extern std::unordered_map<std::string, Texture2D> textures;
    extern std::unordered_map<int, Achievement> Achievements;
    extern std::set<int> unlockedAchievements;  // Keeps track of unlocked ones

    void SetupAchievements();
    extern std::unordered_map<int, Unlock> unlocks;
    extern std::unordered_map<std::string, Font> fonts;
    void SetupUnlocks();

    void LoadTextures();
    void UnloadTextures();
}