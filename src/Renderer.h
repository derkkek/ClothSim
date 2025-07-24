#pragma once
#include "Particle.h"
#include "Line.h"
class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;
	void DrawParticle(Particle* particle, sf::RenderWindow& window);
	void DrawLine(Line* line, sf::RenderWindow& window);
	void DrawGeometry(std::vector<Particle*> &particles, std::vector<Line*> &lines, sf::RenderWindow& window);
	void DrawLines(std::vector<Line*>& lines, sf::RenderWindow& window);
private:

};