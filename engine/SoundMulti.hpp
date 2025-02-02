#pragma once
#include <raylib.h>

#define ALIASES_PER_SOUND 10

struct SoundMulti{

    Sound aliases[ALIASES_PER_SOUND];

    void Load(const char* filename){
        aliases[0] = LoadSound(filename);
        for (int i = 1; i < ALIASES_PER_SOUND; i++){
            aliases[i] = LoadSoundAlias(aliases[0]);
        }
    }

    void Unload(){
        for (int i = 1; i < ALIASES_PER_SOUND; i++)
            UnloadSoundAlias(aliases[i]);
        UnloadSound(aliases[0]);
    }

    void Play(){
        for (int i = 0; i < ALIASES_PER_SOUND; i++){
            if (!IsSoundPlaying(aliases[i])) {
                PlaySound(aliases[i]);
                break;
            }
        }
    }
};