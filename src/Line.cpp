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
	float diffFactor = (GetLength() - Arithmetic::GetLength(diff)) / Arithmetic::GetLength(diff) * 0.5f;

	float softness = 0.5f;

	float offsetX = diff.x * diffFactor * softness;
	float offsetY = diff.y * diffFactor * softness;

	Particle* p1 = GetP1();
	Particle* p2 = GetP2();

	Vector3f p1_Pos = p1->GetPosition();
	Vector3f p2_Pos = p2->GetPosition();

	p1->SetPosition(p1_Pos.x + offsetX, p1_Pos.y + offsetY, 0.0f);
	p2->SetPosition(p2_Pos.x - offsetX, p2_Pos.y - offsetY, 0.0f);

	UpdateVAO();
}

void Line::UpdateVAO()
{
	Vector3f p1Pos = p1->GetPosition();
	Vector3f p2Pos = p2->GetPosition();
	lineVA[0] = sf::Vertex(sf::Vector2f(p1Pos.x, p1Pos.y), sf::Color::White);
	lineVA[1] = sf::Vertex(sf::Vector2f(p2Pos.x, p2Pos.y), sf::Color::White);
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
