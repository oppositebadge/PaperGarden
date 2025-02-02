#pragma once

#include <raylib.h>
#include "Button.hpp"
#include <functional>

class Sidebar {
    public:
        Sidebar();
        void Update();
        void Draw();
        void SetOnPauseCallback(std::function<void()> callback) { on_pause_callback = callback; }

    private:
        float width;
        float height;
        float x;
        float y;
        float margin;
        int border_width;
        Color border_color;
        Rectangle reference_rect;
        Rectangle controls_rect;
        Button pause_button;
        Texture2D pause_black_icon;
        Texture2D pause_white_icon;
        std::function<void()> on_pause_callback;
        void OnPausePressed();
};