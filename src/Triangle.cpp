#include "Triangle.h"

Triangle::Triangle(Particle* p1, Particle* p2, Particle* p3)
    : vertices{ p1, p2, p3 } {
    CalculateArea();
    UpdateRenderData();
}

Triangle::~Triangle() {
    // Don't delete particles - they're owned by the scene
}

float Triangle::CalculateArea() {
    if (!vertices[0] || !vertices[1] || !vertices[2]) {
        area = 0.0f;
        return;
    }

    sf::Vector3f p1 = vertices[0]->GetPosition();
    sf::Vector3f p2 = vertices[1]->GetPosition();
    sf::Vector3f p3 = vertices[2]->GetPosition();

     return abs((p1.x * (p2.y - p3.y) +
        p2.x * (p3.y - p1.y) +
        p3.x * (p1.y - p2.y)) / 2.0f);
}

sf::Vector3f Triangle::GetCentroid() const {
    sf::Vector3f p1 = vertices[0]->GetPosition();
    sf::Vector3f p2 = vertices[1]->GetPosition();
    sf::Vector3f p3 = vertices[2]->GetPosition();

    return sf::Vector3f((p1.x + p2.x + p3.x) / 3.0f,
        (p1.y + p2.y + p3.y) / 3.0f,
        0.0f);
}

bool Triangle::IsValid() const {
    return vertices[0] && vertices[1] && vertices[2] && area > 0.1f;
}

sf::VertexArray Triangle::GetRenderData() {
    UpdateRenderData();
    return triangleVA;
}

void Triangle::UpdateRenderData() {
    for (int i = 0; i < 3; ++i) {
        sf::Vector3f pos = vertices[i]->GetPosition();
        triangleVA[i] = sf::Vertex(sf::Vector2f(pos.x, pos.y),
            sf::Color(100, 150, 255, 60)); // Semi-transparent
    }
}

void Triangle::RelaxationUpdate()
{
    float currentArea = CalculateArea();
    float C = currentArea - area;
    if (abs(C) > 20.0f)
    {
        /*
        d. Compute gradients ∇C for each vertex
        e. Calculate correction scaling: λ = C / (|∇C₁|² + |∇C₂|² + |∇C₃|²)
        f. Apply position corrections: Δpᵢ = -λ * ∇Cᵢ / mᵢ    
        */
    }
}
