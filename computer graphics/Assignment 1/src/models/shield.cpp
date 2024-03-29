#include "shield.hpp"

Shield::Shield() {
    size = glm::vec3(0.5f, 2.0f, 2.0f);
    scale = glm::vec3(0.25f, 0.5f, 0.5f);
    
    static const GLfloat vertex_buffer_data[] = {
        /* top triangles */
        -0.25f, 1.0f, 0.0f,
        -0.25f, -1.0f, 0.0f,
        0.25f, 1.0f, 0.0f,

        -0.25f, -1.0f, 0.0f,
        0.25f, -1.0f, 0.0f,
        0.25f, 1.0f, 0.0f,
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_MAROON_3f),
        REPEAT3(COLOR_MAROON_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}