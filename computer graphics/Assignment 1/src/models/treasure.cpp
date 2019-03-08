#include "treasure.hpp"

Treasure::Treasure() {
    size = glm::vec3(2.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.25f, 0.25f, 0.25f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* top */
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,

        -1.0f, 1.0f, 0.0f,
        -1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,

        /* box */
        -1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f,

        -1.0f, 0.5f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f        
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_BROWN_3f),
        REPEAT3(COLOR_BROWN_3f),

        REPEAT3(COLOR_GOLD_3f),
        REPEAT3(COLOR_GOLD_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

InteractionOutput Treasure::interact(const InteractionInput& input) {
    state.active = 0;

    InteractionOutput output;
    output.score = 250;
    return output;
}

void Treasure::tick() {
    tick_count++;
    if(tick_count/50 % 2 == 0) {
        position.y += 0.01;
        position.x += 0.05;
    } else {
        position.y -= 0.01;
        position.x -= 0.06;
        position.x -= 0.06;
    }    
}