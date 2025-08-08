#include "Particle.h"
#include <iostream>

Particle::Particle(Vector3f pos, float radius,bool stable = false)
	:position(pos), oldPosition(pos), initPos(position), mass(1.0f), radius(radius), stable(stable), selected(false)
{
	
	this->shape.setPosition(Vector2f(this->position.x, this->position.y));
	this->shape.setRadius(this->radius);
	this->shape.setOrigin(this->radius, this->radius);
	this->shape.setFillColor(this->color);
	this->shape.setOutlineThickness(3.5f);
	this->shape.setOutlineColor(sf::Color::Black);
}

Particle::~Particle()
{
}

void Particle::Update(float dt)
{
	if (stable)
	{
		Vector3f initPos = this->GetInitPosition();
		this->SetPosition(initPos.x, initPos.y, initPos.z);
	}
	else
	{
		Verlet(dt);
	}
	KeepInside(1080.0f); // WINDOW HEIGT
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
	Vector3f newPos = position + (position - oldPosition) + (force / mass) * dt * dt;
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
	else if (GetPosition().y < 0.0f)
	{
		SetPosition(GetPosition().x, 0.0f, 0.0f);
		acceleration.y = -acceleration.y;// sf::Vector3f(0.0f, 0.0f, 0.0f);
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
