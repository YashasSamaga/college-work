#include "sea.hpp"

Sea::Sea() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10000.0f;
    
    static const GLfloat vertex_buffer_data[] = {
        -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 1.0f,
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_SEA_3f),
        REPEAT3(COLOR_SEA_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

InteractionOutput Sea::interact(const InteractionInput& input) {
    InteractionOutput output;
    return output;
}