//
// Created by abraa on 5/5/2025.
//

#ifndef STARPOLYGON_H
#define STARPOLYGON_H
#include "Polygon.h"

class StarPolygon final : public Polygon {
public:
  StarPolygon(int x, int y, float radius, int segments, bool filled, int points, float innerRadius);

private:
  int points;
  float innerRadius;

  // Metodos
  void setupBuffers() override;
  void generateSegments() override;
};

#endif //STARPOLYGON_H
