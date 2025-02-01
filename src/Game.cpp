#include "Game.hpp"
#include "Tangram.hpp"
#include <raylib.h>

void Game::Update(){
    tangram->Update();
}

void Game::Draw(){
    ClearBackground(WHITE);
    tangram->Draw();    
}