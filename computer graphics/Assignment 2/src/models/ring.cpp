#include "ring.hpp"
#include "../tools/objloader.hpp"

Ring::Ring() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 15.0f;

    std::vector<GLfloat> vertices;
    assert(load_object("../resources/ring.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i += 3) {
        color_data_buffer[i] = float(i)/vertices.size();
        color_data_buffer[i+1] = float(i)/vertices.size() * 0.5;
        color_data_buffer[i+2] = 0;
    }

    object = create3DObject(GL_TRIANGLES, 
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

InteractionOutput Ring::interact(const InteractionInput& input){
    if(state.active == 0)
        return {};

    float delta = 180 - std::abs(std::abs(input.rotation.y - rotation.y) - 180); ;
    if(delta > 30)
        return {};
    
    state.active = 0;

    InteractionOutput output;
    output.score = 100;
    return output;
}

Ring::collision_type Ring::check_collision(const collision_box<GLfloat>& box) const {
    return glm::length(position - glm::vec3(box.x, box.y, box.z)) < 25.0 ?
           Ring::collision_type::top : Ring::collision_type::none;
}
