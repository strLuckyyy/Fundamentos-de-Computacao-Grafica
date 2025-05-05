//
// Created by abraa on 5/4/2025.
//

#ifndef POLYGON_H
#define POLYGON_H
#pragma once

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
  void draw(GLuint colorProgram) const;

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

  // Metodo para inicializar buffers
  virtual void setupBuffers();

  // Metodo para configuração da forma
  virtual void generateSegments() = 0;
};

#endif //POLYGON_H
