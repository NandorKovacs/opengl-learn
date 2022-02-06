#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define numVAOs 1

GLuint renderingProg;
GLuint vao[numVAOs];

std::string readShaderSource(std::string fileName) {
  std::ifstream ifs{fileName};
  std::ostringstream oss;

  while (ifs) {
    std::string s;
    getline(ifs, s);
    oss << s << std::endl;
  }
  return oss.str();
}

bool checkOpenGLError() {
  bool foundError = false;
  int glErr = glGetError();
  while (glErr != GL_NO_ERROR) {
    std::cerr << "glError: " << gluErrorString(glErr)
              << "| error code: " << glErr << std::endl;
    foundError = true;
    glErr = glGetError();
  }

  return foundError;
}

GLuint createShaderProg() {
  const char* vshaderSource =
      "#version 330 \n"
      "void main(void) \n"
      "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
  std::string strFshaderSource = readShaderSource("fshader-box_border.glsl");
  const char* fshaderSource = strFshaderSource.c_str();

  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
  checkOpenGLError();

  glShaderSource(vShader, 1, &vshaderSource, NULL);
  glShaderSource(fShader, 1, &fshaderSource, NULL);

  checkOpenGLError();

  glCompileShader(vShader);
  glCompileShader(fShader);

  checkOpenGLError();

  GLuint vfProgram = glCreateProgram();

  checkOpenGLError();

  glAttachShader(vfProgram, vShader);
  glAttachShader(vfProgram, fShader);

  checkOpenGLError();

  glLinkProgram(vfProgram);
  checkOpenGLError();
  return vfProgram;
}

void init(GLFWwindow* window) {
  renderingProg = createShaderProg();
  glGenVertexArrays(numVAOs, vao);
  glBindVertexArray(vao[0]);
  glEnable(GL_PROGRAM_POINT_SIZE);
};

void display(GLFWwindow* window, double current_time) {
  glUseProgram(renderingProg);
  glPointSize(30.0f);
  glDrawArrays(GL_POINTS, 0, 1);
}

int main(int argc, char* argv[]) {
  glewExperimental = true;
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  checkOpenGLError();

  GLFWwindow* window = glfwCreateWindow(600, 600, "red_window", NULL, NULL);
  const char* glfwErr;
  glfwGetError(&glfwErr);
  if (glfwErr) {
    std::cerr << "glfw error: " << glfwErr << std::endl;
  }
  checkOpenGLError();

  if (window == NULL) {
    std::cerr << "opengl window is null" << std::endl;
  }

  glfwMakeContextCurrent(window);

  checkOpenGLError();

  auto glewInitRc = glewInit();
  if (glewInitRc != GLEW_OK) {
    std::cerr << "glew error:" << glewGetErrorString(glewInitRc) << std::endl;

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
