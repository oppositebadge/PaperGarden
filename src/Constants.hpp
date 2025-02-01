#pragma once

#include <raylib.h>
#include <string>

namespace AppConstants
{
    const std::string WindowTitle = "Paper garden";
    const std::string GameName = "Paper Garden";
    const std::string assets_path = "assets/";
    const std::string sounds_path = assets_path + "sounds/";
    const std::string music_path = sounds_path + "music/";

    // Virtual resolution for consistent rendering
    const int RenderWidth = 1920;
    const int RenderHeight = 1080;

    // UI Constants that scale with screen size
    inline float GetUIScale() {
        return static_cast<float>(GetScreenHeight()) / 1080.0f;
    }

    inline float GetPauseButtonSize() {
        return 40.0f * GetUIScale();
    }

    inline float GetPauseButtonMargin() {
        return 20.0f * GetUIScale();
    }

    const int RenderScale = 1;

    // default screen size
    const int ScreenWidth = RenderWidth*RenderScale;
    const int ScreenHeight = RenderHeight*RenderScale;

    // when loading an asset, do LoadTexture(AppConstants::GetAssetPath(bare_name.png))
    inline std::string GetAssetPath(std::string assetName)
    {
        return assets_path + assetName;
    }
    
    inline std::string GetSoundAssetPath(std::string assetName)
    {
        return sounds_path + assetName;
    }

    inline std::string GetMusicPath(std::string assetName)
    {
        return music_path + assetName;
    }

}