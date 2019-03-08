#include "dragon.hpp"

Dragon::Dragon() {
    size = glm::vec3(2.0f, 4.0f, 2.0f);
    scale = glm::vec3(0.5f, 0.5f, 0.5f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* face */
        0.0f, 1.0f + 1.0, 0.0f,
        0.71f, 0.71f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,
        
        0.71f, 0.71f + 1.0, 0.0f,
        1.0f, 0.0f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        1.0f, 0.0f + 1.0, 0.0f,
        0.71f, -0.71f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        0.71f, -0.71f + 1.0, 0.0f,
        0.0f, -1.0f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        0.0f, -1.0f + 1.0, 0.0f,
        -0.71f, -0.71f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        -0.71f, -0.71f + 1.0, 0.0f,
        -1.0f, 0.0f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        -1.0f, 0.0f + 1.0, 0.0f,
        -0.71f, 0.71f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        -0.71f, 0.71f + 1.0, 0.0f,
        0.0f, 1.0f + 1.0, 0.0f,
        0.0f, 0.0f + 1.0, 0.0f,

        /* body */
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, -2.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, -2.0f, 0.0f,
        1.0f, -2.0f, 0.0f,
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),

        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

void Dragon::tick() {
    tick_count++;
    if(tick_count % 300) {
        /* fire ice balls */
    }
}

InteractionOutput Dragon::interact(const InteractionInput& input) {
    state.active = 0;
    
    InteractionOutput output;
    output.kill = true;
    return output;
}