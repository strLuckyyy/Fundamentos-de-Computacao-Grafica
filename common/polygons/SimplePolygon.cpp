//
// Created by abraa on 5/4/2025.
//

#include "../../include/polygons/SimplePolygon.h"

#include <cmath>

SimplePolygon::SimplePolygon(const float x, const float y, const float radius, const int segments, const bool filled)
  : Polygon(x, y, radius, segments, filled) {

  SimplePolygon::generateSegments();
  SimplePolygon::setupBuffers();
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

void SimplePolygon::generateSegments() {
  Polygon::generateSegments();

  for (int i = 0; i <= segments; ++i) {
    constexpr float PI = 3.141592653589793f;
    const float theta =
        2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);

    vertices.push_back(center.x + radius * cosf(theta));
    vertices.push_back(center.y + radius * sinf(theta));
    vertices.push_back(.0f);                 // z
  }
}

void SimplePolygon::setupBuffers() { Polygon::setupBuffers(); }
