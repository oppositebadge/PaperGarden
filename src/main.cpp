#include "Game.hpp"
#include "Constants.hpp"
#include "Globals.hpp"

#include <iostream>
#include <memory>
#include <raylib.h>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void); // main loop func
bool Init();
void Deinit();
void SetWorkingDirectoryToLocal();

std::unique_ptr<Game> game = nullptr;

int main(){
    if (!Init()){
        std::cerr << "Init failed";
        return EXIT_FAILURE;
    }

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose())
        {
            UpdateDrawFrame();
        }
    #endif

    Deinit();
    CloseWindow();

    return EXIT_SUCCESS;
}

void UpdateDrawFrame(void){

    Globals::pixel_render->Update();

    game->Update();
    Globals::pixel_render->BeginDraw();
    game->Draw();
    Globals::pixel_render->EndDraw();

    BeginDrawing();
        ClearBackground(BLACK);
        Globals::pixel_render->DrawResult();
    EndDrawing();
}

bool Init(){
    InitWindow(AppConstants::ScreenWidth, AppConstants::ScreenHeight, AppConstants::WindowTitle.c_str());
    //SetWindowState(FLAG_WINDOW_RESIZABLE);

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);

    if (!IsWindowReady()){
        std::cerr << "Failed to initialize raylib window";
        return false;
    }

    SetWorkingDirectoryToLocal();

    // init render buffer
    Globals::pixel_render->SetResolutions(
        AppConstants::RenderWidth,
        AppConstants::RenderHeight,
        GetScreenWidth(),
        GetScreenHeight()
    );

    Globals::LoadTextures();

    game = std::make_unique<Game>();

    return true;
}

void Deinit(){
    Globals::pixel_render->Unload();
    Globals::UnloadTextures();
    CloseAudioDevice();
}

void SetWorkingDirectoryToLocal(){
    ChangeDirectory(GetApplicationDirectory());
}