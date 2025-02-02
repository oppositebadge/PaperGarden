#include "Globals.hpp"
#include "Achievements.hpp"
#include "Constants.hpp"

namespace Globals {
    std::shared_ptr<PixelPerfect> pixel_render = std::make_shared<PixelPerfect>();
    std::unordered_map<std::string, Texture2D> textures = {};
    
    std::unordered_map<int, Achievement> Achievements = {};
    std::set<int> unlockedAchievements = {};
    std::unordered_map<std::string, Font> fonts = {};
    
    Achievement FirstMissingAchievemnt(){
        int expected = 0;
        for (int achieved : unlockedAchievements) {
            if (achieved != expected) {
                return Achievements[expected];  // Found the first missing key
            }
            expected++;
        }
        if (Achievements.find(expected) != Achievements.end()){
            return Achievements[expected];  // If no gaps, return the next number in sequence
        }
        else {
            return Achievement{
                {}, "",
                true // final achievement
            };
        }   
    }

    void SetupAchievements(){
        Achievements[0] = Achievement{{
                    {1009.24, 909.849},
                    {1235.52, 683.575},
                    {1009.24, 683.575},
                    {1009.42, 910.516},
                    {1009.42, 684.242},
                    {783.151, 684.242},
                    {851.667, 528.667},
                    {1011.67, 528.667},
                    {931.667, 448.667},
                    {1010, 528},
                    {1090, 608},
                    {1090, 448},
                    {1010, 688},
                    {1090, 608},
                    {1010, 528},
                    {1010.67, 687},
                    {1010.67, 527},
                    {850.667, 527},
                    {1011, 530},
                    {1091, 450},
                    {1011, 370},
                    {931, 450},
                    {1011, 530},
                    {1011, 370},
                    {1089.33, 608.667},
                    {1169.33, 528.667},
                    {1089.33, 448.667},
            },
            "clue_0"
        };

        Achievements[1] = Achievement{{
                {1134.09, 857.849},
                {1134.09, 631.575},
                {907.817, 631.575},
                {907.575, 857.091},
                {1133.85, 857.091},
                {907.575, 630.817},
                {1218.67, 842.333},
                {1298.67, 762.333},
                {1138.67, 762.333},
                {907.569, 793.137},
                {907.569, 680},
                {794.432, 680},
                {794.432, 680},
                {907.569, 680},
                {794.432, 566.863},
                {909.197, 632.046},
                {1135.47, 632.046},
                {1022.33, 518.909},
                {1159.43, 759.569},
                {1272.57, 759.569},
                {1272.57, 646.431},
                {1159.43, 759.569},
                {1272.57, 646.431},
                {1159.43, 646.431},
                {1135, 650.333},
                {1295, 650.333},
                {1215, 570.333},
            },
            "reference_1"
        };
    
        Achievements[2] = Achievement{{
                {758.667, 717.333},
                {1078.67, 717.333},
                {918.667, 557.333},
                {1075, 879.333},
                {1235, 719.333},
                {915, 719.334},
                {999.667, 639.667},
                {1159.67, 639.667},
                {1079.67, 559.667},
                {1080, 719},
                {1160, 639},
                {1000, 639},
                {1080, 719},
                {1240, 719},
                {1160, 639},
                {913.667, 876},
                {913.667, 716},
                {753.667, 716},
                {995, 958},
                {1075, 878},
                {915, 878},
                {915, 878},
                {1075, 878},
                {995, 798},
                {915.333, 877.667},
                {995.333, 797.667},
                {915.333, 717.667},
        },
            "reference_2"
        };
    }

    void UnlockAchievement(int id){
        unlockedAchievements.insert(id);
    }

    void LoadTextures(){
        // textures["name"] = LoadTexture(AppConstants::GetAssetPath("name.png"))
        // then to use: Globals::textures["name"]
        textures["image"] = LoadTexture(AppConstants::GetAssetPath("image.png").c_str());
        textures["pause_black"] = LoadTexture(AppConstants::GetAssetPath("pause_black.png").c_str());
        textures["pause_white"] = LoadTexture(AppConstants::GetAssetPath("pause_white.png").c_str()); 
        textures["main_menu_background"] = LoadTexture(AppConstants::GetAssetPath("Paper_Garden.png").c_str());

        textures["reference_0"] = LoadTexture(AppConstants::GetAssetPath("reference_0.png").c_str());
        textures["clue_0"] = LoadTexture(AppConstants::GetAssetPath("clue_0.png").c_str());
    }

    void LoadFonts(){
        fonts["pacifico"] = LoadFontEx(AppConstants::GetAssetPath("Pacifico-Regular.ttf").c_str(), 60, NULL, 0);
    }

    void UnloadTextures(){
        for(auto key_texture : textures){
            UnloadTexture(key_texture.second);
        }
    }

    void UnloadFonts(){
        for(auto key_font : fonts){
            UnloadFont(key_font.second);
        }
    }
}