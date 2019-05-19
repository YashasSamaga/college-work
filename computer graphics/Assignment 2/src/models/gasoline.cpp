#include "gasoline.hpp"
#include "../tools/objloader.hpp"
#include <iostream>
Gasoline::Gasoline() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;

    std::vector<GLfloat> vertices;
    assert(load_object("../resources/gasoline.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i += 3) {
        color_data_buffer[i] = float(i)/vertices.size();
        color_data_buffer[i+1] =
        color_data_buffer[i+2] = 0;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

InteractionOutput Gasoline::interact(const InteractionInput& input){
    if(state.active == 0)
        return {};
    
    state.active = 0;

    InteractionOutput output;
    output.fuel = 0.25;
    return output;
}