//
// Created by abraa on 5/3/2025.
//
/*
Desenhe uma espiral
*/

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;


// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
auto *vertexShaderSource = R"(
 #version 400
 layout (location = 0) in vec3 position;
 void main()
 {
	 gl_Position = vec4(position.x, position.y, position.z, 1.0);
 }
 )";

// Código fonte do Fragment Shader (em GLSL): ainda hardcoded
auto *fragmentShaderSource = R"(
 #version 400
 uniform vec4 inputColor;
 out vec4 color;
 void main()
 {
	 color = inputColor;
 }
 )";

constexpr GLuint WIDTH = 800, HEIGHT = 800;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
GLuint setupShader();

int main() {

}

// SHADER //
enum ShaderType { VERTEX, FRAGMENT, PROGRAM };

// Mapeamento para strings
const unordered_map<ShaderType, std::string> ShaderTypeStrings = {
  {VERTEX, "VERTEX"},
  {FRAGMENT, "FRAGMENT"},
  {PROGRAM, "PROGRAM"}
};


void checkShader(const GLuint shader, const ShaderType &type) {
  GLint success;
  GLchar infoLog[512];

  if (type != PROGRAM) {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::"<< ShaderTypeStrings.at(type) <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return;
  }

  glGetShaderiv(shader, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::"<< ShaderTypeStrings.at(type) <<"::COMPILATION_FAILED\n" << infoLog << std::endl;
  }
}

GLuint setupShader() {

  const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
  checkShader(vertexShader, VERTEX);


  const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
  checkShader(fragmentShader, FRAGMENT);


  const GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  checkShader(shaderProgram, PROGRAM);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

// END SHADER //

// INPUTS //
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
// END INPUTS //