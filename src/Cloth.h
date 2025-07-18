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

	void Update(float dt);
	void ParticleGrabber(bool grab);
	void DestroyLine(bool destroy);
	void DestroyUnreferencedParticles();

	void ConstructUniqueLines();

	std::vector<Particle*> Particles();
	std::vector<Line*> Lines();

	std::vector<Particle*> GetNeighbors(int i, int j);

private:
	std::vector<Particle*> particles;
	std::vector<Line*> lines;

	int rows;
	int cols;

	Vector3f gravity;
	Vector3f wind;

};
