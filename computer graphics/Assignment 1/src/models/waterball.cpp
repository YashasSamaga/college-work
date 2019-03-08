#include "waterball.hpp"

WaterBall::WaterBall() {
    size = glm::vec3(2.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.1f, 0.1f, 0.1f);
    
    static const GLfloat vertex_buffer_data[] = {
        0.0f, 1.0f, 0.0f,
        0.71f, 0.71f, 0.0f,
        0.0f, 0.0f, 0.0f,
        
        0.71f, 0.71f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.71f, -0.71f, 0.0f,
        0.0f, 0.0f, 0.0f,

        0.71f, -0.71f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        -0.71f, -0.71f, 0.0f,
        0.0f, 0.0f, 0.0f,

        -0.71f, -0.71f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f,
        -0.71f, 0.71f, 0.0f,
        0.0f, 0.0f, 0.0f,

        -0.71f, 0.71f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f)
    };

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

void WaterBall::tick() {
    if(state.active == 0)
        return;

    tick_count++;
    position.y -= 0.002;
    rotation.z += 1.0;

    if(tick_count < 300) {
        position.x += 0.03;
    } else {
        state.active = 0;
    }
}