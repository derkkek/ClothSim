#include "Renderer.h"

void Renderer::DrawParticle(Particle* particle, sf::RenderWindow& window)
{
	window.draw(particle->Shape());
}

void Renderer::DrawLine(Line* line, sf::RenderWindow& window)
{
	window.draw(line->GetVAO());
}

void Renderer::DrawGeometry(std::vector<Particle*> particles, std::vector<Line*> lines, sf::RenderWindow& window)
{
	for each(Particle* particle in particles)
	{
		DrawParticle(particle, window);
	}
	for each(Line* line in lines)
	{
		DrawLine(line, window);
	}
}
