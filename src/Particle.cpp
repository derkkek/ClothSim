#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3f pos, bool stable = false)
	:position(pos), oldPosition(pos), initPos(position), stable(stable)
{
	
	this->shape.setPosition(Vector2f(this->position.x, this->position.y));
	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setFillColor(this->color);
}

Particle::~Particle()
{
}

void Particle::Update(float dt, Vector3f gravity)
{
	//sf::Vector2i mouseWin = sf::Mouse::getPosition(window);
		////sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

		//// For world-relative coordinates (game objects, scene)
		//sf::Vector2f mouseWorld = window.mapPixelToCoords(mouseWin);

		//if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Arithmetic::GetMouseDistance(particle, mouseWorld) <= 50.0f)
		//{
		//    particle->SetPosition(mouseWorld.x, mouseWorld.y, 0.0f);
		//    for each(Particle * particle in particles)
		//        particle->acceleration = sf::Vector3f(0.0f, 0.0f, 0.0f);

		//    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		//    {
		//        particle->Accelerate(gravity);
		//    }
		//}
		//particle->Accelerate(gravity);
	if (stable)
	{
		this->SetPosition(GetInitPosition().x, GetInitPosition().y, GetInitPosition().z);
	}
	else
	{
		Verlet(dt, gravity);
	}
	KeepInside(800.0f); // WINDOW HEIGT
	UpdateRenderData();
}



void Particle::Accelerate(Vector3f acc)
{
	this->acceleration += acc;
}

void Particle::UpdateRenderData()
{
	this->shape.setPosition(Vector2f(this->position.x, this->position.y));
}

void Particle::Verlet(float dt, Vector3f gravity)
{	
	Vector3f newPos = position + (position - oldPosition) * (1.0f - 0.01f) + gravity * (1.0f - 0.01f) * dt * dt;
	oldPosition = position;
	position = newPos;

	//std::cout << position.x << ", " << position.y << ", " << position.z << "\n\n";

}

void Particle::KeepInside(float bound_y)
{
	if (GetPosition().y > bound_y) 
	{
	    SetPosition(GetPosition().x, bound_y, 0.0f);
		acceleration = sf::Vector3f(0.0f, 0.0f, 0.0f);
	}

}

const CircleShape& Particle::Shape()
{
	return this->shape;
}

void Particle::SetPosition(float x, float y, float z)
{
	this->position = Vector3f(x, y, z);
	this->shape.setPosition(Vector2f(this->position.x, this->position.y));
}

Vector3f Particle::GetPosition()
{
	return position;
}

Vector3f Particle::GetInitPosition()
{
	return initPos;
}
