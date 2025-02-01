#include "Game.hpp"
#include "Globals.hpp"
#include "Tangram.hpp"
#include <cmath>
#include <iostream>
#include <raylib.h>

Color GetPercentColor(int percent){
    if (percent >= 90) return GREEN;
    else if (percent >= 70) return YELLOW;
    else if (percent >= 50) return ORANGE;
    else return RED;
}

void Game::Update(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        grip_id = tangram->GetIdAtPoint(Globals::pixel_render->GetMouseWorldPos());
    }
    if ((IsMouseButtonReleased(MOUSE_LEFT_BUTTON))){
        grip_id = -1;
    }

    if (grip_id != -1){
        tangram->MoveTile(grip_id, 
            Vector2{
                GetMouseDelta().x / Globals::pixel_render->GetZoom() / Globals::pixel_render->GetVirtualRatio(),
                GetMouseDelta().y / Globals::pixel_render->GetZoom() / Globals::pixel_render->GetVirtualRatio()
            }
        );
        if (IsKeyPressed(KEY_R)){
            tangram->RotateTile(grip_id, M_PI/4);
        }
    }
    else if (IsKeyPressed(KEY_R)){
        tangram->RotateTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), M_PI/4, true);
    }

    if (IsKeyPressed(KEY_ENTER)){
        auto points = tangram->GetAllPoints();
        std::cout << "{\n";
        for (auto point : points){
            std::cout << "\t{" << point.x << ", " << point.y << "},\n";
        }
        std::cout << "}\n";
    }
}

void Game::Draw(){
    ClearBackground(GRAY);
    tangram->Draw();    
    
    int percent = tangram->RatePointsSimilarityFromCenter(ref);
    DrawText(
        TextFormat("Similarity: %i", percent),
        Globals::pixel_render->GetCameraCenter().x,
        100, 
        64, 
        GetPercentColor(percent)
    );
}