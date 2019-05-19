#include "destroyerE.hpp"
#include "../tools/objloader.hpp"

DestroyerE::DestroyerE() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
    
    std::vector<GLfloat> vertices;
    assert(load_object("../resources/destroyerE.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i+=3) {
        color_data_buffer[i+1] = rand()/float(RAND_MAX);
        color_data_buffer[i+1] = 0.0f;
        color_data_buffer[i+1] = 0.0f;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

InteractionOutput DestroyerE::interact(const InteractionInput& input) {
    InteractionOutput output;
    return output;
}