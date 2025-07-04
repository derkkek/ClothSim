#include <SFML/Graphics.hpp>


#pragma once
using namespace sf;
class Particle
{
public:
	Particle(Vector3f position, bool stable);
	~Particle();

	void Update(float dt, Vector3f gravity);

	void Accelerate(Vector3f acc);
	void UpdateRenderData();

	void Verlet(float dt, Vector3f gravity);
	void KeepInside(float bound_y);

	const CircleShape& Shape();
	void SetPosition(float x, float y, float z);
	Vector3f GetPosition();
	Vector3f GetInitPosition();
	Vector3f acceleration;
	bool stable;

private:
	Vector3f position;
	Vector3f oldPosition;
	Vector3f initPos;
	Vector3f force;
	CircleShape shape;

	float radius = 4.0f;
	Color color = Color::White;
};
