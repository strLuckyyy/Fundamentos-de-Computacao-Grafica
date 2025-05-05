//
// Created by abraa on 5/4/2025.
//

#ifndef COMPLEX_POLYGON_H
#define COMPLEX_POLYGON_H
#pragma once

#include "Polygon.h"

class ArcPolygon final : public Polygon {
public:
  ArcPolygon(float x, float y, float radius, bool filled, GLfloat startAngle, GLfloat endAngle);

private:
  // Propriedades especiais
  GLfloat startAngle;
  GLfloat endAngle;

  // Metodos
  void setupBuffers() override;
  void generateSegments() override;
};

#endif //COMPLEX_POLYGON_H
