#include "arrow.hpp"
#include "../tools/objloader.hpp"

Arrow::Arrow() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 25.0f;

    std::vector<GLfloat> vertices;
    assert(load_object("../resources/arrow.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i += 3) {
        color_data_buffer[i] = 255;
        color_data_buffer[i+1] =
        color_data_buffer[i+2] = 0;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}