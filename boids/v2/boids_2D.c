
#include "raylib.h"

int main(void)
{
    //constants for circles
    const int screenHeight = 1000;
    const int screenWidth = 1400;
    
    //constants for circles
    const int numberOfCircles = 15;
    const int radius = 5;
    
    //variables for circles
    int CenterX[numberOfCircles];
    int CenterY[numberOfCircles];
    Vector2 direction[numberOfCircles];
    
    //initialise the screen
    InitWindow(screenWidth, screenHeight, "Boid 2D");
    SetTargetFPS(60);
    
    //set the starting point and starting vector for each circle
    int start = 20;
    for(int i = 0; i  < numberOfCircles; i++)
    {
        CenterX[i] = start;
        CenterY[i] = 40;
        
        start += 20;
        
        direction[i] = (Vector2){1, 1};
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //UPDATE****************************************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            //change the direction of the circle if it has reach one of the side
            if((CenterX[i] >= (screenWidth - radius*2)) || (CenterX[i] <= radius*2))
            {
                direction[i].x = -direction[i].x;
            }
            if(CenterY[i] >= (screenHeight - radius*2) || CenterY[i] <= radius*2)
            {
                direction[i].y = -direction[i].y;
            }
            
            //move the circle
            CenterX[i] += direction[i].x;
            CenterY[i] += direction[i].y;
        }

        //DRAW******************************************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            DrawCircle(CenterX[i], CenterY[i], radius, RED);
        }
        
        
        EndDrawing();
    }
}