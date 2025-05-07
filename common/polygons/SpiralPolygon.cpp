//
// Created by abraa on 5/6/2025.
//

#include <algorithm>
#include <polygons/SpiralPolygon.h>

#include "glm/trigonometric.hpp"


SpiralPolygon::SpiralPolygon(const float x, const float y, const int steps, const float radius, const float startRadius, float radiusStep,
                             const float angleStep)
    : Polygon(x, y, radius, steps, false), startRadius(startRadius), radiusStep(radiusStep), angleStep(angleStep)
{
    SpiralPolygon::generateSegments();
    SpiralPolygon::setupBuffers();
}

void SpiralPolygon::draw(const GLuint colorProgram) const
{
    const GLint colorLoc = glGetUniformLocation(colorProgram, "inputColor");

    glUniform4fv(colorLoc, 1, color);
    glLineWidth(2.0f);
    glBindVertexArray(VAO);

    glDrawArrays(GL_LINE_STRIP, 1, segments / 3);

    glBindVertexArray(0);
}

void SpiralPolygon::generateSegments()
{
    Polygon::generateSegments();

    for (int i = 0; i < segments; ++i) {
        const float theta = angleStep * i;
        const float radius = startRadius + radiusStep * theta;

        vertices.push_back(center.x + radius * cosf(theta));
        vertices.push_back(center.y + radius * sinf(theta));
        vertices.push_back(0.0f);
    }
}

void SpiralPolygon::setupBuffers() { Polygon::setupBuffers(); }
