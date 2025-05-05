//
// Created by abraa on 5/4/2025.
//

#include "../../include/polygons/SimplePolygon.h"

#include <cmath>

SimplePolygon::SimplePolygon(const float x, const float y, const float radius, const int segments, const bool filled)
  : Polygon(x, y, radius, segments, filled) {

  SimplePolygon::generateSegments();
  setupBuffers();
}

void SimplePolygon::updateGeometry(const float newRadius,
                                   const int newSegments) {
  radius = newRadius;
  segments = newSegments;

  // Reconfigura os buffers com os novos parâmetros
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  setupBuffers();
}

void SimplePolygon::setupBuffers() { Polygon::setupBuffers(); }

void SimplePolygon::generateSegments() {
  // Limpa vértices anteriores
  vertices.clear();

  // Centralizando
  vertices.push_back(center.x);
  vertices.push_back(center.y);
  vertices.push_back(.0f);


  // Adiciona o centro se for preenchido
  if (isFilled) {
    vertices.push_back(center.x); // x
    vertices.push_back(center.y); // y
    vertices.push_back(.0f); // z
  }

  // Gera os vértices do círculo
  for (int i = 0; i <= segments; ++i) {
    constexpr float PI = 3.141592653589793f;
    const float theta =
        2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);

    vertices.push_back(center.x + radius * cosf(theta));
    vertices.push_back(center.y + radius * sinf(theta));
    vertices.push_back(.0f);                 // z
  }
}

