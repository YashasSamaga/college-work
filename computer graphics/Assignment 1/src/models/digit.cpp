#include "digit.hpp"

static const GLfloat default_vertex_buffer_data[] = {
    /* top-most */
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f,  0.8f, 0.0f,

    -1.0f, 1.0f, 0.0f,
    -1.0f,  0.8f, 0.0f,
    1.0f,  0.8f, 0.0f,

    /* top left */
    -1.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    - 0.8f, 0.0f, 0.0f,

    -1.0f, 1.0f, 0.0f,
    - 0.8f, 1.0f, 0.0f,
    - 0.8f, 0.0f, 0.0f,

    /* top right */
    1.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
     0.8f, 0.0f, 0.0f,

    1.0f, 1.0f, 0.0f,
     0.8f, 1.0f, 0.0f,
     0.8f, 0.0f, 0.0f,

    /* middle */
    -1.0f,  0.10f, 0.0f,
    1.0f,  0.10f, 0.0f,
    1.0f, - 0.10f, 0.0f,

    -1.0f,  0.10f, 0.0f,
    -1.0f, - 0.10f, 0.0f,
    1.0f, - 0.10f, 0.0f,

    /* bottom left */
    -1.0f, -1.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    - 0.8f, 0.0f, 0.0f,

    -1.0f, -1.0f, 0.0f,
    - 0.8f, -1.0f, 0.0f,
    - 0.8f, 0.0f, 0.0f,

    /* bottom right */
    1.0f, -1.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
     0.8f, 0.0f, 0.0f,

    1.0f, -1.0f, 0.0f,
     0.8f, -1.0f, 0.0f,
     0.8f, 0.0f, 0.0f,

    /* bottom-most */
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, - 0.8f, 0.0f,

    -1.0f, -1.0f, 0.0f,
    -1.0f, - 0.8f, 0.0f,
    1.0f, - 0.8f, 0.0f        
};

static const GLfloat default_vertex_color_data[sizeof(default_vertex_buffer_data)/sizeof(GLfloat)] = {
    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f)
};

Digit::Digit() {
    size = glm::vec3(2.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.1f, 0.2f, 0.1f);

    vertex_color_data.resize(sizeof(default_vertex_buffer_data)/sizeof(GLfloat));
    std::copy(std::begin(default_vertex_color_data), std::end(default_vertex_color_data),
              std::begin(vertex_color_data));

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(default_vertex_buffer_data)/sizeof(GLfloat)/3,
                            default_vertex_buffer_data,
                            vertex_color_data.data(),
                            GL_FILL);
}

void Digit::set_digit(char digit) {
    assert(digit >= 0 && digit < 10);

    static const char activations[] = {
        0b01110111,
        0b00010010,
        0b01011101,
        0b01101101,
        0b00101110,
        0b01101011,
        0b01111010,
        0b00100101,
        0b01111111,
        0b01101111
    };

    std::copy(std::begin(default_vertex_color_data), std::end(default_vertex_color_data),
              std::begin(vertex_color_data));

    char segments = activations[digit];
    for(int i = 0; i < 7; i++) {        
        if(segments & (1 << i)) {
            auto color = NORMALIZE_COLOR(COLOR_DARKGREY);
            for(int j = 0; j < 6; j++) {
                vertex_color_data[i * 18 + j * 3 + 0] = color.r;
                vertex_color_data[i * 18 + j * 3 + 1] = color.g;
                vertex_color_data[i * 18 + j * 3 + 2] = color.b;
            }
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, object->ColorBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(default_vertex_buffer_data), vertex_color_data.data());
}