#ifndef INCLUDE_LEVEL_HPP
#define INCLUDE_LEVEL_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern void initLevel();
extern void levelDraw(GLFWwindow* window, glm::mat4 VP);

extern void get_camera(glm::vec3& eye, glm::vec3& target, glm::vec3& up);

#endif /* INCLUDE_LEVEL_HPP */