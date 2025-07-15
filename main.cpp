#include <src/function.h>

int main()
{
    // Enable MSAA 4X.
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    // Initialize window.
    InitWindow(window, window, "Music");

    // Set Window Options.
    SetWindowIcon(LoadImage("./res/icons/quraan_icon.png"));

    // Initialize Audio Device.
    InitAudioDevice();

    // Music object.
    Music music[] = {
        LoadMusicStream("resource/Music/CHAL DIYE TUM KAHAN  LYRICAL OST  VIDEO SONG - 4K  KABHI MAIN KABHI TUM  MUSTAFA x SHARJEENA.mp3"),
        LoadMusicStream("resource/Music/JOSH BRAR _ Tere Bina Na Guzara E Feat. Kinza Hashmi  Qaran Mallhi  Latest Punjabi Song 2024.mp3"),
        LoadMusicStream("resource/Music/Ranjheya Ve  Zain Zohaib  Yratta media.mp3"),
        LoadMusicStream("resource/Music/Sahiba (Music Video) Jasleen Royal Vijay Deverakonda Radhika Madan Stebin PriyaAditya Sudhanshu.mp3"),
        LoadMusicStream("resource/Music/Shubh - Supreme (Official Music Video).mp3"),
    };

    string music_name[] = {
        "CHAL DIYE TUM KAHAN",
        "Tere Bina Na Guzara E",
        "Ranjheya Ve",
        "Sahiba",
        "Supreme"};
    PlayMusicStream(music[1]);

    // Slider rec.
    Rectangle seek_rec{50, 400, 300, 10};
    seek_rec.x = GetScreenWidth() / 2.0f - seek_rec.width / 2.0f;

    // Texture2D.
    Texture2D texture = LoadTexture("resource/cd.png");
    texture.width = 212;
    texture.height = 212;
    Texture2D dark_mode = LoadTexture("resource/dark-mode-toggle.png");
    dark_mode.width = 101;
    dark_mode.height = 52;
    Texture2D light_mode = LoadTexture("resource/light-mode-toggle.png");
    light_mode.width = 101;
    light_mode.height = 52;
    Texture2D forward = LoadTexture("resource/forward.png");
    forward.width = 35;
    forward.height = 35;
    Texture2D backward = LoadTexture("resource/backward.png");
    backward.width = 35;
    backward.height = 35;

    // Target FPS.
    SetTargetFPS(60);

    // Render loop.
    while (!WindowShouldClose())
    {
        // <----- UPDATE ----->
        float tex_centerx = GetScreenWidth() / 2.0f - texture.width / 2.0f;
        float tex_centery = GetScreenWidth() / 2.0f - texture.height / 2.0f;
        Vector2 mode_pos{
            GetScreenWidth() - 110,
            20};
        bool is_mode_hover = CheckCollisionPointRec(GetMousePosition(), Rectangle{mode_pos.x, mode_pos.y, light_mode.width, light_mode.height});

        if (is_mode_hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            is_dark_mode = is_dark_mode ? false : true;
        }
        if (isButtonHover || isSliderHover || isButtonHover_2 || is_mode_hover)
        {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Update Music Buffer.
        UpdateMusicStream(music[current_item]);

        // <----- RENDER ----->
        BeginDrawing();
        // Clear Background
        ClearBackground(is_dark_mode ? BLACK : WHITE);
        // <--- DRAW --->
        DrawTexture(texture, tex_centerx, tex_centery - 200, WHITE);
        GuiPlayButton(Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f + 200}, music[current_item], 50, is_dark_mode ? SKYBLUE : GOLD, WHITE);
        GuiNex_previous_Button(Vector2{GetScreenWidth() / 2.0f + 100, GetScreenHeight() / 2.0f + 200}, music, forward, 35, is_dark_mode ? SKYBLUE : GOLD, WHITE, "next");
        GuiNex_previous_Button(Vector2{GetScreenWidth() / 2.0f - 100, GetScreenHeight() / 2.0f + 200}, music, backward, 35, is_dark_mode ? SKYBLUE : GOLD, WHITE, "back");

        GuiSliderMusic(seek_rec, music[current_item], SKYBLUE);
        DrawText(music_name[current_item].c_str(), GetScreenWidth() / 2.0f - MeasureText(music_name[current_item].c_str(), 30) / 2.0f, GetScreenHeight() / 2.0f + 50, 30, is_dark_mode ? WHITE : BLACK);
        if (is_dark_mode)
        {
            DrawTextureV(dark_mode, mode_pos, SKYBLUE);
        }
        else
        {
            DrawTextureV(light_mode, mode_pos, GOLD);
        }
        EndDrawing();
    }

    // De Initialization of OpenGL Context.
    CloseWindow();
}