#pragma once
#include "Line.h"
#include "Particle.h"
#include "EventHandler.h"
using namespace sf;
class Cloth
{
public:
	Cloth(float left, float right, float top, float bottom, float step);
	~Cloth() =default;

	void Update(float dt, int constraintIteration);
	void ParticleGrabber(bool grab); // passing bool to a function is a bad practice..
	void DestroyLineByMouse(bool destroy);
	void DestroyLineByOffset();
	void DestroyUnreferencedParticles();

	void ConstructUniqueLines();

	std::vector<Particle*> Particles();
	std::vector<Line*> Lines();

	std::vector<Particle*> GetNeighbors(int i, int j);

	void SetGravity(Vector3f& gravity);

private:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;

	int rows;
	int cols;

	Vector3f gravity;
	Vector3f wind;

};
