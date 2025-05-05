//
// Created by abraa on 5/4/2025.
//

#include <cmath>
#include <polygons/ArcPolygon.h>

ArcPolygon::ArcPolygon(const float x, const float y, const float radius,
                               const bool filled, const GLfloat startAngle,
                               const GLfloat endAngle)
    : Polygon(x, y, radius, 30, filled), startAngle(startAngle), endAngle(endAngle) {
  ArcPolygon::generateSegments();
  setupBuffers();
}

void ArcPolygon::setupBuffers() { Polygon::setupBuffers(); }

void ArcPolygon::generateSegments() {
  vertices.clear(); // Limpa vértices existentes

  // Adiciona o centro (necessário para GL_TRIANGLE_FAN)
  vertices.push_back(center.x);
  vertices.push_back(center.y);
  vertices.push_back(0.0f);

  // Adiciona o centro se for preenchido
  if (isFilled) {
    vertices.push_back(center.x); // x
    vertices.push_back(center.y); // y
    vertices.push_back(.0f);      // z
  }

  // Gera os vértices do arco
  for (int i = 0; i <= segments; ++i) {
    // Interpola o ângulo atual entre start e end
    const float t = static_cast<float>(i) / static_cast<float>(segments);
    const float currentAngle = startAngle + t * (endAngle - startAngle);

    // Calcula as coordenadas do vértice
    vertices.push_back(center.x + radius * cosf(currentAngle)); // X
    vertices.push_back(center.y + radius * sinf(currentAngle)); // Y
    vertices.push_back(0.0f);                                   // Z
  }
}
