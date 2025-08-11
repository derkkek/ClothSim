#pragma once
#include <array>
#include "Particle.h"
#include "Line.h"
#include "Arithmetic.h"

class Triangle {
public:
    Triangle(Particle* p1, Particle* p2, Particle* p3);
    ~Triangle();

    std::array<Particle*, 3> GetVertices() const { return vertices; }
    float GetArea() const { return area; }
    sf::Vector3f GetCentroid() const;
    bool IsValid() const;

    // For rendering (optional)
    sf::VertexArray GetRenderData();
    void UpdateRenderData();

    void RelaxationUpdate();

private:
    std::array<Particle*, 3> vertices;
    float area;
    sf::VertexArray triangleVA{ sf::Triangles, 3 };

    float CalculateArea();
};