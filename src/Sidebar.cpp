#include "Sidebar.hpp"
#include "Constants.hpp"
#include "Globals.hpp"

#include <raylib.h>
#include <cmath>  // Add this for fmin

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

    submit_button = Button(
        Rectangle{0, 0, 80, 40},  // Make button slightly smaller
        Color{34, 139, 34, 255},
        Color{50, 205, 50, 255},
        Color{0, 100, 0, 255},
        1.0f, false, 10, true
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
        controls_rect.x + controls_rect.width - 70,
        controls_rect.y + controls_rect.height - 60
    );

    submit_button.BindOnPressed(std::bind(&Sidebar::OnSubmitPressed, this));
    submit_button.SetPosition(
        controls_rect.x + controls_rect.width - 170,  // Move further left from pause button
        controls_rect.y + controls_rect.height - 60   // Align with pause button vertically
    );

    //std::cout << IsTextureValid(pause_black_icon) << std::endl;
}

void Sidebar::Update() {
    pause_button.Update();
    if (accuracy_percentage >= minimum_accuracy){
        submit_button.Update(MOUSE_BUTTON_LEFT);
    }
}

void Sidebar::Draw(Texture2D reference) {
    // Draw sidebar contents
    int font_size = 80;
    //DrawText("Reference", reference_rect.x + reference_rect.width/2 - 100, reference_rect.y + reference_rect.height/2 - 10, font_size, BLACK);
    //DrawTextureV(reference, Globals::pixel_render->GetCameraCenter(), WHITE);
    DrawTexturePro(reference, Rectangle{0,0,1024,1024}, reference_rect, Vector2{0,0}, 0.f, WHITE);
    DrawRectangleRoundedLinesEx(reference_rect, 0.05f, 5, border_width, border_color);
    
    DrawRectangleRoundedLinesEx(controls_rect, 0.05f, 5, border_width, border_color);
    DrawTextPro(
        Globals::fonts["pacifico"],
        TextFormat("Similarity: %i", accuracy_percentage),
        Vector2{controls_rect.x + controls_rect.width/2 - 100, controls_rect.y + controls_rect.height/2 - 10},
        Vector2{0,0},
        0.f,
        font_size,
        1.0f,
        GetPercentColor(accuracy_percentage)
        );

    pause_button.Draw();
    
    if (accuracy_percentage >= minimum_accuracy){
        submit_button.Draw();
        // Draw submit text
        const char* submit_text = "Submit";
        Vector2 text_size = MeasureTextEx(GetFontDefault(), submit_text, 20, 1);
        DrawText(
            submit_text,
            submit_button.GetBounds().x + (submit_button.GetBounds().width - text_size.x)/2,
            submit_button.GetBounds().y + (submit_button.GetBounds().height - text_size.y)/2,
            20,
            WHITE
        );
    }
}

void Sidebar::OnPausePressed() {
    if (on_pause_callback) {
        on_pause_callback();
    }
}

void Sidebar::OnSubmitPressed() {
    if (on_submit_callback) {
        on_submit_callback();
    }
}