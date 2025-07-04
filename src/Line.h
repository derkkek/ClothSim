#pragma once
#include "Particle.h"
#include "Arithmetic.h"
#include <array>
#include <SFML/Graphics.hpp>
using namespace sf;
class Line
{
public:
	Line(Particle* p1, Particle* p2, float length);
	~Line() = default;

	VertexArray GetVAO();
	void Update();
	void UpdateVAO();
	Particle* GetP1();
	Particle* GetP2();
	float GetLength();
private:
	Particle* p1;
	Particle* p2;
	VertexArray lineVA{ sf::Lines, 2 };
	float length;
};