#include "Globals.hpp"
#include "Constants.hpp"

namespace Globals {
    std::shared_ptr<PixelPerfect> pixel_render = std::make_shared<PixelPerfect>();
    std::unordered_map<std::string, Texture2D> textures = {};

    void LoadTextures(){
        // textures["name"] = LoadTexture(AppConstants::GetAssetPath("name.png"))
        // then to use: Globals::textures["name"]
        textures["image"] = LoadTexture(AppConstants::GetAssetPath("image.png").c_str());
    }

    void UnloadTextures(){
        for(auto key_texture : textures){
            UnloadTexture(key_texture.second);
        }
    }
}