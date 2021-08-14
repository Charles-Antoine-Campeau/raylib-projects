#include "raylib.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    
    InitWindow(screenWidth, screenHeight, "Left right sphere");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}