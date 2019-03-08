#include <iostream>

#include "wall.hpp"

Wall::Wall() {
    size = glm::vec3(20.0f, 20.0f, 1.0f);

    scale = glm::vec3(0.4f, 0.3f, 1.0f);

    static GLfloat vertex_buffer_data[] = {
        /* background */
        -10.0f, 10.0f, 0.0f,
        10.0f, 10.0f, 0.0f,
        10.0f, -10.0f, 0.0f,

        -10.0f, 10.0f, 0.0f,
        -10.0f, -10.0f, 0.0f,
        10.0f, -10.0f, 0.0f,

        /* left block */
        -8.0f, 8.0f, 0.0f,
        -2.0f, 8.0f, 0.0f,
        -2.0f, -8.0f, 0.0f,

        -8.0f, 8.0f, 0.0f,
        -8.0f, -8.0f, 0.0f,
        -2.0f, -8.0f, 0.0f,

        /* left block */
        2.0f, 8.0f, 0.0f,
        8.0f, 8.0f, 0.0f,
        8.0f, -8.0f, 0.0f,

        2.0f, 8.0f, 0.0f,
        2.0f, -8.0f, 0.0f,
        8.0f, -8.0f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_BLACK_3f),
        REPEAT3(COLOR_BLACK_3f),

        REPEAT3(COLOR_DARKGREY_3f),
        REPEAT3(COLOR_DARKGREY_3f),

        REPEAT3(COLOR_DARKGREY_3f),
        REPEAT3(COLOR_DARKGREY_3f),
    };

    object = create3DObject(GL_TRIANGLES, 
                                  sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                                  vertex_buffer_data,
                                  vertex_color_data,
                                  GL_FILL);
}

InteractionOutput Wall::interact(const InteractionInput& input) {
    InteractionOutput output;
    output.stop = true;
    return output;
}