#pragma once

#include "Globals.hpp"
#include "Tangram.hpp"

#include <raylib.h>
#include <memory>

class Game {
private:

    std::unique_ptr<Tangram> tangram = nullptr;
    int grip_id = -1;

public:

    Game() {
        tangram = std::make_unique<Tangram>(Globals::pixel_render->GetCameraCenter());
    }

    void Update();
    void Draw();
};