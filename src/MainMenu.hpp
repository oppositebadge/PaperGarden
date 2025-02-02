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
        Button view_unlocks_button;
        std::function<void()> on_play_callback = nullptr;
        std::function<void()> on_exit_callback = nullptr;
        std::function<void()> on_view_unlocks_callback = nullptr;
        std::string title_text;
        std::string play_button_text;
        std::string exit_button_text;
        std::string view_unlocks_button_text;
        Texture2D background;
        bool show_play = false;
        bool show_view_unlocks = false;

    public:
        MainMenu(
            Vector2 center, 
            Texture2D background,
            const std::string& title = "Paper Garden", 
            const std::string& play_text = "Play", 
            const std::string& exit_text = "Exit",
            const std::string& view_unlocks_text = "View Unlocks",
            bool show_play = false,
            bool show_view_unlocks = false
        );
        
        ~MainMenu();
        void Update();
        void Draw();
        void OnPlayPressed();
        void OnExitPressed();
        void OnViewUnlocksPressed();
        void SetOnPlayCallback(std::function<void()> callback) {
            on_play_callback = callback;
        }
        void SetOnExitCallback(std::function<void()> callback) {
            on_exit_callback = callback;
        }
        void SetOnViewUnlocksCallback(std::function<void()> callback) {
            on_view_unlocks_callback = callback;
        }
        // static void UpdateCounter();
};