#pragma once

#include "Globals.hpp"
#include "Tangram.hpp"

#include <raylib.h>
#include <memory>
#include <vector>

class Game {
private:

    std::unique_ptr<Tangram> tangram = nullptr;
    int grip_id = -1;

    std::vector<Vector2> ref = {
        {1163.09, 854.849},
        {1163.09, 628.575},
        {936.817, 628.575},
        {940.575, 854.091},
        {1166.85, 854.092},
        {940.575, 627.817},
        {1269.38, 735.425},
        {1269.38, 622.287},
        {1156.24, 622.287},
        {861, 754},
        {941, 674},
        {861, 594},
        {861, 594},
        {941, 674},
        {941, 514},
        {1046.2, 629.046},
        {1272.47, 629.046},
        {1159.33, 515.909},
        {938.431, 630.569},
        {1051.57, 630.569},
        {1051.57, 517.431},
        {938.431, 630.569},
        {1051.57, 517.431},
        {938.431, 517.431},
        {1052.29, 626.091},
        {1165.42, 512.954},
        {1052.29, 512.954}
    };

public:

    Game() {
        tangram = std::make_unique<Tangram>(Globals::pixel_render->GetCameraCenter());
    }

    void Update();
    void Draw();
};