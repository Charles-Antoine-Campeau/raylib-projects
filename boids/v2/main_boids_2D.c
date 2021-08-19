#include "raylib.h"

//***************************************************************************************************************************************
//GLOBAL VARIALBES
//constants for screen
const int screenHeight = 900;
const int screenWidth = 1400;

//constants for circles
const int numberOfCircles = 15;
const int radius = 10;

const Color color[] = {GRAY, YELLOW, GOLD, ORANGE, PINK, RED, MAROON, GREEN, LIME, DARKGREEN, 
                       SKYBLUE, DARKBLUE, PURPLE, DARKPURPLE, BROWN};

//***************************************************************************************************************************************

#include "functions.c"

int main(void)
{
    //array to store all the boids
    struct Boid boids[numberOfCircles];

    //initialise the screen
    InitWindow(screenWidth, screenHeight, "Boid 2D");
    SetTargetFPS(60);

    //set the starting point and starting vector for each circle
    int start = 50;
    for(int i = 0; i  < numberOfCircles; i++)
    {
        //create a boid and add it to the array
        struct Boid tmpBoid;
        tmpBoid.color = color[i];
        tmpBoid.direction = (Vector2){1, 1};
        tmpBoid.position = (Vector2){start, GetRandomValue(40, 300)};
        tmpBoid.radius = radius;
        boids[i] = tmpBoid;
        
        start += 60;
    }

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //UPDATE****************************************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            CheckIfBorderReach(&boids[i], screenHeight, screenWidth, radius);
            
            //Change the direction of the circle if another circle is going to collide with it
            for(int j = i; j < numberOfCircles; j++)
            {
                if(i != j)
                {
                    CheckIfGoingToCollide(&boids[i], &boids[j]);
                }
            }

            //move the circle
            boids[i].position = (Vector2) {boids[i].position.x + boids[i].direction.x, boids[i].position.y + boids[i].direction.y};
        }
        
        //DRAW******************************************************************************
        for(int i = 0; i < numberOfCircles; i++)
        {
            DrawCircle(GetPositionX(boids[i]), GetPositionY(boids[i]), radius, GetBoidColor(boids[i]));
        }
        
        
        EndDrawing();
    }
}