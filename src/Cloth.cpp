#include "Cloth.h"
#include <iostream>
#include <set>
#include <algorithm>

Cloth::Cloth(float start, float end, float step) 
    :gravity(sf::Vector3f(0.0f, 200.0f, 0.0f)), rows((end - start) / step), cols((end - start) / step)
{
    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            float x = start + row * step;
            float y = start + col * step;
            if (col == 0)
            {
                particles.push_back(new Particle(sf::Vector3f(x, y, 0.0f), true));
            }
            else
            {
                particles.push_back(new Particle(sf::Vector3f(x, y, 0.0f), false));

            }

        }
    }

    std::set<std::pair<Particle*, Particle*>> existingLines;

    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            int index = row * cols + col;
            Particle* a = particles.at(index);
            std::vector<Particle*> neighbors = GetNeighbors(row, col);
            for (Particle* b : neighbors) 
            {
                auto linePair = std::minmax(a, b);
                if (existingLines.find(linePair) == existingLines.end()) 
                {
                    lines.push_back(new Line(a, b, Arithmetic::GetDistance(a, b)));
                    existingLines.insert(linePair);
                }
            }
        }
    }
}

void Cloth::Update(float dt)
{
    for each(Particle* particle in particles)
    {
        particle->Update(dt, gravity);
    }

    for each(Line* line in lines)
    {
        line->Update();
    }

}

void Cloth::Render(RenderWindow& window)
{
    for each(Particle * particle in particles)
    {
        window.draw(particle->Shape());
    }
    for each(Line * line in lines)
    {
        window.draw(line->GetVAO());
    }
}

std::vector<Particle*> Cloth::GetNeighbors(int i, int j) 
{
    std::vector<Particle*> neighbors;

    // Up
    if (i > 0)
        neighbors.push_back(particles[(i - 1) * cols + j]);
    // Down
    if (i < rows - 1)
        neighbors.push_back(particles[(i + 1) * cols + j]);
    // Left
    if (j > 0)
        neighbors.push_back(particles[i * cols + (j - 1)]);
    // Right
    if (j < cols - 1)
        neighbors.push_back(particles[i * cols + (j + 1)]);

    return neighbors;
}