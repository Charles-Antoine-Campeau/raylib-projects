
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
    
    while(!WindowShouldClose())
    {
        //UPDATE************************************************************************
        UpdatePhysics();
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            CreatePhysicsBodyCircle(GetMousePosition(), GetRandomValue(10, 45), 10);
        }
        
        int bodiesCount = GetPhysicsBodiesCount();
        
        // Destroy falling physics bodies
        for (int i = bodiesCount - 1; i >= 0; i--)
        {
            PhysicsBody body = GetPhysicsBody(i);
            if (body != NULL && (body->position.y > screenHeight*2)) DestroyPhysicsBody(body);
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