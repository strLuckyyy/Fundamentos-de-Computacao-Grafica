//
// Created by abraa on 5/5/2025.
//

#ifndef STARPOLYGON_H
#define STARPOLYGON_H
#include "Polygon.h"

class StarPolygon final : public Polygon {
public:
  StarPolygon(float x, float y, float radius, int points, bool filled, float innerRadius);

private:
  float innerRadius;

  // Metodos
  void setupBuffers() override;
  void generateSegments() override;
};

#endif //STARPOLYGON_H
