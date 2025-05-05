//
// Created by abraa on 5/4/2025.
//

#include <cmath>
#include <polygons/Polygon.h>

Polygon::Polygon(const float x, const float y, const float radius,
                 const int segments, const bool filled)
    : center(x, y), radius(radius), segments(segments), isFilled(filled), VAO(0), VBO(0) { }

Polygon::~Polygon() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Polygon::setColor(const float r, const float g, const float b,
                       const float a) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
  color[3] = a;
}

void Polygon::setCenter(const glm::vec2 newCenter) {
  center = newCenter;
}

void Polygon::draw(const GLuint colorProgram) const {
  const GLint colorLoc = glGetUniformLocation(colorProgram, "inputColor");
  glUniform4fv(colorLoc, 1, color);

  glBindVertexArray(VAO);

  if (isFilled) {
    glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2); // +2 (centro + fechamento)
  } else {
    glDrawArrays(GL_LINE_LOOP, 1, segments + 1);
  }

  glBindVertexArray(0);
}

void Polygon::setupBuffers() {
  // Configura buffers OpenGL
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,
               static_cast<long>(vertices.size() * sizeof(float)),
               vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        static_cast<void *>(nullptr));
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
