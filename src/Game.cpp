#include "Game.hpp"
#include "Globals.hpp"
#include "Render3D.hpp"
#include "Tangram.hpp"
#include "MainMenu.hpp"
#include "Sidebar.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <raylib.h>

Game::Game() : current_state(MENU) {

    current_goal = Globals::FirstMissingAchievemnt();

    Vector2 center = {
        static_cast<float>(GetScreenWidth()) / 2,
        static_cast<float>(GetScreenHeight()) / 2
    };
    
    // Initialize components
    tangram = std::make_unique<Tangram>(Globals::pixel_render->GetCameraCenter());
    main_menu = std::make_unique<MainMenu>(center, "   ", "Play", "Exit", "View Unlocks", true);
    pause_menu = std::make_unique<MainMenu>(center, "Paused", "Resume", "Main Menu", "None", false);
    sidebar = std::make_unique<Sidebar>();
    sidebar->SetOnPauseCallback([this]() {
        current_state = PAUSED;
    });
    sidebar->SetOnSubmitCallback([this]() {
        current_state = VIEWING_UNLOCKS;
    });
    render3d = std::make_unique<Render3D>();

    // Set up menu callbacks
    if (main_menu) {
        main_menu->SetOnPlayCallback([this]() { 
            current_state = PLAYING; 
        });
        main_menu->SetOnExitCallback([this]() {
            should_close = true;
        });
        main_menu->SetOnViewUnlocksCallback([this]() {
            current_state = VIEWING_UNLOCKS;
        });
    }

    if (pause_menu) {
        pause_menu->SetOnPlayCallback([this]() { 
            current_state = PLAYING; 
        });
        pause_menu->SetOnExitCallback([this]() {
            current_state = MENU;
        });
    }
}

void Game::Update() {
    switch (current_state) {
        case MENU:
            main_menu->Update();
            break;
            
        case PLAYING:            
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = PAUSED;
                break;
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
                if (IsKeyPressed(KEY_R)){
                    tangram->RotateTile(grip_id, M_PI/4);
                }
            }
            else if (IsKeyPressed(KEY_R)){
                tangram->RotateTilesAtPoint(Globals::pixel_render->GetMouseWorldPos(), M_PI/4, true);
            }

            if (IsKeyPressed(KEY_ENTER)){
                auto points = tangram->GetAllPoints();
                std::cout << "\nReference_" << tangram->GetPictureCount() << " = {\n";
                for (auto point : points){
                    std::cout << "\t{" << point.x << ", " << point.y << "},\n";
                }
                std::cout << "}\n\n";

                tangram->TakePicture();
            }
        
            {
                int percent = tangram->RatePointsSimilarityFromCenter(current_goal.reference_points);
                sidebar->SetAccuracyPercentage(percent);
                sidebar->Update();
            }
            
            break;

        case PAUSED:
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = PLAYING;
            }
            pause_menu->Update();
            break;

        case VIEWING_UNLOCKS:
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = PAUSED;
            }
            break;
    }
}

void Game::Draw() {
    ClearBackground(RAYWHITE);

    switch (current_state) {
        case MENU:
            main_menu->Draw();
            break;

        case PLAYING:
            tangram->Draw();
            sidebar->Draw(Globals::textures[current_goal.reference_image_name]);
            break;

        case PAUSED:
            pause_menu->Draw();

            break;
        case VIEWING_UNLOCKS:
            
            render3d->BeginDraw();
                DrawGrid(20, 10.0f);
            render3d->EndDraw();


            break;
    }
}