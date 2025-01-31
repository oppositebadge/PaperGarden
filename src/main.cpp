#include "Constants.hpp"
#include "Globals.hpp"

#include <iostream>
#include <raylib.h>

#ifdef PLATFORM_WEB
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void); // main loop func
bool Init();
void Deinit();
void SetWorkingDirectoryToLocal();

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

    // something like game->Update()
    Globals::pixel_render->BeginDraw();
    // something like game->Draw()

    // for example
        DrawTexturePro(Globals::textures["image"],
        Rectangle{0,0,64,64},
        Rectangle{Globals::pixel_render->GetCameraCenter().x, Globals::pixel_render->GetCameraCenter().y, 500,500},
        Vector2{0,0}, 0, WHITE);

    Globals::pixel_render->EndDraw();

    BeginDrawing();
        ClearBackground(WHITE);
        Globals::pixel_render->DrawResult();
    EndDrawing();
}

bool Init(){
    InitWindow(AppConstants::ScreenWidth, AppConstants::ScreenHeight, AppConstants::WindowTitle.c_str());
    SetWindowState(FLAG_WINDOW_RESIZABLE);

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