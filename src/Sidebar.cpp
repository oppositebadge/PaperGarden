#include "Sidebar.hpp"
#include "Constants.hpp"
#include <iostream>  // for std::cout
#include <raylib.h>  // for IsTextureReady()
#include "Globals.hpp"

Sidebar::Sidebar() :
    pause_black_icon(Globals::textures["pause_black"]),
    pause_white_icon(Globals::textures["pause_white"]),
    pause_button(
        Rectangle{0, 0, 60, 60},
        pause_black_icon,
        pause_white_icon,
        pause_black_icon,
        1.0f,             // SecShowPressed
        false,            // CheckboxVal
        true             // Active
    ) {
    

    width = AppConstants::SidebarWidth;
    height = AppConstants::SidebarHeight * 40/100;
    margin = 10;
    x = 0 + margin;
    y = 0 + margin;
    border_width = 2;
    border_color = BLACK;
    reference_rect = {x, y, width, height};
    controls_rect = {x, y + height + (2*margin), width, height};
    pause_button.BindOnPressed(std::bind(&Sidebar::OnPausePressed, this));
    pause_button.SetPosition(
        controls_rect.x + controls_rect.width - 70,  // 10px margin from right
        controls_rect.y + controls_rect.height - 70  // 10px margin from bottom
    );

    std::cout << IsTextureValid(pause_black_icon) << std::endl;
}

void Sidebar::Update() {
    pause_button.Update();
}

void Sidebar::Draw() {
    // Draw sidebar contents
    DrawRectangleRoundedLinesEx(reference_rect, 0.05f, 5, border_width, border_color);
    DrawText("Reference", reference_rect.x + reference_rect.width/2 - 50, reference_rect.y + reference_rect.height/2 - 10, 20, BLACK);
    DrawRectangleRoundedLinesEx(controls_rect, 0.05f, 5, border_width, border_color);
    DrawText("Time", controls_rect.x + controls_rect.width/2 - 50, controls_rect.y + controls_rect.height/2 - 10, 20, BLACK);
    pause_button.Draw();
}

void Sidebar::OnPausePressed() {
    if (on_pause_callback) {
        on_pause_callback();
    }
}