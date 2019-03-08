#include "floor.hpp"

Floor::Floor() {
    size = glm::vec3(20.0f, 1.0f, 1.0f);
    
    static const GLfloat vertex_buffer_data[] = {
        -10.0f, -0.5f, 0.0f,
        -10.0f, 0.5f, 0.0f,
        10.0f, -0.5f, 0.0f,

        -10.0f, 0.5f, 0.0f,
        10.0f, 0.5f, 0.0f,
        10.0f, -0.5f, 0.0f,
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_GREEN_3f),
        REPEAT3(COLOR_GREEN_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

InteractionOutput Floor::interact(const InteractionInput& input) {
    InteractionOutput output;
    output.stop = true;
    return output;
}