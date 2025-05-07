//
// Created by abraa on 5/3/2025.
//
/*
Desenhe uma espiral
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include <polygons/SpiralPolygon.h>

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
const string TITLE = "Exercise 8";

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
GLuint setupShader();

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_SAMPLES, 8); // anti serrilhado

  // Criação da janela GLFW
  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, TITLE.c_str(), nullptr, nullptr);
  if (!window)
  {
    std::cerr << "Falha ao criar a janela GLFW" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

  // GLAD: carrega todos os ponteiros d funções da OpenGL
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
  {
    std::cerr << "Falha ao inicializar GLAD" << std::endl;
    return -1;
  }

  // Obtendo as informações de versão
  const GLubyte *renderer = glGetString(GL_RENDERER); /* get renderer string */
  const GLubyte *version = glGetString(GL_VERSION);	/* version as a string */
  cout << "Renderer: " << renderer << endl;
  cout << "OpenGL version supported " << version << endl;

  // Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  // Shader
  const GLuint shaderID = setupShader();

  // Espiral
  auto spiral = SpiralPolygon(0, 0, 500, 5.f, .0f, .01f, .115f);
  spiral.setColor(1.f, 0.f, 0.f, 0.f);

  // LOOP
  double prev_s = glfwGetTime();
  double title_countdown_s = .1f;

  while (!glfwWindowShouldClose(window)) {
    // FPS Title
    {
      const double curr_s = glfwGetTime();
      const double elapsed_s = curr_s - prev_s;
      prev_s = curr_s;

      // Exibe o FPS, mas não a cada frame, para evitar oscilações excessivas.
      title_countdown_s -= elapsed_s;
      if (title_countdown_s <= 0.0 && elapsed_s > 0.0)
      {
        const double fps = 1.0 / elapsed_s;

        // Cria uma string e define o FPS como título da janela.
        char tmp[256];
        sprintf(tmp, "Ex-8 -- Abrahao\tFPS %.2lf", fps);
        glfwSetWindowTitle(window, tmp);

        title_countdown_s = 0.1; // Reinicia o temporizador para atualizar o título periodicamente.
      }
    }

    glfwPollEvents();
    glClearColor(.1f, .1f, .1f, 1.0f); // cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderID);

    // Draw Call
    spiral.draw(shaderID);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
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