#ifndef INCLUDE_LEVEL_HPP
#define INCLUDE_LEVEL_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern glm::vec3 get_position();

extern void initLevel();
extern void levelDraw(GLFWwindow* window, glm::mat4 VP);

#endif