#include "Triangle.h"

Triangle::Triangle(Particle* p1, Particle* p2, Particle* p3)
    : vertices{ p1, p2, p3 } , areaStiffness(0.1f)
{
    CalculateArea();
    UpdateRenderData();
}

Triangle::~Triangle() {
    // Don't delete particles - they're owned by the scene
}

float Triangle::CalculateArea()
{
    if (!vertices[0] || !vertices[1] || !vertices[2]) {
        return 0.0f;
    }

    sf::Vector3f p1 = vertices[0]->GetPosition();
    sf::Vector3f p2 = vertices[1]->GetPosition();
    sf::Vector3f p3 = vertices[2]->GetPosition();

    // Use cross product method for better numerical stability
    sf::Vector2f v1(p2.x - p1.x, p2.y - p1.y);
    sf::Vector2f v2(p3.x - p1.x, p3.y - p1.y);

    float crossProduct = v1.x * v2.y - v1.y * v2.x;
    return abs(crossProduct) * 0.5f;
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
    float C = area - currentArea;  
    
    if (abs(C) > 100.0f) 
    {
        // Get vertex positions
        Particle* p1 = vertices[1];
        Particle* p2 = vertices[0];
        Particle* p3 = vertices[2];

        sf::Vector3f pos1 = p1->GetPosition();
        sf::Vector3f pos2 = p2->GetPosition();
        sf::Vector3f pos3 = p3->GetPosition();

        // Gradient for p1: perpendicular to edge p2-p3
        sf::Vector2f edge_23 = sf::Vector2f(pos3.x - pos2.x, pos3.y - pos2.y);
        sf::Vector2f grad1 = 0.5f * sf::Vector2f(-edge_23.y, edge_23.x);

        // Gradient for p2: perpendicular to edge p3-p1  
        sf::Vector2f edge_31 = sf::Vector2f(pos1.x - pos3.x, pos1.y - pos3.y);
        sf::Vector2f grad2 = 0.5f * sf::Vector2f(-edge_31.y, edge_31.x);

        // Gradient for p3: perpendicular to edge p1-p2
        sf::Vector2f edge_12 = sf::Vector2f(pos2.x - pos1.x, pos2.y - pos1.y);
        sf::Vector2f grad3 = 0.5f * sf::Vector2f(-edge_12.y, edge_12.x);

        // Calculate lambda
        float gradMagSqr1 = grad1.x * grad1.x + grad1.y * grad1.y;
        float gradMagSqr2 = grad2.x * grad2.x + grad2.y * grad2.y;
        float gradMagSqr3 = grad3.x * grad3.x + grad3.y * grad3.y;

        float lambda = C / (gradMagSqr1 / p1->mass + gradMagSqr2 / p2->mass + gradMagSqr3 / p3->mass);

        sf::Vector2f correction1 = -lambda * grad1 / p1->mass;
        sf::Vector2f correction2 = -lambda * grad2 / p2->mass;
        sf::Vector2f correction3 = -lambda * grad3 / p3->mass;

        p1->SetPosition(pos1.x + correction1.x, pos1.y + correction1.y, 0.0f);
        p2->SetPosition(pos2.x + correction2.x, pos2.y + correction2.y, 0.0f);
        p3->SetPosition(pos3.x + correction3.x, pos3.y + correction3.y, 0.0f);
    }
}
