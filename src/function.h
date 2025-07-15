#include <raylib.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include <sstream>
using namespace std;
#define window 800

bool isButtonHover;
bool isSliderHover;
bool isButtonHover_2;
int current_item = 1;
static bool is_dark_mode = true;

// gui prototype

void GuiSliderMusic(Rectangle rec, Music &music, Color color)
{
    // Update
    Rectangle slider = rec;

    float time_played = GetMusicTimePlayed(music);
    float max_second = GetMusicTimeLength(music);
    isSliderHover = CheckCollisionPointRec(GetMousePosition(), rec);

    if (isSliderHover && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        float dx = GetMousePosition().x - rec.x;
        PauseMusicStream(music);
        slider.width = dx;
        SeekMusicStream(music, dx / (rec.width / max_second)); // Responsive depends to rec.width.
    }
    else
    {
        // ResumeMusicStream(music);
        slider.width = (rec.width / max_second) * time_played; // Responsive depends to rec.width.
    }

    // Point slider.
    float point_radius = rec.height / 2;
    Vector2 circle_center = Vector2{slider.x + slider.width, slider.y + point_radius};

    // Format: Convert second to minute.
    // Second to minute -> minute = second/60
    std::stringstream ss;
    ss << (int)time_played / 60 << ":"; // first show mins
    ss << (int)time_played % 60;

    // Render
    DrawRectangleRounded(slider, 1.0f, 7, is_dark_mode ? (isSliderHover ? color : Fade(color, 0.9f)) : (isSliderHover ? GOLD : Fade(GOLD, 0.9f))); // Slider
    DrawRectangleRounded(rec, 1.0f, 7, is_dark_mode ? Fade(color, 0.3f) : Fade(GOLD, 0.3f));                                                       // Rec
    DrawRectangleRoundedLinesEx(rec, 3, 1.0f, 7, is_dark_mode ? Fade(color, 0.7f) : Fade(GOLD, 0.7f));                                             // Border
    DrawCircleV(circle_center, point_radius, BLUE);
    DrawCircleLines(circle_center.x, circle_center.y, point_radius, is_dark_mode ? WHITE : BLACK);
    DrawText(ss.str().c_str(), rec.x - MeasureText(ss.str().c_str(), 23) - 23, rec.y, 23, is_dark_mode ? WHITE : BLACK);
    ss.clear();
    ss = std::stringstream("");
    ss << (int)max_second / 60 << ":"; // first show mins
    ss << (int)max_second % 60;
    DrawText(ss.str().c_str(), rec.x + rec.width + MeasureText(ss.str().c_str(), 23) - 18, rec.y, 23, is_dark_mode ? WHITE : BLACK);
}
void GuiPlayButton(Vector2 position, Music &music, float radius, Color bgColor, Color fgColor)
{
    // Update
    static bool isPlayed = true;
    isButtonHover = CheckCollisionPointCircle(position, GetMousePosition(), radius);
    float point = radius / 3.0f;

    if (isButtonHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        isPlayed = isPlayed ? false : true;
    }

    // Render
    DrawCircleV(position, radius, isButtonHover ? bgColor : Fade(bgColor, 0.7f));

    if (isPlayed)
    {
        ResumeMusicStream(music);
        // Resume Symbol Shape.
        DrawRectangle(position.x - point, position.y - point, radius / 4.0, radius / 1.5, fgColor);                   // Left Rectangle
        DrawRectangle(position.x + point - (radius / 4.0f), position.y - point, radius / 4.0, radius / 1.5, fgColor); // Right Rectangle
    }
    else
    {
        // Triangle Symbol Shape.
        PauseMusicStream(music);
        DrawTriangle(
            Vector2{position.x - point, position.y - point},
            Vector2{position.x - point, position.y + point},
            Vector2{position.x + point, position.y},
            fgColor);
    }
}

void GuiNex_previous_Button(Vector2 position, Music music[], Texture texture, float radius, Color bgColor, Color fgColor, string action)
{ // Update
    isButtonHover_2 = CheckCollisionPointCircle(position, GetMousePosition(), radius);
    if (isButtonHover_2)
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }

    if (isButtonHover_2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (action == "next")
        {
            if (current_item < 4)
            {
                current_item++;
                PlayMusicStream(music[current_item]);
            }
        }
        if (action == "back")
        {
            if (current_item > 0)
            {
                current_item--;
                PlayMusicStream(music[current_item]);
            }
        }
    }

    // Render
    DrawCircleV(position, radius, bgColor);
    DrawTexture(texture, position.x - radius / 2, position.y - radius / 2, fgColor);
}
