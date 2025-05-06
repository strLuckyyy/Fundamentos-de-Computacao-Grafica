//
// Created by abraa on 5/5/2025.
//

#include <algorithm>
#include <cmath>
#include <polygons/StarPolygon.h>

StarPolygon::StarPolygon(const float x, const float y, const float radius,
  const int points, const bool filled, const float innerRadius)
   : Polygon(x, y, radius, points, filled), innerRadius(innerRadius) {

  generateSegments();
  setupBuffers();
}

void StarPolygon::draw(const GLuint colorProgram) const
{
    const GLint colorLoc = glGetUniformLocation(colorProgram, "inputColor");

    glUniform4fv(colorLoc, 1, color);
    glLineWidth(2.0f);
    glBindVertexArray(VAO);

    if (isFilled) {
        glDrawArrays(GL_TRIANGLE_FAN, 0, segments * 2);
    } else {
        glDrawArrays(GL_LINE_LOOP, 1, segments * 2);
    }

    glBindVertexArray(0);
}

void StarPolygon::setupBuffers() { Polygon::setupBuffers(); }

void StarPolygon::generateSegments() {
    vertices.clear();
    constexpr float PI = M_PI;
    const float angleStep = 2.0f * PI / static_cast<float>(segments * 2); // 10 passos para 5 pontas
    innerRadius = radius * innerRadius;

    for (int i = 0; i < segments * 2; i++) {
        const float angle = angleStep * static_cast<float>(i) - PI / 2.f;
        const float r = (i % 2 == 0) ? innerRadius : radius;

        vertices.push_back(center.x + r * cosf(angle)); // X
        vertices.push_back(center.y + r * sinf(angle)); // Y
        vertices.push_back(0.0f);                      // Z
    }

    // Fecha o loop (conecta o último ao primeiro vértice)
    vertices.push_back(vertices[0]);
    vertices.push_back(vertices[1]);
    vertices.push_back(vertices[2]);

    if (isFilled) {
        vertices.push_back(center.x);
        vertices.push_back(center.y);
        vertices.push_back(0.0f);
    }
}
