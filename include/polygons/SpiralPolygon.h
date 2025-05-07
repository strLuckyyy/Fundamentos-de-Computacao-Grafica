//
// Created by abraa on 5/6/2025.
//

#ifndef SPIRALPOLYGON_H
#define SPIRALPOLYGON_H
#pragma once
#include "Polygon.h"

class SpiralPolygon final : public Polygon
{
public:
    SpiralPolygon(float x, float y, int steps, float radius, float startRadius, float radiusStep,
    float angleStep);

    void draw(GLuint colorProgram) const;

private:
    float startRadius;
    float radiusStep;
    float angleStep; // lido em radianos

    void generateSegments() override;
    void setupBuffers() override;
};

#endif //SPIRALPOLYGON_H
