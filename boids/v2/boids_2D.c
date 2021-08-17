
#include "raylib.h"

int main(void)
{
    const int screenHeight = 1000;
    const int screenWidth = 1400;
    
    InitWindow(screenWidth, screenHeight, "Boid 2D");
    SetTargetFPS(60);
    
    
    int CenterX[] = {20};
    int CenterY[] = {20};
    
    Vector2 direction[] = {{1,1}};
    
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //UPDATE***************************************************
        CenterX[0] += direction[0].x;
        CenterY[0] += direction[0].y;
        
        //DRAW*****************************************************
        DrawCircle(CenterX[0], CenterY[0], 15, RED);
        
        EndDrawing();
    }
}