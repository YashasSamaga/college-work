#include "parachute.hpp"
#include "../tools/objloader.hpp"

Parachute::Parachute() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

    std::vector<GLfloat> vertices;
    assert(load_object("../resources/parachute.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i += 3) {
        color_data_buffer[i] = 0;
        color_data_buffer[i+1] = float(i)/vertices.size();
        color_data_buffer[i+2] = 0;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

void Parachute::tick() {
    position.z -= 0.25f;
}

InteractionOutput interact(const InteractionInput& input) {
    InteractionOutput output;
    output.score = 250;
}