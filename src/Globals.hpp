
#pragma once

#include "Achievements.hpp"

#include <PixelPerfect.hpp>
#include <raylib.h>
#include <string>
#include <memory>
#include <unordered_map>
#include <set>

namespace Globals {

    // Oil 6 palette for menu
    const Color menu_white = {251, 245, 239, 255};
    const Color menu_black = {39, 39, 68, 255};
    const Color menu_yellow = {242, 211, 171, 255};
    const Color menu_blue = {73, 77, 126, 255};
    const Color menu_purple = {139, 109, 156, 255};
    const Color menu_red = {198, 159, 165, 255};

    // Pico 8 for the game
    const Color pico_black = {0, 0, 0, 255};
    const Color pico_blue_dark = {29, 43, 83, 255};
    const Color pico_vineous = {126, 37, 83, 255};
    const Color pico_green_dark = {0, 135, 81, 255};
    const Color pico_green_brown = {171, 82, 54, 255};
    const Color pico_swamp = {95, 87, 79, 255};
    const Color pico_gray = {194, 195, 199, 255};
    const Color pico_white = {255, 241, 232, 255};
    const Color pico_red = {255, 0, 77, 255};
    const Color pico_orange = {255, 163, 0, 255};
    const Color pico_yellow = {255, 236, 39, 255};
    const Color pico_green = {0, 228, 54, 255};
    const Color pico_blue = {41, 173, 255, 255};
    const Color pico_purple = {131, 118, 156, 255};
    const Color pico_pink = {255, 119, 168, 255};
    const Color pico_turquoise = {255, 204, 170, 255};

    // render can be accessed from anywhere
    extern std::shared_ptr<PixelPerfect> pixel_render;
    extern std::unordered_map<std::string, Texture2D> textures;
    extern std::unordered_map<int, Achievement> Achievements;
    extern std::set<int> unlockedAchievements;  // Keeps track of unlocked ones

    void UnlockAchievement(int id);

    void SetupAchievements();
    extern std::unordered_map<std::string, Font> fonts;

    void LoadFonts();

    void LoadTextures();
    void UnloadTextures();

    Achievement FirstMissingAchievemnt(); // retuns achievement that needs to be done as it's missing in unlockedAchievements
}