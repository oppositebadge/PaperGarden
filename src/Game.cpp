#include "Game.hpp"
#include "Globals.hpp"
#include "Tangram.hpp"
#include <cmath>
#include <raylib.h>

void Game::Update(){
    if (IsKeyPressed(KEY_R)){
        tangram->RotateTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), M_PI/4, true);
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        tangram->MoveTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), Vector2{
            GetMouseDelta().x / Globals::pixel_render->GetZoom() / Globals::pixel_render->GetVirtualRatio(),
            GetMouseDelta().y / Globals::pixel_render->GetZoom() / Globals::pixel_render->GetVirtualRatio()
        }, true);
    }
}

void Game::Draw(){
    ClearBackground(WHITE);
    tangram->Draw();    
}