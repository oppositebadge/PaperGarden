#pragma once

#include <raylib.h>
#include <string>

namespace AppConstants
{
    const std::string WindowTitle = "Paper garden";
    const std::string GameName = "Paper Garden";
    const std::string assets_path = "assets/";
    const std::string shaders_path = assets_path + "shaders/";
    const std::string sounds_path = assets_path + "sounds/";
    const std::string music_path = sounds_path + "music/";

    // Virtual resolution for consistent rendering
    const int RenderWidth = 1920;
    const int RenderHeight = 1080;

    const int RenderScale = 1;

    // default screen size
    const int ScreenWidth = RenderWidth*RenderScale;
    const int ScreenHeight = RenderHeight*RenderScale;

    const int SidebarWidth = ScreenWidth * 20/100;
    const int SidebarHeight = ScreenHeight;

    // when loading an asset, do LoadTexture(AppConstants::GetAssetPath(bare_name.png))
    inline std::string GetAssetPath(std::string assetName)
    {
        return assets_path + assetName;
    }
    
    // when loading an asset, do LoadTexture(AppConstants::GetAssetPath(bare_name.png))
    inline std::string GetShaderAssetPath(std::string assetName)
    {
        return shaders_path + assetName;
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