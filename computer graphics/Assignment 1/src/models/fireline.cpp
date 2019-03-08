#include "fireline.hpp"

Fireline::Fireline() {
    size = glm::vec3(8.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.2f, 0.2f, 0.2f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* line */
        -2.5f, 0.5f, 0.0f,
        2.5f, 0.5f, 0.0f,
        2.5f, -0.5f, 0.0f,

        -2.5f, 0.5f, 0.0f,
        -2.5f, -0.5f, 0.0f,
        2.5f, -0.5f, 0.0f,

        /* left cylinder */
        0.0f - 3, 1.0f, 0.0f,
        0.71f - 3, 0.71f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,
        
        0.71f - 3, 0.71f, 0.0f,
        1.0f - 3, 0.0f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        1.0f - 3, 0.0f, 0.0f,
        0.71f - 3, -0.71f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        0.71f - 3, -0.71f, 0.0f,
        0.0f - 3, -1.0f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        0.0f - 3, -1.0f, 0.0f,
        -0.71f - 3, -0.71f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        -0.71f - 3, -0.71f, 0.0f,
        -1.0f - 3, 0.0f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        -1.0f - 3, 0.0f, 0.0f,
        -0.71f - 3, 0.71f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        -0.71f - 3, 0.71f, 0.0f,
        0.0f - 3, 1.0f, 0.0f,
        0.0f - 3, 0.0f, 0.0f,

        /* right */
        0.0f + 3, 1.0f, 0.0f,
        0.71f + 3, 0.71f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,
        
        0.71f + 3, 0.71f, 0.0f,
        1.0f + 3, 0.0f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,

        1.0f + 3, 0.0f, 0.0f,
        0.71f + 3, -0.71f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,

        0.71f + 3, -0.71f, 0.0f,
        0.0f + 3, -1.0f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,

        0.0f + 3, -1.0f, 0.0f,
        -0.71f + 3, -0.71f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,

        -0.71f + 3, -0.71f, 0.0f,
        -1.0f + 3, 0.0f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,

        -1.0f + 3, 0.0f, 0.0f,
        -0.71f + 3, 0.71f, 0.0f,
        0.0f + 3, 0.0f, 0.0f,

        -0.71f + 3, 0.71f, 0.0f,
        0.0f + 3, 1.0f, 0.0f,
        0.0f + 3, 0.0f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_ORANGE_3f),
        REPEAT3(COLOR_ORANGE_3f),

        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),

        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

InteractionOutput Fireline::interact(const InteractionInput& input) {
    state.active = 0;
    
    InteractionOutput output;
    output.kill = true;
    return output;
}