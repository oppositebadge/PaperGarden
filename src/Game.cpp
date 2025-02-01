#include "Game.hpp"
#include "Globals.hpp"
#include "Tangram.hpp"
#include "MainMenu.hpp"
#include <cmath>
#include <iostream>
#include <raylib.h>
#include "Constants.hpp"

Game::Game() : current_state(GameState::MENU) {
    Vector2 center = {
        static_cast<float>(GetScreenWidth()) / 2,
        static_cast<float>(GetScreenHeight()) / 2
    };
    
    // Initialize components
    tangram = std::make_unique<Tangram>();
    main_menu = std::make_unique<MainMenu>(center, "Paper Garden", "Play", "Exit");
    pause_menu = std::make_unique<MainMenu>(center, "Paused", "Resume", "Exit to Main Menu");

    // Set up menu callbacks
    if (main_menu) {
        main_menu->SetOnPlayCallback([this]() { 
            current_state = GameState::PLAYING; 
        });
        main_menu->SetOnExitCallback([this]() {
            should_close = true;
        });
    }

    if (pause_menu) {
        pause_menu->SetOnPlayCallback([this]() { 
            current_state = GameState::PLAYING; 
        });
        pause_menu->SetOnExitCallback([this]() {
            current_state = GameState::MENU;
        });
    }
}

void Game::Update() {
    if (!IsWindowReady()) return;

    switch (current_state) {
        case GameState::MENU:
            if (main_menu) main_menu->Update();
            break;
            
        case GameState::PLAYING:
            Globals::pixel_render->Update();
            
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = GameState::PAUSED;
                break;
            }
            
            if (tangram) {
                if (IsKeyPressed(KEY_R)) {
                    tangram->RotateTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), M_PI/4, true);
                }
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    tangram->MoveTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), Vector2{
                        GetMouseDelta().x / Globals::pixel_render->GetZoom() / Globals::pixel_render->GetVirtualRatio(),
                        GetMouseDelta().y / Globals::pixel_render->GetZoom() / Globals::pixel_render->GetVirtualRatio()
                    }, true);
                }
            }
            break;

        case GameState::PAUSED:
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = GameState::PLAYING;
            }
            if (pause_menu) pause_menu->Update();
            break;
    }
}

void Game::Draw() {
    if (!IsWindowReady()) return;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (current_state) {
        case GameState::MENU:
            if (main_menu) main_menu->Draw();
            break;
            
        case GameState::PLAYING:
        case GameState::PAUSED:
            // Draw game state first
            if (tangram) {
                Globals::pixel_render->BeginDraw();
                ClearBackground(RAYWHITE);
                tangram->Draw();
                Globals::pixel_render->EndDraw();
                
                ClearBackground(BLACK);
                Globals::pixel_render->DrawResult();
            }
            
            // If paused, draw the overlay and menu
            if (current_state == GameState::PAUSED) {
                BeginBlendMode(BLEND_ALPHA);
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{0, 0, 0, 180});
                EndBlendMode();
                
                if (pause_menu) pause_menu->Draw();
            }
            break;
    }
    
    EndDrawing();
}