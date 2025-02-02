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
        Rectangle{0, 0, 80, 40},
        Globals::pico_green,      // Default color
        Globals::pico_green_dark,  // Hover color
        Globals::pico_green_dark,   // Pressed color
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
    
    float controls_height = height * 0.6f;
    controls_rect = {
        x, 
        y + height + margin,
        width, 
        controls_height
    };

    pause_button.BindOnHovered(Globals::PlaySoundOnButtonHovered);
    pause_button.BindOnPressed(std::bind(&Sidebar::OnPausePressed, this));
    // Center pause button horizontally and place it at bottom
    pause_button.SetPosition(
        controls_rect.x + (controls_rect.width - pause_button.GetWidth())/2,  // Center horizontally
        controls_rect.y + controls_rect.height - 60  // Near bottom
    );

    // Place submit button above pause button
    submit_button.SetPosition(
        controls_rect.x + (controls_rect.width - submit_button.GetWidth())/2,  // Center horizontally
        controls_rect.y + controls_rect.height - 120  // Above pause button
    );

    submit_button.BindOnHovered(Globals::PlaySoundOnButtonHovered);
    submit_button.BindOnPressed(std::bind(&Sidebar::OnSubmitPressed, this));

    //std::cout << IsTextureValid(pause_black_icon) << std::endl;
}

void Sidebar::Update() {
    pause_button.Update(MOUSE_BUTTON_LEFT);
    if (accuracy_percentage >= minimum_accuracy){
        submit_button.Update(MOUSE_BUTTON_LEFT);
    }
}

void Sidebar::Draw(Texture2D reference) {
    // Draw sidebar contents
    int font_size = 60;
    DrawTexturePro(reference, Rectangle{0,0,1024,1024}, reference_rect, Vector2{0,0}, 0.f, WHITE);
    
    // Move similarity text above submit button
    DrawTextPro(
        Globals::fonts["pacifico"],
        // pacifico font doesn't have % character
        TextFormat("Similarity: %i", accuracy_percentage),
        Vector2{
            controls_rect.x + controls_rect.width/2 - 160,
            controls_rect.y + controls_rect.height/2 - 80  // Moved up by adjusting y coordinate
        },
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

    // Move instruction text further down
    const char* line1 = "Recreate the reference";
    const char* line2 = "picture using tiles.";
    const char* line3 = "Click and drag to move,";
    const char* line4 = "press R to rotate the shapes";
    int instruction_font_size = 60;
    
    DrawTextEx(
        Globals::fonts["pacifico"],
        line1,
        Vector2{x + 10, controls_rect.y + controls_rect.height + 60},  // Increased y offset
        instruction_font_size,
        1,
        Globals::pico_blue_dark
    );
    DrawTextEx(
        Globals::fonts["pacifico"],
        line2,
        Vector2{x + 10, controls_rect.y + controls_rect.height + 90},  // Increased y offset
        instruction_font_size,
        1,
        Globals::pico_blue_dark
    );
    DrawTextEx(
        Globals::fonts["pacifico"],
        line3,
        Vector2{x + 10, controls_rect.y + controls_rect.height + 150},  // Increased y offset
        instruction_font_size,
        1,
        Globals::pico_blue_dark
    );
    DrawTextEx(
        Globals::fonts["pacifico"],
        line4,
        Vector2{x + 10, controls_rect.y + controls_rect.height + 190},  // Increased y offset
        instruction_font_size,
        1,
        Globals::pico_blue_dark
    );
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