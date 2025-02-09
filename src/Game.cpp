#include "Game.hpp"
#include "Constants.hpp"
#include "Globals.hpp"
#include "Render3D.hpp"
#include "SecretsMenu.hpp"
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
        static_cast<float>(AppConstants::RenderWidth) / 2,
        static_cast<float>(AppConstants::RenderHeight) / 2
    };
    
    // Initialize components
    tangram = std::make_unique<Tangram>(Globals::pixel_render->GetCameraCenter());

    main_menu = std::make_unique<MainMenu>(center, Globals::textures["main_menu_background"], "   ", "Play", "Exit", "Secrets", true, true);
    pause_menu = std::make_unique<MainMenu>(center, Globals::textures["main_menu_background"], "Paused", "Resume", "Main Menu", "None", true,  false);
    win_menu = std::make_unique<MainMenu>(center, Globals::textures["main_menu_background"], "Congratulations\n on completing the game!", "None", "Main Menu", "None", false, false);
    secrets_menu = std::make_unique<SecretsMenu>(Globals::pixel_render->GetCameraCenter(), Globals::textures["main_menu_background"]);

    secrets_menu->SetOnExitCallback([this]() {
        current_state = MENU;
    });

    sidebar = std::make_unique<Sidebar>();
    sidebar->SetOnPauseCallback([this]() {
        current_state = PAUSED;
    });
    sidebar->SetOnSubmitCallback(std::bind(&Game::OnSubmit, this));
    render3d = std::make_unique<Render3D>();

    // Set up menu callbacks
    main_menu->SetOnPlayCallback([this]() { 
        current_state = PLAYING; 
    });
    main_menu->SetOnExitCallback([this]() {
        should_close = true;
    });
    main_menu->SetOnViewUnlocksCallback([this]() {
        current_state = VIEWING_UNLOCKS;
    });
    


    pause_menu->SetOnPlayCallback([this]() { 
        current_state = PLAYING; 
    });
    pause_menu->SetOnExitCallback([this]() {
        current_state = MENU;
    });


    win_menu->SetOnExitCallback([this]() {
        current_state = MENU;
    });
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

            /*
            if (IsKeyPressed(KEY_ENTER)){
                auto points = tangram->GetAllPoints();
                std::cout << "\nReference_" << tangram->GetPictureCount() << " = {\n";
                for (auto point : points){
                    std::cout << "\t{" << point.x << ", " << point.y << "},\n";
                }
                std::cout << "}\n\n";

                tangram->TakePicture();
            }
            */
        
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
            /*
            render3d->Update();
            if (IsKeyPressed(KEY_ESCAPE)) {
                current_state = PAUSED;
            }
            break;
            */

            secrets_menu->Update();
            break;

        case WIN:
            win_menu->Update();
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
            {
                Texture2D background = Globals::textures["game_background"];
                DrawTexturePro(
                    background,
                    Rectangle{0, 0, (float)background.width, (float)background.height},
                    Rectangle{0, 0, AppConstants::RenderWidth, AppConstants::RenderHeight},
                    Vector2{0, 0},
                    0.0f,
                    WHITE
                );
            }

            tangram->Draw();
            sidebar->Draw(Globals::textures[current_goal.reference_image_name]);
            
            break;

        case PAUSED:
            pause_menu->Draw();
            break;
        case VIEWING_UNLOCKS:

            /*
            render3d->BeginDraw();
                //DrawGrid(20, 10.0f);
                DrawModel(Globals::models["garden"], Vector3{0,0,0}, 0.05, WHITE);
            render3d->EndDraw();

            break;
            */


            secrets_menu->Draw();
            break;


        case WIN:
            win_menu->Draw();
            break;        
    }
}

void Game::OnSubmit(){
    tangram = nullptr;
    tangram = std::make_unique<Tangram>(Globals::pixel_render->GetCameraCenter());

    Globals::UnlockAchievement(Globals::FirstMissingAchievemntId());
    current_goal = Globals::FirstMissingAchievemnt();

    if (current_goal.final){
        current_state = WIN; 
    }
}