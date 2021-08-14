/*
* First program with raylib.  Consist of moving a sphere back and forth from left to right.
*/

#include "raylib.h"

int main(void)
{
    //screen size
    const int screenWidth = 1200;
    const int screenHeight = 800;
    
    //Set the 3d camera
    Camera camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    //set the variables for the sphere
    Vector3 spherePosition = {0.0f, 0.0f, 0.0f};
    bool goRight = true;
    float speed = 1.0f;
    float distance = 4.0f;
    
    InitWindow(screenWidth, screenHeight, "Left right sphere");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        
        DrawSphere(spherePosition, 1, RED);
        DrawGrid(10, 1.0f);
        
        //determine if the sphere needs to move left or right
        if(goRight)
        {
            spherePosition.x += speed * GetFrameTime();
        }
        else
        {
            spherePosition.x -= speed * GetFrameTime();
        }
        
        //determine if the sphere has reach one of the end
        if(spherePosition.x >= distance)
        {
            goRight = false;
        }
        if(spherePosition.x <= -distance)
        {
            goRight = true;
        }
        
        EndMode3D();
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}