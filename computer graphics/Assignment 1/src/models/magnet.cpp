#include "magnet.hpp"

Magnet::Magnet() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(0.5f, 0.5f, 1.0f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* base */
        -1.0f, 1.0f, 0.0f,
        -0.5f, 1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,

        /* red */
        -0.5f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,

        -0.5f, 1.0f, 0.0f,
        -0.5, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,

        /* blue */
        -0.5f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        1.0f, -1.0f, 0.0f,

        -0.5f, -0.5f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_YELLOW_3f),
        REPEAT3(COLOR_YELLOW_3f),

        REPEAT3(COLOR_RED_3f),
        REPEAT3(COLOR_RED_3f),

        REPEAT3(COLOR_BLUE_3f),
        REPEAT3(COLOR_BLUE_3f),
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}