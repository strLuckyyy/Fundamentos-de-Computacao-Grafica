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

void StarPolygon::setupBuffers() { Polygon::setupBuffers(); }


void StarPolygon::generateSegments() {
  vertices.clear();

  // sem implementação ainda
}

