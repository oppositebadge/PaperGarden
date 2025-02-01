#pragma once
#include <string>
#include "Button.hpp"
#include <raylib.h>
#include <functional>

class MainMenu {
    private:
        Vector2 main_menu_center;
        Rectangle main_menu_rect;
        const int font_size = 60;
        const Color text_color = BLACK;
        Button play_button;
        Button exit_button;
        std::function<void()> on_play_callback = nullptr;
        std::function<void()> on_exit_callback = nullptr;
        std::string title_text;
        std::string play_button_text;
        std::string exit_button_text;

    public:
        MainMenu(Vector2 center, const std::string& title = "Paper Garden", const std::string& play_text = "Play", const std::string& exit_text = "Exit");
        void Update();
        void Draw();
        void OnPlayPressed();
        void OnExitPressed();
        void SetOnPlayCallback(std::function<void()> callback) {
            on_play_callback = callback;
        }
        void SetOnExitCallback(std::function<void()> callback) {
            on_exit_callback = callback;
        }
        // static void UpdateCounter();
};