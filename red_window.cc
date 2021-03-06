#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

void init(GLFWwindow* window){};

void display(GLFWwindow* window, double current_time) {
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char* argv[]) {
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }
  glfwWindowHint(GLFW_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);
  GLFWwindow* window = glfwCreateWindow(600, 600, "red_window", NULL, NULL);
  glfwMakeContextCurrent(window);
  if(glewInit() != GLEW_OK) {
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
