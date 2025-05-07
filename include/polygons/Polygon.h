//
// Created by abraa on 5/4/2025.
//

#ifndef POLYGON_H
#define POLYGON_H
#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "glm/vec2.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class Polygon {
public:
  Polygon(float x, float y, float radius, int segments, bool filled);
  virtual ~Polygon();

  void setColor(float r, float g, float b, float a);
  void setCenter(glm::vec2 newCenter);

  // Metodo que desenha a forma na tela
  virtual void draw(GLuint colorProgram) const;

protected:
  // Propriedades do polígono
  glm::vec2 center;
  float radius;
  int segments;
  bool isFilled;

  // Cor do círculo (RGBA)
  float color[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // Branco por padrão

  // Buffers OpenGL
  GLuint VAO, VBO;
  std::vector<float> vertices;

  // BUFFERS
  virtual void setupBuffers();

  // POLYGON
  virtual void generateSegments();
};

#endif //POLYGON_H
