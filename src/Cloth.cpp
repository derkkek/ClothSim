#include "Cloth.h"
#include <iostream>
#include <set>
#include <algorithm>

Cloth::Cloth(float left, float right, float top, float bottom, float step)
    :gravity(sf::Vector3f(0.0f, 200.0f, 0.0f)), rows((right - left) / step), cols((bottom - top) / step)
{
    for (int row = 0; row < rows; ++row) 
    {
        for (int col = 0; col < cols; ++col) 
        {
            float x = left + row * step;
            float y = top + col * step;
            if (col == 0 && row % 6 == 0)
            {
                particles.push_back(new Particle(sf::Vector3f(x, y, 0.0f), true));
            }
            else
            {
                particles.push_back(new Particle(sf::Vector3f(x, y, 0.0f), false));

            }

        }
    }

    ConstructUniqueLines();
}

void Cloth::Update(float dt)
{
  
    ParticleGrabber(EventHandler::mousePressed);

    for (Particle* particle : particles)
    {

        particle->AddForce(gravity);
        particle->Update(dt);
        particle->ZeroForce();
        
    }

    for (int i = 0; i < 10; i++)
    {
        for (Line* line : lines)
        {
            line->Update();
        }
    }
}

void Cloth::Render(RenderWindow& window)
{
    for each(Particle* particle in particles)
    {
        particle->UpdateRenderData();
        window.draw(particle->Shape());
    }
    for each(Line * line in lines)
    {
        line->UpdateVAO();
        window.draw(line->GetVAO());
    }
}

void Cloth::ParticleGrabber(bool grab)
{
    static std::vector<Particle*> grabbedParticles;
    float offsetX;
    float offsetY;

    if (grab)
    {
        if (grabbedParticles.empty())
        {
            // Grab all particles within radius
            for (Particle* particle : particles)
            {
                float mouseDistance = Arithmetic::GetMouseDistance(particle, EventHandler::mouseWorld);
                if (mouseDistance <= 50.0f)
                {


                    grabbedParticles.push_back(particle);
                    particle->selected = true;
                }
            }
        }
        // Move all grabbed particles
        for (Particle* particle : grabbedParticles)
        {
            //offsetX = particle->GetPosition().x - EventHandler::mouseWorld.x;
            //offsetY = particle->GetPosition().y - EventHandler::mouseWorld.y;
            particle->SetPosition(EventHandler::mouseWorld.x + offsetX, EventHandler::mouseWorld.y + offsetY, 0.0f);
        }
    }
    else
    {
        // Release all grabbed particles
        for (Particle* particle : grabbedParticles)
        {
            particle->selected = false;
        }
        grabbedParticles.clear();
    }
}

void Cloth::ConstructUniqueLines()
{
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
                if (existingLines.find(linePair) == existingLines.end()) //if the unique pair doesn't exists in our set. 
                {
                    lines.push_back(new Line(a, b, Arithmetic::GetDistance(a, b)));
                    existingLines.insert(linePair);
                }
            }
        }
    }
    existingLines.clear();
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