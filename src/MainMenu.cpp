#include "MainMenu.hpp"
#include <raymath.h>
#include <string>
#include "Globals.hpp"
#include <raylib.h>

MainMenu::MainMenu(Vector2 center, const std::string& title, const std::string& play_text, const std::string& exit_text) : 
    main_menu_center(center),
    title_text(title),
    play_button_text(play_text),
    exit_button_text(exit_text),
    background(Globals::textures["main_menu_background"]),
    play_button(
        Rectangle{
            center.x - 120,
            center.y,
            240,
            60
        },
        Color{34, 139, 34, 255},
        Color{50, 205, 50, 255},
        Color{0, 100, 0, 255},
        1.0f, false, 10, true
    ),
    exit_button(
        Rectangle{
            center.x - 120,
            center.y + 100,
            240,
            60
        },
        Color{139, 0, 0, 255},
        Color{205, 92, 92, 255},
        Color{100, 0, 0, 255},
        1.0f, false, 10, true
    )
{
    play_button.BindOnPressed(std::bind(&MainMenu::OnPlayPressed, this));
    exit_button.BindOnPressed(std::bind(&MainMenu::OnExitPressed, this));
}

MainMenu::~MainMenu() {
    // Remove this line since the texture is managed by Globals
    // UnloadTexture(background);
}

void MainMenu::Update() {
    play_button.Update(MOUSE_BUTTON_LEFT);
    exit_button.Update(MOUSE_BUTTON_LEFT);
}

void MainMenu::Draw() {
    // Draw background image scaled to fill screen
    DrawTexturePro(
        background,
        Rectangle{0, 0, (float)background.width, (float)background.height},
        Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
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
        Vector2{main_menu_center.x - text_size.x/2 - 100, main_menu_center.y - 150},
        title_font_size,
        2,
        text_color
    );

    // Draw buttons
    play_button.Draw();
    exit_button.Draw();

    // Draw button texts
    const int button_font_size = 30;
    
    // Draw play text
    Vector2 play_text_size = MeasureTextEx(GetFontDefault(), play_button_text.c_str(), button_font_size, 1);
    DrawText(
        play_button_text.c_str(),
        main_menu_center.x - play_text_size.x/2,
        main_menu_center.y + 60.f/2 - play_text_size.y/2,
        button_font_size,
        WHITE
    );

    // Draw exit text with custom text
    Vector2 exit_text_size = MeasureTextEx(GetFontDefault(), exit_button_text.c_str(), button_font_size, 1);
    DrawText(
        exit_button_text.c_str(),
        main_menu_center.x - exit_text_size.x/2,
        main_menu_center.y + 100 + 60.f/2 - exit_text_size.y/2,
        button_font_size,
        WHITE
    );
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