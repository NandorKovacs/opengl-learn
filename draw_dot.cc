#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define numVAOs 1

GLuint renderingProg;
GLuint vao[numVAOs];

// std::string readShaderSource(std::string fileName) {
//   std::ifstream ifs{fileName};
//   std::ostringstream oss;

//   while (ifs) {
//     std::string s;
//     getline(ifs, s);
//     oss << s << std::endl;
//   }
//   return oss.str();
// }

GLuint createShaderProg() {
  const char* vshaderSource =
      "#version 430 \n"
      "void main(void) \n"
      "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
  // std::string strFshaderSource = readShaderSource("fshader-box_border.glsl");
  const char* fshaderSource =
      "#version 430 \n"
      "out vec4 color; \n"
      "void main(void) \n"
      "{ color = vec4(0.0, 0.0, 1.0, 1.0); }";

  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vShader, 1, &vshaderSource, NULL);
  glShaderSource(fShader, 1, &fshaderSource, NULL);
  glCompileShader(vShader);
  glCompileShader(fShader);

  GLuint vfProgram = glCreateProgram();
  glAttachShader(vfProgram, vShader);
  glAttachShader(vfProgram, fShader);
  glLinkProgram(vfProgram);

  return vfProgram;
}

void init(GLFWwindow* window) {
  renderingProg = createShaderProg();
  glGenVertexArrays(numVAOs, vao);
  glBindVertexArray(vao[0]);
};

void display(GLFWwindow* window, double current_time) {
  glUseProgram(renderingProg);
  glPointSize(30.0f);
  glDrawArrays(GL_POINTS, 0, 1);
}

int main(int argc, char* argv[]) {
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }
  glfwWindowHint(GLFW_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);
  GLFWwindow* window = glfwCreateWindow(600, 600, "red_window", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (glewInit() != GLEW_OK) {
    exit(EXIT_FAILURE);
  }
  glfwSwapInterval(1);

  init(window);

  while (!glfwWindowShouldClose(window)) {
    display(window, glfwGetTime());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
