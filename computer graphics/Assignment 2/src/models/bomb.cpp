#include "bomb.hpp"
#include "../tools/objloader.hpp"

Bomb::Bomb() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.25f;

    std::vector<GLfloat> vertices;
    assert(load_object("../resources/bomb.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i += 3) {
        color_data_buffer[i] = 0;
        color_data_buffer[i+1] = 0.4 + 0.6 * float(i)/vertices.size();
        color_data_buffer[i+2] = 0;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

void Bomb::tick() {
    if(glm::length(position - target) < 10.0) {
        state.active = 0;
        return;
    }

    position += glm::normalize(target - position) * 0.1f;
}

InteractionOutput Bomb::interact(const InteractionInput& input) {
    return {};
}
