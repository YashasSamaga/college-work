#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>

bool load_object(const std::string& path, std::vector<GLfloat> &vertices);
bool load_object(const std::string& path, std::vector<GLfloat> &vertices, glm::vec3& size);
