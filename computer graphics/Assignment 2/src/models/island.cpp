#include "island.hpp"
#include "../tools/objloader.hpp"

Island::Island() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 15.0f;

    destroyed = false;
    
    std::vector<GLfloat> vertices;
    assert(load_object("../resources/island.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i+=3) {
        color_data_buffer[i] = rand()/float(RAND_MAX);
        color_data_buffer[i+1] = rand()/float(RAND_MAX);
        color_data_buffer[i+2] = 0.0f;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

void Island::tick() {
    if(destroyed == true) {
        position.y -= 1.0f;
    }
}

InteractionOutput Island::interact(const InteractionInput& input) {
    InteractionOutput output;
    return output;
}