#include "golden_coin.hpp"

GoldenCoin::GoldenCoin() {
    size = glm::vec3(1.0f, 1.0f, 1.0f);
    scale = glm::vec3(0.1f, 0.1f, 1.0f);

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

InteractionOutput GoldenCoin::interact(const InteractionInput& input) {
    state.active = 0;

    InteractionOutput output;
    output.score = 30;
    return output;
}