#include "Globals.hpp"
//#include "Constants.hpp" will be needed later

namespace Globals {
    std::shared_ptr<PixelPerfect> pixel_render = std::make_shared<PixelPerfect>();
    std::unordered_map<std::string, Texture2D> textures = {};

    void LoadTextures(){
        // textures["name"] = LoadTexture(AppConstants::GetAssetPath("name.png"))
        // then to use: Globals::textures["name"]
    }

    void UnloadTextures(){
        for(auto key_texture : textures){
            UnloadTexture(key_texture.second);
        }
    }
}