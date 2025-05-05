//
// Created by abraa on 5/4/2025.
//

#ifndef SIMPLEPOLYGON_H
#define SIMPLEPOLYGON_H
#pragma once
#include "Polygon.h"

class SimplePolygon final : public Polygon {
public:
  SimplePolygon(float x, float y, float radius, int segments, bool filled);

  void updateGeometry(float newRadius, int newSegments);

private:
  void setupBuffers() override;
  void generateSegments() override;
};

#endif //SIMPLEPOLYGON_H
