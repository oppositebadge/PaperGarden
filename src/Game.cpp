#include "Game.hpp"
#include "Globals.hpp"
#include "Tangram.hpp"
#include <cmath>
#include <raylib.h>

void Game::Update(){
    if (IsKeyPressed(KEY_R)){
        tangram->RotateTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), M_PI/4, true);
    }

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
    }
}

void Game::Draw(){
    ClearBackground(WHITE);
    tangram->Draw();    
}