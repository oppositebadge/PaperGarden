#pragma once

#include "Achievements.hpp"
#include "Tangram.hpp"
#include "MainMenu.hpp"
#include "Sidebar.hpp"
#include <Render3D.hpp>

#include <raylib.h>
#include <memory>

enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    VIEWING_UNLOCKS
};

class Game {
private:
    GameState current_state;
    std::unique_ptr<MainMenu> main_menu = nullptr;
    std::unique_ptr<MainMenu> pause_menu = nullptr;
    std::unique_ptr<Tangram> tangram = nullptr;
    std::unique_ptr<Render3D> render3d = nullptr;
    std::unique_ptr<Sidebar> sidebar = nullptr;
    bool should_close = false;

    int grip_id = -1;

    Achievement current_goal; // an achievement that the player is currently working on

public:
    Game();
    void Update();
    void Draw();
    bool ShouldClose() const { return should_close; }
};