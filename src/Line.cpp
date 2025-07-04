#include "Line.h"

Line::Line(Particle* p1, Particle* p2, float length)
	:p1(p1), p2(p2), length(length)
{
	lineVA[0] = sf::Vertex(sf::Vector2f(p1->GetPosition().x, p1->GetPosition().y), sf::Color::White);
	lineVA[1] = sf::Vertex(sf::Vector2f(p2->GetPosition().x, p2->GetPosition().y), sf::Color::White);

}

VertexArray Line::GetVAO()
{
	return lineVA;
}

void Line::Update()
{
	sf::Vector2f diff = Arithmetic::GetDifference(GetP1(), GetP2());
	float diffFactor = (GetLength() - Arithmetic::GetLength(diff)) / Arithmetic::GetLength(diff) * 0.5;

	float softness = 1.0f;

	float offsetX = diff.x * diffFactor * softness;
	float offsetY = diff.y * diffFactor * softness;

	GetP1()->SetPosition(GetP1()->GetPosition().x + offsetX, GetP1()->GetPosition().y + offsetY, 0.0f);
	GetP2()->SetPosition(GetP2()->GetPosition().x - offsetX, GetP2()->GetPosition().y - offsetY, 0.0f);
}

void Line::UpdateVAO()
{
	lineVA[0] = sf::Vertex(sf::Vector2f(p1->GetPosition().x, p1->GetPosition().y), sf::Color::White);
	lineVA[1] = sf::Vertex(sf::Vector2f(p2->GetPosition().x, p2->GetPosition().y), sf::Color::White);
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
