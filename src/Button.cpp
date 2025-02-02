#include "Button.hpp"
#include "raylib.h"

Button::Button(Rectangle ButtonRect, Texture2D TextureDefault, Texture2D TextureHovered, Texture2D TexturePressed, float SecShowPressed, bool CheckboxVal, bool Active){
    button_rect = ButtonRect;
    texture_default = TextureDefault;
    texture_hovered = TextureHovered;
    texture_pressed = TexturePressed;
    sec_show_pressed = SecShowPressed;
    checkbox_value = CheckboxVal;
    active = Active;

    use_colors = false;
}

Button::Button(Rectangle ButtonRect, Color ColorDefault, Color ColorHovered, Color ColorPressed, float SecShowPressed, bool CheckboxVal, float Thickness, bool Active){
    button_rect = ButtonRect;
    color_default = ColorDefault;
    color_hovered = ColorHovered;
    color_pressed = ColorPressed;
    sec_show_pressed = SecShowPressed;
    checkbox_value = CheckboxVal;
    active = Active;

    use_colors = true;
    thickness = Thickness;
}

void Button::UpdateV(Vector2 MousePos, int MouseButton){
    if (active && CheckCollisionPointRec(MousePos, button_rect)){

        hovered = true;

        if (IsMouseButtonPressed(MouseButton)){
            down = true;
            sec_since_pressed = 0;
            checkbox_value = !checkbox_value;

            if (on_pressed != 0) on_pressed();
        }

        if (IsMouseButtonReleased(MouseButton))
        {
            down = false;
            if (on_released != 0) on_released();
        }

    }
    else {
        hovered = false;
        down = false;
    }

    if (sec_since_pressed >= 0 && sec_since_pressed < sec_show_pressed)
    {
        sec_since_pressed += GetFrameTime();
    }
    if (sec_since_pressed >= sec_show_pressed){
        sec_since_pressed = -1;
    }
}

void Button::Update(int MouseButton){
    UpdateV(GetMousePosition(), MouseButton);
}


void Button::Draw(){
    Color color;
    Texture2D texture;

    if ( (sec_since_pressed >= 0 && sec_since_pressed <= sec_show_pressed) || down)
    {
        if (use_colors) color = color_pressed;
        else texture = texture_pressed;
    }
    else if (hovered)
    {
        if (use_colors) color = color_hovered;
        else texture = texture_hovered;
    }
    else {
        if (use_colors) color = color_default;
        else texture = texture_default;
    }

    Rectangle source = Rectangle{0, 0, float(texture.width), float(texture.height)};

    if (use_colors)
    {
        float roundness = 0.5f;
        int segments = 0;
        DrawRectangleRounded(button_rect, roundness, segments, color);
        DrawRectangleRoundedLinesEx(Rectangle{
            button_rect.x-thickness/2,
            button_rect.y-thickness/2,
            button_rect.width+thickness,
            button_rect.height+thickness
        }, roundness, segments, thickness, BLACK);
        //DrawRectangleRec(button_rect, color);
        //DrawRectangleLinesEx(button_rect, thickness, BLACK);
    }
    else {
        DrawTexturePro(texture, source, button_rect, Vector2{0,0}, 0, WHITE);
    }
    
}

void Button::BindOnPressed(void (*func)()){
    on_pressed = func;
}

void Button::BindOnReleased(void (*func)()){
    on_released = func;
}

void Button::BindOnPressed(std::function<void()> func) {
    on_pressed = func;
}

void Button::BindOnReleased(std::function<void()> func) {
    on_released = func;
}

bool Button::IsDown(){
    return down;
}

bool Button::IsActive(){
    return active;
}

void Button::SetActive(bool Active){
    active = Active;
}

void Button::ToggleActive(){
    active = !active;
}