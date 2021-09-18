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
Color GetBoidColor(struct Boid *boid) {return boid->color; }
Vector2 GetDirection(struct Boid *boid) {return boid->direction; }
double GetDirectionX(struct Boid *boid) { return boid->direction.x; }
double GetDirectionY(struct Boid *boid) { return boid->direction.y; }
Vector2 GetPosition(struct Boid *boid) { return boid->direction; }
double GetPositionX(struct Boid *boid) { return boid->position.x; }
double GetPositionY(struct Boid *boid) { return boid->position.y; }
double GetRadius(struct Boid *boid) { return boid->radius; }

//***************************************************************************************************************************************
//SET METHODS
void SetColor(struct Boid boid, Color color) {boid.color = color; }
void SetDirection(struct Boid *boid, Vector2 newDirection) { boid->direction = newDirection; }
void SetPosition(struct Boid *boid, Vector2 newVector){ boid->position = newVector; }
void SetRadius(struct Boid boid) { boid.radius = 10; }

//***************************************************************************************************************************************
//GLOBAL METHODS

double pythagoreanTheorem(double a, double b)
{
    return sqrt(pow(a, 2) + pow(b, 2));
}

/**
    Determine if the boid has reach one of the side of the screen
    Param:
        boid: Pointer to the boid to check
        height: height of the screen
        width: width of the screen
*/
void CheckIfBorderReach(struct Boid *boid, int height, int width)
{
    if((boid->position.x >= (width - vision)) || (boid->position.x <= vision))
    {
        //boid has reach the left or right side
        boid->direction.x = -boid->direction.x;
    }
    if((boid->position.y >= (height - vision) || boid->position.y <= vision))
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
    double deltaX = other->position.x - this->position.x;
    double deltaY = other->position.y - this->position.y;
    
    //verify the distance between the 2 circles
    if (deltaX <= collideDistance || deltaY <= collideDistance)
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
    Align a boid to go in the same direction than the other beside it
    Param:
        boids: array containg all the boids
        index: index of the boid to change direction
    Return:
        the new suggested vector
*/
Vector2 DirectInSameDirectionThanLocalRegion(struct Boid boids[], int index)
{
    int numberInLocal = 0;
    Vector2 newDirectionVector = (Vector2) {0.00, 0.00};
    
    for(int i = 0; i < numberOfCircles; i++)
    {
        //make sure it is not comparing the same boid
        if(i != index)
        {
            //get the distance between the boid in index and another one
            double deltaXPositon = GetPositionX(&boids[i]) + GetPositionX(&boids[index]);
            double deltaYPosition = GetPositionY(&boids[i]) + GetPositionY(&boids[index]);
            double scalarPosition = sqrt(pow(deltaXPositon, 2) + pow(deltaYPosition, 2));
            
            //determine if the other boid is close and add its direction to the new vector
            if(scalarPosition < vision)
            {
                numberInLocal++;
                AddVectors(&newDirectionVector, &boids[i].direction); 
            }
        }
    }
    
    if(numberInLocal > 0)
    {
        newDirectionVector.x = newDirectionVector.x / numberInLocal;
        newDirectionVector.y = newDirectionVector.y / numberInLocal;
        return newDirectionVector;
    }
    else
    {
        Vector2 nullReturn = {0,0};
        return nullReturn;
    }
}

/**
    Get the perceived global center of mass and create a vector to move the boid towards that point
    Param:
        boids: array containg all the boids
        index: index of the boid to change direction
    Return:
        a vector pointing towards the center of mass
*/
Vector2 MoveTowardCenter(struct Boid boids[], int index)
{
    Vector2 center = {0,0};
    
    for(int i = 0; i < numberOfCircles; i++)
    {
        if(i != index)
        {
            center = AddVectors(&center, &boids[i].position);
        }
    }
    
    center.x = ((center.x/(numberOfCircles - 1)) - boids[index].position.x)/100;
    center.y = ((center.y/(numberOfCircles - 1)) - boids[index].position.y)/100;
    
    return center;
}

/**
    Create a repulsion vector for the boid
    Param:
        boids: array containg all the boids
        index: index of the boid to change direction
    Return:
        the repulsion vector
*/
Vector2 KeepAwayFromOthers(struct Boid boids[], int index)
{
    Vector2 repulsion = {0, 0};
    
    for(int i = 0; i < numberOfCircles; i++)
    {
        if(i != index)
        {
            Vector2 delta;
            delta.x = boids[i].position.x - boids[index].position.x;
            delta.y = boids[i].position.y - boids[index].position.y;
            
            if(abs(pythagoreanTheorem(delta.x, delta.y)) < 100)
            {
                repulsion.x = repulsion.x - delta.x;
                repulsion.y = repulsion.y - delta.y;
            }
        }
    }
    
    return repulsion;
}