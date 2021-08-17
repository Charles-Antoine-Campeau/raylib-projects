
#include "raylib.h"

int main(void)
{
    const int screenHeight = 1000;
    const int screenWidth = 1400;
    
    const int numberOfCircles = 15;
    
    InitWindow(screenWidth, screenHeight, "Boid 2D");
    SetTargetFPS(60);
    
    int CenterX[numberOfCircles];
    int CenterY[numberOfCircles];
    Vector2 direction[numberOfCircles];
    
    int start = 20;
    for(int i = 0; i  < numberOfCircles; i++)
    {
        CenterX[i] = start;
        CenterY[i] = 20;
        
        start += 20;
        
        direction[i] = (Vector2){1, 1};
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //UPDATE***************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            CenterX[i] += direction[i].x;
            CenterY[i] += direction[i].y;
        }

        //DRAW*****************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            DrawCircle(CenterX[i], CenterY[i], 5, RED);
        }
        
        
        EndDrawing();
    }
}