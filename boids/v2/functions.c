#include "raylib.h"
#include "math.h"

//***************************************************************************************************************************************
//STRUCTURE DEFINITION
struct Boid
{
    Color color;
    Vector2 direction;
    Vector2 position;
    int radius;
};

//***************************************************************************************************************************************
//Get methods
Color GetBoidColor(struct Boid boid) {return boid.color; }
Vector2 GetDirection(struct Boid boid) {return boid.direction; }
int GetDirectionX(struct Boid boid) { return boid.direction.x; }
int GetDirectionY(struct Boid boid) { return boid.direction.y; }
Vector2 GetPosition(struct Boid boid) { return boid.direction; }
int GetPositionX(struct Boid boid) { return boid.position.x; }
int GetPositionY(struct Boid boid) { return boid.position.y; }
int GetRadius(struct Boid boid) { return boid.radius; }

//***************************************************************************************************************************************
//SET METHODS
void SetColor(struct Boid boid, Color color) {boid.color = color; }
void SetDirection(struct Boid boid, int x, int y) { boid.direction = (Vector2) {x, y}; }
void SetPosition(struct Boid boid, Vector2 newVector){ boid.position = newVector; }
void SetRadius(struct Boid boid) { boid.radius = 10; }

//***************************************************************************************************************************************
//GLOBAL METHODS

/**
    Determine if the boid has reach one of the side of the screen
    Param:
        boid: Pointer to the boid to check
        height: height of the screen
        width: width of the screen
        circleRadius: radius of the boid
*/
void CheckIfBorderReach(struct Boid *boid, int height, int width, int circleRadius)
{
    if((boid->position.x >= (width - circleRadius*2)) || (boid->position.x <= circleRadius*2))
    {
        //boid has reach the left or right side
        boid->direction.x = -boid->direction.x;
    }
    if((boid->position.y >= (height - circleRadius*2) || boid->position.y <= circleRadius*2))
    {
        //boid has reach the top or bottom of the screen
        boid->direction.y = -boid->direction.y;
    }
}

/**
    Determine if a boid is goingto colide with another boid
    Param:
        this: pointer to the first boid
        other: pointer to the second boid
*/
void CheckIfGoingToCollide(struct Boid *this, struct Boid *other)
{
    int deltaX = other->position.x - this->position.x;
    int deltaY = other->position.y - this->position.y;
    
    //verify the distance between the 2 circles
    if (deltaX <= radius*5 || deltaY <= radius*5)
    {
        //determine the type of tragectory
        if(this->position.x == other->position.x)
        {
            if(this->position.y == other->position.x)
            {
                //do nothing, parrallel
            }
            else
            {
                this->direction.y = -this->direction.y;
            }
        }
        else
        {
            if(this->position.y == other->position.y)
            {
                this->direction.x = -this->direction.x;
            }
        }
    }
}

/**
    Add two Vector2 together
    Param:
        first: pointer to the first Vector2
        second: pointer to the second Vector2
    return:
        The sum of the two Vector2
*/
Vector2 AddVectors(Vector2 *first, Vector2 *second)
{
    return (Vector2) {first->x + second->x, first->y + second->y};
}

/**
*/
void DirectInSameDirectionThanLocalRegion()
{
    
}