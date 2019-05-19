#include "carrier.hpp"
#include "../tools/objloader.hpp"

Carrier::Carrier() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 100.0f;
    
    std::vector<GLfloat> vertices;
    assert(load_object("../resources/carrier.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i++) {
        color_data_buffer[i] = rand()/float(RAND_MAX);
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

void Carrier::tick() {

}

InteractionOutput Carrier::interact(const InteractionInput& input) {
    InteractionOutput output;
    return output;
}