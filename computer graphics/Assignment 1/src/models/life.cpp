#include "life.hpp"

Life::Life() {
    size = glm::vec3(2.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.25f, 0.25f, 0.25f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* top triangles */
        -1.0f, 0.5f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,

        0.0f, 0.5f, 0.0f,
        0.5f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,

        /* base */
        -1.0f, 0.5f, 0.0f,
        0.0f, -1.0f, 0.0f,
        1.0f, 0.5f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
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

InteractionOutput Life::interact(const InteractionInput& input) {
    state.active = 0;

    InteractionOutput output;
    output.lives = 1;
    return output;
}

void Life::tick() {
    tick_count++;
    if(tick_count/200 % 2 == 0) {
        position.y += 0.005;
        position.x += 0.01;
    } else {
        position.y -= 0.005;
        position.x -= 0.012;
    }    
}