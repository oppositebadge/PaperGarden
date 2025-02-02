#include "Sidebar.hpp"
#include "Constants.hpp"
#include "Globals.hpp"

#include <raylib.h>

Color GetPercentColor(int percent){
    if (percent >= 90) return GREEN;
    else if (percent >= 70) return YELLOW;
    else if (percent >= 50) return ORANGE;
    else return RED;
}

Sidebar::Sidebar() {

    pause_black_icon = Globals::textures["pause_black"];
    pause_white_icon = Globals::textures["pause_white"];

    pause_button = Button(
        Rectangle{0, 0, 60, 60},
        pause_black_icon,
        pause_white_icon,
        pause_black_icon,
        1.0f,             // SecShowPressed
        false,            // CheckboxVal
        true             // Active
    );

    width = AppConstants::SidebarWidth;
    height = AppConstants::SidebarHeight * 40.f/100;
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

    //std::cout << IsTextureValid(pause_black_icon) << std::endl;
}

void Sidebar::Update() {
    pause_button.Update();
}

void Sidebar::Draw(Texture2D reference) {
    // Draw sidebar contents
    int font_size = 40;
    //DrawText("Reference", reference_rect.x + reference_rect.width/2 - 100, reference_rect.y + reference_rect.height/2 - 10, font_size, BLACK);
    //DrawTextureV(reference, Globals::pixel_render->GetCameraCenter(), WHITE);
    DrawTexturePro(reference, Rectangle{0,0,1024,1024}, reference_rect, Vector2{0,0}, 0.f, WHITE);
    DrawRectangleRoundedLinesEx(reference_rect, 0.05f, 5, border_width, border_color);
    
    DrawRectangleRoundedLinesEx(controls_rect, 0.05f, 5, border_width, border_color);
    DrawText(TextFormat("Similarity: %i", accuracy_percentage), controls_rect.x + controls_rect.width/2 - 100, controls_rect.y + controls_rect.height/2 - 10, font_size, GetPercentColor(accuracy_percentage));

    pause_button.Draw();
}

void Sidebar::OnPausePressed() {
    if (on_pause_callback) {
        on_pause_callback();
    }
}