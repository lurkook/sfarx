#include "raylib.h"
#include <stdio.h>
#include <sfarx.h>
#include <mz.h>

int main(void)
{
    /*
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "sfarx");
    SetTargetFPS(60);

    while (!WindowShouldClose())
        update();

    CloseWindow();
    */

    FILE *ptr = fopen("/home/mikhail/Spark The Electric Jester.exe", "r");
    mz_t mz = mz_read(ptr);

    return 0;
}

void update(void)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("hello world!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}