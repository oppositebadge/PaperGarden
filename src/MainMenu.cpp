#include "MainMenu.hpp"
#include <raymath.h>
#include <string>
#include "Constants.hpp"
#include "Globals.hpp"
#include <raylib.h>

MainMenu::MainMenu(
    Vector2 center,
    Texture2D background,
    const std::string& title,
    const std::string& play_text,
    const std::string& exit_text,
    const std::string& view_unlocks_text,
    bool show_play,
    bool show_view_unlocks) :
    
    main_menu_center(center),
    title_text(title),
    play_button_text(play_text),
    exit_button_text(exit_text),
    view_unlocks_button_text(view_unlocks_text),
    background(background),
    play_button(
        Rectangle{
            center.x - 120,
            center.y,
            240,
            60
        },
        Globals::pico_green,         // Default color
        Globals::pico_green_dark,   // Hover color
        Globals::pico_green_dark,    // Pressed color
        1.0f, false, 5, true
    ),
    exit_button(
        Rectangle{
            center.x - 120,
            center.y + play_button.GetBounds().height + 40,  // 40px gap after play button
            240,
            60
        },
        Globals::pico_red,          // Default color
        Globals::pico_pink,    // Hover color
        Globals::pico_red,     // Pressed color
        1.0f, false, 5, true
    ),
    view_unlocks_button(
        Rectangle{
            center.x - 120,
            center.y + (play_button.GetBounds().height + 40) * 2,  // Double the offset of exit button
            240,
            60
        },
        Globals::pico_blue_dark,         // Default color
        Globals::pico_blue,   // Hover color
        Globals::pico_blue_dark,    // Pressed color
        1.0f, false, 5, true
    ),
    show_play(show_play),
    show_view_unlocks(show_view_unlocks)
{
    play_button.BindOnPressed(std::bind(&MainMenu::OnPlayPressed, this));
    play_button.BindOnHovered(Globals::PlaySoundOnButtonHovered);

    exit_button.BindOnPressed(std::bind(&MainMenu::OnExitPressed, this));
    exit_button.BindOnHovered(Globals::PlaySoundOnButtonHovered);

    view_unlocks_button.BindOnPressed(std::bind(&MainMenu::OnViewUnlocksPressed, this));
    view_unlocks_button.BindOnHovered(Globals::PlaySoundOnButtonHovered);
}

MainMenu::~MainMenu() {
    // Remove this line since the texture is managed by Globals
    // UnloadTexture(background);
}

void MainMenu::Update() {
    if (show_play){
        play_button.Update(MOUSE_BUTTON_LEFT);
    }
    exit_button.Update(MOUSE_BUTTON_LEFT);
    if (show_view_unlocks) {
        view_unlocks_button.Update(MOUSE_BUTTON_LEFT);
    }
}

void MainMenu::Draw() {
    // Draw background image scaled to fill screen
    DrawTexturePro(
        background,
        Rectangle{0, 0, (float)background.width, (float)background.height},
        Rectangle{0, 0, AppConstants::RenderWidth, AppConstants::RenderHeight},
        Vector2{0, 0},
        0.0f,
        WHITE
    );

    // Draw title
    const int title_font_size = 60;
    Vector2 text_size = MeasureTextEx(Globals::fonts["pacifico"], title_text.c_str(), title_font_size, 1);
    DrawTextEx(
        Globals::fonts["pacifico"],
        title_text.c_str(),
        Vector2{main_menu_center.x - text_size.x/2, main_menu_center.y - 150},
        title_font_size,
        2,
        text_color
    );

    // Draw buttons
    if (show_play){
        play_button.Draw();
    }
    
    exit_button.Draw();
    if (show_view_unlocks) {
        view_unlocks_button.Draw();
    }

    const int button_font_size = 60;
    
    if (show_play){
        // Draw play text centered on play button
        Vector2 play_text_size = MeasureTextEx(Globals::fonts["pacifico"], play_button_text.c_str(), button_font_size, 1);
        DrawTextEx(
            Globals::fonts["pacifico"],
            play_button_text.c_str(),
            Vector2{
                play_button.GetBounds().x + play_button.GetBounds().width/2 - play_text_size.x/2,
                play_button.GetBounds().y + play_button.GetBounds().height/2 - play_text_size.y/2
            },
            button_font_size,
            1.f,
            Globals::pico_white
        );
    }

    // Draw exit text centered on exit button
    Vector2 exit_text_size = MeasureTextEx(Globals::fonts["pacifico"], exit_button_text.c_str(), button_font_size, 1);
    DrawTextEx(
        Globals::fonts["pacifico"],
        exit_button_text.c_str(),
        Vector2{
            exit_button.GetBounds().x + exit_button.GetBounds().width/2 - exit_text_size.x/2,
            exit_button.GetBounds().y + exit_button.GetBounds().height/2 - exit_text_size.y/2
        },
        button_font_size,
        1.f, 
        Globals::pico_white
    );
    
    // Draw view unlocks text if button is shown
    if (show_view_unlocks) {
        Vector2 view_unlocks_text_size = MeasureTextEx(Globals::fonts["pacifico"], view_unlocks_button_text.c_str(), button_font_size, 1);
        DrawTextEx(
            Globals::fonts["pacifico"],
            view_unlocks_button_text.c_str(),
            Vector2{
                view_unlocks_button.GetBounds().x + view_unlocks_button.GetBounds().width/2 - view_unlocks_text_size.x/2,
                view_unlocks_button.GetBounds().y + view_unlocks_button.GetBounds().height/2 - view_unlocks_text_size.y/2
            },
            button_font_size,
            1.f,
            Globals::pico_white
        );
    }
}

void MainMenu::OnPlayPressed() {
    if (on_play_callback) {
        on_play_callback();
    }
}

void MainMenu::OnExitPressed() {
    if (on_exit_callback) {
        on_exit_callback();
    }
}

void MainMenu::OnViewUnlocksPressed() {
    if (on_view_unlocks_callback) {
        on_view_unlocks_callback();
    }
}