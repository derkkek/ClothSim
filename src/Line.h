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
	Line(Particle* p, Vector3f end, float length, bool temporary);
	~Line() = default;

	VertexArray GetVAO();
	void Update(float dt);
	void UpdateVAO(Vector3f& start, Vector3f& end);

	Particle* GetP1();
	Particle* GetP2();
	float GetLength();
	float GetCorrectionX();
	float GetCorrectionY();

	bool temporary;
	float stiffness;

private:
	Particle* p1;
	Particle* p2;
	Vector3f startPos;
	Vector3f endPos;
	VertexArray lineVA{ sf::Lines, 2 };
	float length;
	float correctionX;
	float correctionY;
};