
#include "raylib.h"

int main(void)
{    
    //constants for circles
    const int screenHeight = 900;
    const int screenWidth = 1400;
    
    //constants for circles
    const int numberOfCircles = 15;
    const int radius = 10;
    
    const Color color[] = {GRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, 
                           SKYBLUE, DARKBLUE, PURPLE, DARKPURPLE, BROWN};
    
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
        CenterY[i] = GetRandomValue(40, 250);
        
        start += 60;
        
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
            
            int centerOfGravityX = 0;
            int centerOfGravityY = 0;
            //Change the direction of the circle if another circle is going to collide with it
            for(int j = i; j < numberOfCircles; j++)
            {
                centerOfGravityX += CenterX[j];
                centerOfGravityY += CenterY[j];
                //make sure that the compared circle is not the same
                if(i != j)
                {
                    int deltaX = CenterX[j] - CenterX[i];
                    int deltaY = CenterY[j] - CenterY[j];
                    
                    //verify the distance between the 2 circles
                    if (deltaX <= radius*5 || deltaY <= radius*5)
                    {
                        //determine the type of tragectory
                        if(CenterX[i] == CenterX[j])
                        {
                            if(CenterY[i] == CenterY[j])
                            {
                                //do nothing, parrallel
                            }
                            else
                            {
                                direction[i].y = -direction[i].y;
                            }
                        }
                        else
                        {
                            if(CenterY[i] == CenterY[j])
                            {
                                direction[i].x = -direction[i].x;
                            }
                            else
                            {
                                
                            }
                        }
                    }
                    else
                    {
                        
                    }
                }
            }

            //move the circle
            CenterX[i] += direction[i].x;
            CenterY[i] += direction[i].y;
            
            
        }
        
        //DRAW******************************************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            DrawCircle(CenterX[i], CenterY[i], radius, color[i]);
        }
        
        
        EndDrawing();
    }
}