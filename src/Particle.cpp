#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3f pos, bool stable = false)
	:position(pos), oldPosition(pos), initPos(position), mass(1.0f), stable(stable), selected(false)
{
	
	this->shape.setPosition(Vector2f(this->position.x, this->position.y));
	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setFillColor(this->color);
}

Particle::~Particle()
{
}

void Particle::Update(float dt)
{
	if (stable)
	{
		this->SetPosition(GetInitPosition().x, GetInitPosition().y, GetInitPosition().z);
	}
	else
	{
		Verlet(dt);
	}
	KeepInside(1080.0f); // WINDOW HEIGT
}



void Particle::Accelerate(Vector3f acc)
{
	this->acceleration += acc;
}

void Particle::UpdateRenderData()
{
	this->shape.setPosition(Vector2f(this->position.x, this->position.y));
}

void Particle::AddForce(Vector3f force)
{
	this->force += force;
}

void Particle::ZeroForce()
{
	this->force = Vector3f(0.0f, 0.0f,0.0f);
}


void Particle::Verlet(float dt)
{	
	Vector3f newPos = position + (position - oldPosition) * (1.0f - 0.01f) + (force / mass) * (1.0f - 0.01f) * dt * dt;
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
