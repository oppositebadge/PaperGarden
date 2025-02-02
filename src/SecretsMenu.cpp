#include "SecretsMenu.hpp"
#include "Globals.hpp"
#include <raylib.h>

void SecretsMenu::Update(){
    exit_button.Update(MOUSE_LEFT_BUTTON);

    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0)
    {
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < SECRETS_MAX_INPUT_CHARS))
        {
            buffer[letterCount] = (char)key;
            buffer[letterCount+1] = '\0'; // Add null terminator at the end of the string.
            letterCount++;
        }

        key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        buffer[letterCount] = '\0';
    }
}

void SecretsMenu::Draw(){

    DrawTexturePro(
        background,
        Rectangle{0, 0, (float)background.width, (float)background.height},
        Rectangle{0, 0, AppConstants::RenderWidth, AppConstants::RenderHeight},
        Vector2{0, 0},
        0.0f,
        WHITE
    );
    
    //DrawRectangleLinesEx(inputBox, 3, Globals::pico_black);
    float y_offset = 10.f;
    DrawLineV(
        Vector2{inputBox.x, inputBox.y + inputBox.height+y_offset},
        Vector2{inputBox.x + inputBox.width, inputBox.y + inputBox.height+y_offset},
        Globals::pico_black
    );

    DrawTextEx(Globals::fonts["pacifico"], buffer, Vector2{inputBox.x + 5, inputBox.y + 8}, 60, 1.f, Globals::pico_black);
    DrawTextEx(Globals::fonts["pacifico"], "If you guess the name of the shape, you will get a solution", Vector2{inputBox.x -180, inputBox.y + 380}, 60, 1.f, Globals::pico_black);

    int id = Globals::SecretId(buffer);
    if (id != -1){
        DrawTexture(Globals::textures[Globals::AchievementFromId(id).solution_image_name], 0, 0, WHITE);
        DrawTextEx(Globals::fonts["pacifico"], "Secret revealed!", Vector2{inputBox.x -100, inputBox.y + 100}, 60, 1.f, Globals::pico_green);
    }

    exit_button.Draw();
    std::string exit_button_text = "Main Menu";
    int button_font_size = 60;

    Vector2 exit_text_size = MeasureTextEx(Globals::fonts["pacifico"], exit_button_text.c_str(), button_font_size, 1);
    DrawTextEx(
        Globals::fonts["pacifico"],
        exit_button_text.c_str(),
        Vector2{
            exit_button.GetBounds().x + exit_button.GetBounds().width/2 - exit_text_size.x/2,
            exit_button.GetBounds().y + exit_button.GetBounds().height/2 - exit_text_size.y/2
        },
        button_font_size,
        1.f, 
        WHITE
    );
}