#include "volcano.hpp"
#include "../tools/objloader.hpp"

Volcano::Volcano() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 15.0f;
    
    std::vector<GLfloat> vertices;
    assert(load_object("../resources/volcano.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i+=3) {
        color_data_buffer[i] = float(i)/vertices.size();
        color_data_buffer[i+1] = 0.0f;
        color_data_buffer[i+2] = 0.0f;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

InteractionOutput Volcano::interact(const InteractionInput& input) {
    InteractionOutput output;
    output.kill = true;
    return output;
}

Volcano::collision_type Volcano::check_collision(const collision_box<GLfloat>& box) const {
    return glm::length(glm::vec3(position.x, position.z, 0.0f) - glm::vec3(box.x, box.z, 0.0f)) < 150.0 ?
           Volcano::collision_type::top : Volcano::collision_type::none;
}
