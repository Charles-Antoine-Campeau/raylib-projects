
#include "raylib.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

int main(void)
{
    //initiate the window
    const int screenHeight = 800;
    const int screenWidth = 1200;
    InitWindow(screenWidth, screenHeight, "Boids");
    SetTargetFPS(60);
    
    InitPhysics();
    
    // Create floor rectangle physics body
    PhysicsBody floor = CreatePhysicsBodyRectangle((Vector2){ screenWidth/2, screenHeight }, screenWidth, 10, 10);
    floor->enabled = false; // Disable body state to convert it to static (no dynamics, but collisions)
    floor->restitution = 1;
    
    //Create left rectangle physics body
    PhysicsBody leftWall = CreatePhysicsBodyRectangle((Vector2){0, screenHeight/2 }, 10, screenHeight, 10);
    leftWall->enabled = false;
    leftWall->restitution = 1;
    
    //Create right rectangle physics body
    PhysicsBody rightWall = CreatePhysicsBodyRectangle((Vector2){screenWidth, screenHeight/2}, 10, screenHeight, 10);
    rightWall->enabled = false;
    rightWall->restitution = 1;
    
    //Create roof rectangle physics body
    PhysicsBody roof = CreatePhysicsBodyRectangle((Vector2){screenWidth/2, 0}, screenWidth, 10, 10);
    roof->enabled = false;
    roof->restitution = 1;
    
    while(!WindowShouldClose())
    {
        //UPDATE************************************************************************
        UpdatePhysics();
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            PhysicsBody tmpSphere = CreatePhysicsBodyCircle(GetMousePosition(), GetRandomValue(10, 45), 10);
            tmpSphere->useGravity = false;
            tmpSphere->velocity = (Vector2){GetRandomValue(-1, 1), GetRandomValue(-1, 1)};
            tmpSphere->restitution = 5;
        }
        
        int bodiesCount = GetPhysicsBodiesCount();
        
        // Destroy out of bounds physics bodies
        for (int i = bodiesCount - 1; i >= 0; i--)
        {
            PhysicsBody body = GetPhysicsBody(i);
            int positionY = body->position.y;
            int positionX = body->position.x;
            if (body != NULL && ( (positionY > screenHeight*2) || (positionY < -screenHeight) || (positionX > screenWidth * 2) || (positionX < -screenWidth) ) )
            {
                DestroyPhysicsBody(body);
            }
        }

        
        //DRAW**************************************************************************
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        
        // Draw created physics bodies
            bodiesCount = GetPhysicsBodiesCount();
            for (int i = 0; i < bodiesCount; i++)
            {
                PhysicsBody body = GetPhysicsBody(i);

                if (body != NULL)
                {
                    int vertexCount = GetPhysicsShapeVerticesCount(i);
                    for (int j = 0; j < vertexCount; j++)
                    {
                        // Get physics bodies shape vertices to draw lines
                        // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                        DrawLineV(vertexA, vertexB, BLACK);     // Draw a line between two vertex positions
                    }
                }
            }
               
        EndDrawing();
    }
    
    ClosePhysics();
    CloseWindow();
}