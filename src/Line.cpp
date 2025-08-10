#include "Line.h"

Line::Line(Particle* p1, Particle* p2, float length)
	:p1(p1), p2(p2), length(length), correctionX(0.0f), correctionY(0.0f), temporary(false), stiffness(0.1f)
{
	lineVA[0] = sf::Vertex(sf::Vector2f(p1->GetPosition().x, p1->GetPosition().y), sf::Color::White);
	lineVA[1] = sf::Vertex(sf::Vector2f(p2->GetPosition().x, p2->GetPosition().y), sf::Color::White);
}

Line::Line(Particle* p, Vector3f end, float length, bool temporary = false)
	:p1(p), p2(nullptr), startPos(p1->GetPosition()), endPos(end), length(length), correctionX(0.0f), correctionY(0.0f), stiffness(0.1f),temporary(temporary)
{
	lineVA[0] = sf::Vertex(sf::Vector2f(p->GetPosition().x, p->GetPosition().y), sf::Color::Red);
	lineVA[1] = sf::Vertex(sf::Vector2f(end.x, end.y), sf::Color::Red);
}

VertexArray Line::GetVAO()
{
	return lineVA;
}

void Line::Update(float dt)
{
    Particle* p1 = GetP1();
    Particle* p2 = GetP2();

    Vector3f p1_Pos = p1->GetPosition();
    Vector3f p2_Pos = p2->GetPosition();

    sf::Vector2f l = Arithmetic::GetDifference(p1, p2);
    float current_length = Arithmetic::GetLength(l);

    if (current_length == 0.0f) return; // Prevent division by zero

    float w1 = 1.0f / p1->mass;
    float w2 = 1.0f / p2->mass;

    float C = current_length - length;
    Vector2f constraintGradient = l / current_length;
    float a = 1.0f / stiffness;

    float lambda = C / (w1 * Arithmetic::GetLength(constraintGradient) * Arithmetic::GetLength(constraintGradient) + w2 * Arithmetic::GetLength(constraintGradient) * Arithmetic::GetLength(constraintGradient) + (a / dt * dt));

    correctionX = stiffness * lambda * w1 * constraintGradient.x;
    correctionY = stiffness * lambda * w2 * constraintGradient.y;
    p1->SetPosition(p1_Pos.x - correctionX , p1_Pos.y - correctionY, 0.0f);
    p2->SetPosition(p2_Pos.x + correctionX, p2_Pos.y + correctionY, 0.0f);


    UpdateVAO(p1->GetPosition(), p2->GetPosition());
}
void Line::UpdateVAO(Vector3f& start, Vector3f& end)
{
	lineVA[0] = sf::Vertex(sf::Vector2f(start.x, start.y), sf::Color::White);
	lineVA[1] = sf::Vertex(sf::Vector2f(end.x, end.y), sf::Color::White);
}

Particle* Line::GetP1()
{
	return p1;
}
Particle* Line::GetP2()
{
	return p2;
}

float Line::GetLength()
{
	return length;
}

float Line::GetCorrectionX()
{
	return correctionX;
}

float Line::GetCorrectionY()
{
	return correctionY;
}
