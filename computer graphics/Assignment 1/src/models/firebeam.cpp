#include "firebeam.hpp"

Firebeam::Firebeam() {
    size = glm::vec3(12.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.2f, 0.2f, 0.2f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* line */
        -4.5f, 0.5f, 0.0f,
        4.5f, 0.5f, 0.0f,
        4.5f, -0.5f, 0.0f,

        -4.5f, 0.5f, 0.0f,
        -4.5f, -0.5f, 0.0f,
        4.5f, -0.5f, 0.0f,

        /* left cylinder */
        0.0f - 5, 1.0f, 0.0f,
        0.71f - 5, 0.71f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,
        
        0.71f - 5, 0.71f, 0.0f,
        1.0f - 5, 0.0f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        1.0f - 5, 0.0f, 0.0f,
        0.71f - 5, -0.71f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        0.71f - 5, -0.71f, 0.0f,
        0.0f - 5, -1.0f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        0.0f - 5, -1.0f, 0.0f,
        -0.71f - 5, -0.71f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        -0.71f - 5, -0.71f, 0.0f,
        -1.0f - 5, 0.0f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        -1.0f - 5, 0.0f, 0.0f,
        -0.71f - 5, 0.71f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        -0.71f - 5, 0.71f, 0.0f,
        0.0f - 5, 1.0f, 0.0f,
        0.0f - 5, 0.0f, 0.0f,

        /* right */
        0.0f + 5, 1.0f, 0.0f,
        0.71f + 5, 0.71f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,
        
        0.71f + 5, 0.71f, 0.0f,
        1.0f + 5, 0.0f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,

        1.0f + 5, 0.0f, 0.0f,
        0.71f + 5, -0.71f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,

        0.71f + 5, -0.71f, 0.0f,
        0.0f + 5, -1.0f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,

        0.0f + 5, -1.0f, 0.0f,
        -0.71f + 5, -0.71f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,

        -0.71f + 5, -0.71f, 0.0f,
        -1.0f + 5, 0.0f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,

        -1.0f + 5, 0.0f, 0.0f,
        -0.71f + 5, 0.71f, 0.0f,
        0.0f + 5, 0.0f, 0.0f,

        -0.71f + 5, 0.71f, 0.0f,
        0.0f + 5, 1.0f, 0.0f,
        0.0f + 5, 0.0f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),

        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),

        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

void Firebeam::tick() {
    tick_count++;
    if((tick_count + 50)/100 % 2 == 0) {
        position.y += 0.05;
    } else {
        position.y -= 0.05;
    }    
}

InteractionOutput Firebeam::interact(const InteractionInput& input) {
    state.active = 0;
    
    InteractionOutput output;
    output.kill = true;
    return output;
}