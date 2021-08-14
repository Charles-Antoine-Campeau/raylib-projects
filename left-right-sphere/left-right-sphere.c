/*
* First program with raylib.  Consist of moving a sphere back and forth from left to right.
*/

#include "raylib.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;
    
    Camera camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    Vector3 spherePosition = {0.0f, 0.0f, 0.0f};
    
    InitWindow(screenWidth, screenHeight, "Left right sphere");
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        
        DrawSphere(spherePosition, 1, RED);
        
        DrawGrid(10, 1.0f);
        
        EndMode3D();
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}