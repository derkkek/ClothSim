#include "Arithmetic.h"


float Arithmetic::GetDistance(Particle* p1, Particle* p2)
{
    float dx = p1->GetPosition().x - p2->GetPosition().x;
    float dy = p1->GetPosition().y - p2->GetPosition().y;

    return sqrt(dx * dx + dy * dy);
}

float Arithmetic::GetMouseDistance(Particle* p, Vector2f mousePos)
{
    float dx = p->GetPosition().x - mousePos.x;
    float dy = p->GetPosition().y - mousePos.y;

    return sqrt(dx * dx + dy * dy);
}

float Arithmetic::GetLength(Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

Vector2f Arithmetic::GetDifference(Particle* p1, Particle* p2)
{
    Vector2f difference;
    difference.x = p1->GetPosition().x - p2->GetPosition().x;
    difference.y = p1->GetPosition().y - p2->GetPosition().y;

    return difference;
}
