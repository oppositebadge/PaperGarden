#include "Game.hpp"
#include "Constants.hpp"
#include "Globals.hpp"

#include <iostream>
#include <memory>
#include <raylib.h>

#define GLSL_VERSION            330

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
        while (!WindowShouldClose() && game && !game->ShouldClose())
        {
            UpdateDrawFrame();
        }
    #endif

    Deinit();
    CloseWindow();

    return EXIT_SUCCESS;
}

void UpdateDrawFrame(void){

    Globals::MusicUpdate();

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
    // Initialize window first
    InitWindow(AppConstants::ScreenWidth, AppConstants::ScreenHeight, AppConstants::WindowTitle.c_str());
    
    if (!IsWindowReady()) {
        std::cerr << "Failed to initialize raylib window";
        return false;
    }

    InitAudioDevice();
    SetAudioStreamBufferSizeDefault(4096);

    SetExitKey(KEY_NULL);  // Disable default ESC key exit behavior

    // Initialize render buffer
    Globals::pixel_render->SetResolutions(
        AppConstants::RenderWidth,
        AppConstants::RenderHeight,
        GetScreenWidth(),
        GetScreenHeight()
    );

    // Load textures before creating game instance
    Globals::LoadMusic();
    Globals::LoadSounds();
    
    Globals::LoadTextures();
    Globals::LoadModels();
    Globals::LoadShaders();
    
    Globals::LoadFonts();
    
    Globals::SetupAchievements();

    // Create game instance after window and textures are ready
    game = std::make_unique<Game>();

    return true;
}

void Deinit(){

    Globals::UnloadMusic();
    Globals::UnloadSounds();

    Globals::pixel_render->Unload();
    Globals::UnloadFonts();

    Globals::UnloadShaders();

    Globals::UnloadModels();
    Globals::UnloadTextures();
    CloseAudioDevice();
}

void SetWorkingDirectoryToLocal(){
    ChangeDirectory(GetApplicationDirectory());
}