#pragma once

#include "Button.hpp"
#include "Constants.hpp"
#include "Globals.hpp"
#include <raylib.h>

#define SECRETS_MAX_INPUT_CHARS     13

class SecretsMenu {

private:
    Texture2D background;

    char buffer[SECRETS_MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
    int letterCount = 0;
    Rectangle inputBox = { AppConstants::ScreenWidth/2.0f - 100, AppConstants::ScreenHeight/2.0f, 225, 50 };

    Button exit_button;

public:

    SecretsMenu(Vector2 center, Texture2D background) : background(background),
        exit_button(
            Rectangle{
                center.x - 120,
                center.y+300,
                240,
                60
            },
            Color{139, 0, 0, 255},
            Color{205, 92, 92, 255},
            Color{100, 0, 0, 255},
            1.0f, false, 5, true
        ) {

        exit_button.BindOnHovered(Globals::PlaySoundOnButtonHovered);
    }

    void SetOnExitCallback(std::function<void()> callback) { exit_button.BindOnPressed(callback); }

    void Update();
    void Draw();
};