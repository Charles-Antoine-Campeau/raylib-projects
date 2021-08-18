
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
    Vector2 position[numberOfCircles];
    Vector2 direction[numberOfCircles];

    //initialise the screen
    InitWindow(screenWidth, screenHeight, "Boid 2D");
    SetTargetFPS(60);

    //set the starting point and starting vector for each circle
    int start = 20;
    for(int i = 0; i  < numberOfCircles; i++)
    {
        position[i] = (Vector2){start, GetRandomValue(40, 300)};
        
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
            if((position[i].x >= (screenWidth - radius*2)) || (position[i].x <= radius*2))
            {
                direction[i].x = -direction[i].x;
            }
            if(position[i].y >= (screenHeight - radius*2) || position[i].y <= radius*2)
            {
                direction[i].y = -direction[i].y;
            }
            
            int centerOfGravityX = 0;
            int centerOfGravityY = 0;
            //Change the direction of the circle if another circle is going to collide with it
            for(int j = i; j < numberOfCircles; j++)
            {
                centerOfGravityX += position[j].x;
                centerOfGravityY += position[j].y;
                //make sure that the compared circle is not the same
                if(i != j)
                {
                    int deltaX = position[j].x - position[i].x;
                    int deltaY = position[j].y - position[j].y;
                    
                    //verify the distance between the 2 circles
                    if (deltaX <= radius*5 || deltaY <= radius*5)
                    {
                        //determine the type of tragectory
                        if(position[i].x == position[j].x)
                        {
                            if(position[i].y == position[j].y)
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
                            if(position[i].y == position[j].y)
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
            position[i].x += direction[i].x;
            position[i].y += direction[i].y;
            
            
        }
        
        //DRAW******************************************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            DrawCircle(position[i].x, position[i].y, radius, color[i]);
        }
        
        
        EndDrawing();
    }
}