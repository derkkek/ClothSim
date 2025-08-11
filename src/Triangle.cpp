#include "Triangle.h"

Triangle::Triangle(Particle* p1, Particle* p2, Particle* p3)
    : vertices{ p1, p2, p3 } {
    CalculateArea();
    UpdateRenderData();
}

Triangle::~Triangle() {
    // Don't delete particles - they're owned by the scene
}

float Triangle::CalculateArea() 
{
    float area = 0.0f;
    if (!vertices[0] || !vertices[1] || !vertices[2]) 
    {
        area = 0.0f;
        return area;
    }

    sf::Vector3f p1 = vertices[0]->GetPosition();
    sf::Vector3f p2 = vertices[1]->GetPosition();
    sf::Vector3f p3 = vertices[2]->GetPosition();

     area = abs((p1.x * (p2.y - p3.y) +
        p2.x * (p3.y - p1.y) +
        p3.x * (p1.y - p2.y)) / 2.0f);

     return area;
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

        // For triangle with vertices p1, p2, p3
        Particle* p1 = vertices[0];
        Particle* p2 = vertices[1];
        Particle* p3 = vertices[2];
        sf::Vector2f edge_12 = Arithmetic::GetDifference(p2, p1);
        sf::Vector2f edge_23 = Arithmetic::GetDifference(p3, p2);
        sf::Vector2f edge_31 = Arithmetic::GetDifference(p1, p3);

        // Gradients (perpendicular to opposite edges)
        sf::Vector2f grad1 = 0.5f * sf::Vector2f(-edge_23.y, edge_23.x);  // perpendicular to p2-p3
        sf::Vector2f grad2 = 0.5f * sf::Vector2f(-edge_31.y, edge_31.x);  // perpendicular to p3-p1  
        sf::Vector2f grad3 = 0.5f * sf::Vector2f(-edge_12.y, edge_12.x);  // perpendicular to p1-p2

        float lambda = C / (Arithmetic::GetLength(grad1) * Arithmetic::GetLength(grad1) + Arithmetic::GetLength(grad2) * Arithmetic::GetLength(grad2) + Arithmetic::GetLength(grad3) * Arithmetic::GetLength(grad3));
        float correction1X = -lambda * grad1.x / p1->mass;
        float correction1Y = -lambda * grad1.y / p1->mass;

        float correction2X = -lambda * grad2.x / p2->mass;
        float correction2Y = -lambda * grad2.y / p2->mass;

        float correction3X = -lambda * grad3.x / p3->mass;
        float correction3Y = -lambda * grad3.y / p3->mass;
        p1->SetPosition(p1->GetPosition().x - correction1X, p1->GetPosition().y - correction1Y, 0.0f);
        p2->SetPosition(p2->GetPosition().x - correction2X, p2->GetPosition().y - correction2Y, 0.0f);
        p3->SetPosition(p3->GetPosition().x - correction3X, p3->GetPosition().y - correction3Y, 0.0f);

    }
}
