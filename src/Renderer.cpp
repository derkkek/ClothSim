#include "Renderer.h"

void Renderer::DrawParticle(Particle* particle, sf::RenderWindow& window)
{
	window.draw(particle->Shape());
}

void Renderer::DrawLine(Line* line, sf::RenderWindow& window)
{
	window.draw(line->GetVAO());
}

void Renderer::DrawLines(std::vector<Line*>& lines, sf::RenderWindow& window)
{
	for each(Line* line in lines)
	{
		DrawLine(line, window);
	}
}

void Renderer::DrawParticles(std::vector<Particle*>& particles, sf::RenderWindow& window)
{
	for each(Particle * particle in particles)
	{
		DrawParticle(particle, window);
	}
}

void Renderer::DrawGeometry(std::vector<Particle*> &particles, std::vector<Line*> &lines, sf::RenderWindow& window)
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

