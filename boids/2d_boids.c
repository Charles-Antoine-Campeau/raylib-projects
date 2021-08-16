
#include "raylib.h"

int main(void)
{
    //initiate the window
    const int windowHeight = 800;
    const int windowWidth = 1200;
    InitWindow(windowWidth, windowHeight, "Boids");
    SetTargetFPS(60);
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        MaximizeWindow();
        EndDrawing();
    }
}