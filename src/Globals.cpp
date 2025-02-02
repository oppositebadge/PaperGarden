#include "Globals.hpp"
#include "Achievements.hpp"
#include "Constants.hpp"

namespace Globals {
    std::shared_ptr<PixelPerfect> pixel_render = std::make_shared<PixelPerfect>();
    std::unordered_map<std::string, Texture2D> textures = {};
    
    std::unordered_map<int, Achievement> Achievements = {};
    std::set<int> unlockedAchievements = {};
    
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
                {989.242, 921.849},
                {1215.52, 695.575},
                {989.242, 695.575},
                {991.425, 922.516},
                {991.425, 696.242},
                {765.151, 696.242},
                {833.667, 540.667},
                {993.667, 540.667},
                {913.667, 460.667},
                {989, 541},
                {1069, 621},
                {1069, 461},
                {989, 701},
                {1069, 621},
                {989, 541},
                {987.667, 697},
                {987.667, 537},
                {827.667, 537},
                {990, 540},
                {1070, 460},
                {990, 380},
                {910, 460},
                {990, 540},
                {990, 380},
                {1070.33, 622.667},
                {1150.33, 542.667},
                {1070.33, 462.667},
            },
            "reference_0.png"
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
            "reference_1.png"
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
            "reference_2.png"
        };
    }

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