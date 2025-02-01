#pragma once

#include "Globals.hpp"
#include "Tangram.hpp"

#include <raylib.h>
#include <memory>

class Game {
private:

    std::unique_ptr<Tangram> tangram = nullptr;

public:

    Game() {
        tangram = std::make_unique<Tangram>(Globals::pixel_render->GetCameraCenter());
    }

    void Update();
    void Draw();
};