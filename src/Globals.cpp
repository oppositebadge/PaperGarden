#include "Globals.hpp"
#include "Achievements.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <string>

#define IMAGE_EXT ".png"
#define FONT_EXT ".ttf"
#define MUSIC_EXT ".wav"
#define SOUND_EXT ".wav"

void LoadMusicGlobal(std::string name){
    Globals::music_map[name] = LoadMusicStream( AppConstants::GetMusicPath(name + MUSIC_EXT).c_str() );
}

void LoadTextureGlobal(std::string name){
    Globals::textures[name] = LoadTexture( AppConstants::GetAssetPath(name+IMAGE_EXT).c_str() );
}

void LoadSoundGlobal(std::string name){
    Globals::sounds[name] = SoundMulti{};
    Globals::sounds[name].Load( AppConstants::GetSoundAssetPath(name+SOUND_EXT).c_str() );
}

void LoadFontGlobal(std::string name){
    Globals::fonts[name] = LoadFontEx(AppConstants::GetFontAssetPath(name+FONT_EXT).c_str(), 60, NULL, 0);
}

namespace Globals {
    std::shared_ptr<PixelPerfect> pixel_render = std::make_shared<PixelPerfect>();
    std::unordered_map<std::string, Texture2D> textures = {};
    std::unordered_map<std::string, Model> models = {};
    std::unordered_map<std::string, Shader> shaders = {};

    std::unordered_map<std::string, SoundMulti> sounds = {};
    std::unordered_map<std::string, Music> music_map = {};
    std::string current_music = "";
    bool music_playing = true;

    std::unordered_map<int, Achievement> Achievements = {};
    std::set<int> unlockedAchievements = {};
    std::unordered_map<std::string, Font> fonts = {};
    
    int FirstMissingAchievemntId(){
        int expected = 0;
        for (int achieved : unlockedAchievements) {
            if (achieved != expected) {
                return expected;  // Found the first missing key
            }
            expected++;
        }
        if (Achievements.find(expected) != Achievements.end()){
            return expected;
        }
        else return -1;
    }

    Achievement FirstMissingAchievemnt(){
        int id = FirstMissingAchievemntId();
        if (id >= 0){
            return Achievements[id];
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
                    {1172.67, 839.666},
                    {1332.67, 679.666},
                    {1012.67, 679.666},
                    {854, 680},
                    {1174, 680},
                    {1014, 520},
                    {1014, 839},
                    {1094, 759},
                    {1014, 679},
                    {1173, 680},
                    {1333, 680},
                    {1253, 600},
                    {1173, 680},
                    {1253, 600},
                    {1093, 600},
                    {1014.67, 836},
                    {1014.67, 676},
                    {854.667, 676},
                    {1095, 916},
                    {1175, 836},
                    {1095, 756},
                    {1015, 836},
                    {1095, 916},
                    {1095, 756},
                    {1095, 602.333},
                    {1255, 602.333},
                    {1175, 522.333},
            },
            "clue_1"
        };
    
        Achievements[2] = Achievement{{
                {911, 680},
                {1071, 840},
                {1071, 520},
                {911.667, 1000.67},
                {1071.67, 840.667},
                {911.667, 680.667},
                {764.667, 518.667},
                {924.667, 518.667},
                {844.667, 438.667},
                {925, 524},
                {1085, 524},
                {1005, 444},
                {925, 524},
                {1005, 444},
                {845, 444},
                {911, 683},
                {1071, 523},
                {911, 523},
                {918.431, 444.569},
                {1031.57, 444.569},
                {1031.57, 331.431},
                {918.431, 444.569},
                {1031.57, 331.431},
                {918.431, 331.431},
                {1086, 525},
                {1166, 445},
                {1006, 445},
        },
            "clue_2"
        };
    }

    void LoadSounds(){
        //LoadSoundGlobal(sound);
        Globals::sounds["low7"] = SoundMulti{};
        Globals::sounds["low7"].Load( AppConstants::GetSoundAssetPath(std::string("Short - Low/Classic UI SFX - Short - Low #7")+SOUND_EXT).c_str() );
    }

    void UnloadSounds(){
        for (auto key_sound : sounds){
            key_sound.second.Unload();
        }
    }

    void LoadMusic(){
        LoadMusicGlobal("lofi");
        SetMusicVolume(music_map["lofi"], 0.1);
        
        LoadMusicGlobal("alex-productions-breakfast-in-paris");
        SetMusicVolume(music_map["alex-productions-breakfast-in-paris"], 0.7);

        LoadMusicGlobal("japanese");
        LoadMusicGlobal("garden_theme");

        current_music = "alex-productions-breakfast-in-paris";
        PlayMusicStream(music_map[current_music]);
    }

    void UnloadMusic(){
        UnloadMusicStream(music_map[current_music]);
    }

    void UnlockAchievement(int id){
        unlockedAchievements.insert(id);
    }
    
    void LoadTextures(){
        // textures["name"] = LoadTexture(AppConstants::GetAssetPath("name.png"))
        // then to use: Globals::textures["name"]
        LoadTextureGlobal("pause_black");
        LoadTextureGlobal("pause_white");
        LoadTextureGlobal("main_menu_background");
        LoadTextureGlobal("game_background");

        LoadTextureGlobal("reference_0");

        LoadTextureGlobal("clue_0");
        LoadTextureGlobal("clue_1");
        LoadTextureGlobal("clue_2");
        LoadTextureGlobal("leaf_outline");
    }

    void LoadFonts(){
        fonts["pacifico"] = LoadFontEx(AppConstants::GetFontAssetPath("Pacifico-Regular.ttf").c_str(), 60, NULL, 0);
        fonts["vampire_kiss"] = LoadFontEx(AppConstants::GetFontAssetPath("vampire-kiss/Vampire Kiss Demo.ttf").c_str(), 60, NULL, 0);
        fonts["poppins"] = LoadFontEx(AppConstants::GetFontAssetPath("Poppins/Poppins-Regular.ttf").c_str(), 60, NULL, 0);
    }

    void LoadModels(){
        models["garden"] = LoadModel(AppConstants::GetAssetPath("low_poly_garden/scene.gltf").c_str());
    }

    void LoadShaders(){
        // Shader shader = LoadShader(0, AppConstants::GetShaderAssetPath("raymarching.fs").c_str());
        // shaders["raymarching"] = shader;
        // // Get shader locations for required uniforms
        // int viewEyeLoc = GetShaderLocation(shader, "viewEye");
        // int viewCenterLoc = GetShaderLocation(shader, "viewCenter");
        // int runTimeLoc = GetShaderLocation(shader, "runTime");
        // int resolutionLoc = GetShaderLocation(shader, "resolution");

        // std::cout << "\nviewEyeLoc " << viewEyeLoc;
        // std::cout << "\nviewCenterLoc " << viewCenterLoc;
        // std::cout << "\nrunTimeLoc " << runTimeLoc;
        // std::cout << "\nresolutionLoc " << resolutionLoc;

        // float resolution[2] = { AppConstants::RenderWidth, AppConstants::RenderHeight };
        // SetShaderValue(shader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    }

    void UnloadFonts(){
        for(auto key_font : fonts){
            UnloadFont(key_font.second);
        }
    }

    void UnloadModels(){
        for(auto key_model : models){
            UnloadModel(key_model.second);
        }
    }

    void UnloadTextures(){
        for(auto key_texture : textures){
            UnloadTexture(key_texture.second);
        }
    }

    void UnloadShaders(){
        for(auto key_shader : shaders){
            UnloadShader(key_shader.second);
        }
    }

    void PlaySound(const char* name){
        sounds[name].Play();
    }

    void MusicUpdate(){
        UpdateMusicStream(music_map[current_music]);
    }

    void MusicStop(){
        StopMusicStream(music_map[current_music]);
    }

    void MusicResume(){
        if (music_playing) ResumeMusicStream(music_map[current_music]);
    }

    void MusicPlayFromBeginning(){
        if (music_playing) {
            SeekMusicStream(music_map[current_music], 0.0f);
            PlayMusicStream(music_map[current_music]);
        }
    }

    bool IsCurrentMusicPlaying(){
        return IsMusicStreamPlaying(music_map[current_music]);
    }

    void PlaySoundOnButtonHovered(){
        PlaySound("low7");
    }
}