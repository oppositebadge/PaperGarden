#pragma once
#include <functional>
#include <raylib.h>

class Button{
    private:
        Rectangle button_rect;
        Texture2D texture_default;
        Texture2D texture_hovered;
        Texture2D texture_pressed;

        Color color_default;
        Color color_hovered;
        Color color_pressed;


        float sec_since_pressed = -1;
        float sec_show_pressed;
        float thickness = 10;

        bool use_colors = false;
        bool checkbox_value;
        bool active = true;
        bool down = false;
        bool hovered = false;
    
        std::function<void()> on_pressed = 0;
        std::function<void()> on_released = 0;
        std::function<void()> on_hovered = 0;

    public:
        Button() {}
        Button(Rectangle ButtonRect, Texture2D TextureDefault, Texture2D TextureHovered, Texture2D TexturePressed, float SecShowPressed, bool CheckboxVal, bool Active = true);
        Button(Rectangle ButtonRect, Color ColorDefault, Color ColorHovered, Color ColorPressed, float SecShowPressed, bool CheckboxVal, float Thickness = 10, bool Active = true);

        void UpdateV(Vector2 MousePos, int MouseButton = 0);
        void Update(int MouseButton = 0);

        void Draw();

        void BindOnPressed(void (*func)());
        void BindOnReleased(void (*func)());
        void BindOnHovered(void (*func)());

        void BindOnPressed(std::function<void()> func);
        void BindOnReleased(std::function<void()> func);
        void BindOnHovered(std::function<void()> func);

        bool IsDown();
        bool IsActive();

        void SetActive(bool Active);
        void ToggleActive();

        Rectangle GetBounds() const { return button_rect; }

        void SetPosition(float x, float y) { button_rect.x = x; button_rect.y = y; }
        float GetWidth() const { return button_rect.width; }
};