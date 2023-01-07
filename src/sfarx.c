#include "raylib.h"

int screenWidth = 800;
int screenHeight = 450;

void UpdateDrawFrame(void);

int main()
{
    InitWindow(screenWidth, screenHeight, "sfarx");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("hello world!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}