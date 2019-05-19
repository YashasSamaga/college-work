#include "meter.hpp"

static const GLfloat default_vertex_buffer_data[] = {
    -1.0f, 1.0f, -0.01f,
    -1.0f, -1.0f, -0.01f,
    1.0f, -1.0f, -0.01f,

    -1.0f, 1.0f, -0.01f,
    1.0f, 1.0f, -0.01f,
    1.0f, -1.0f, -0.01f,

    -1.0f, 0.0f, 0.0f, //19
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,

    -1.0f, 0.0f, 0.0f, //28
    1.0f, 0.0f, 0.0f, //31
    1.0f, -1.0f, 0.0f,
};

static const GLfloat default_vertex_color_data[sizeof(default_vertex_buffer_data)/sizeof(GLfloat)] = {
    REPEAT3(COLOR_WHITE_3f),
    REPEAT3(COLOR_WHITE_3f),

    REPEAT3(COLOR_GREEN_3f),
    REPEAT3(COLOR_GREEN_3f)
};

Meter::Meter() {
    size = glm::vec3(2.0f, 2.0f, 2.0f);
    scale = glm::vec3(0.25f, 2.0f, 1.0f);

    vertex_color_data.resize(sizeof(default_vertex_buffer_data)/sizeof(GLfloat));
    std::copy(std::begin(default_vertex_color_data), std::end(default_vertex_color_data),
              std::begin(vertex_color_data));

    vertex_data.resize(sizeof(default_vertex_buffer_data)/sizeof(GLfloat));
    std::copy(std::begin(default_vertex_buffer_data), std::end(default_vertex_buffer_data),
              std::begin(vertex_data));

    object = create3DObject(GL_TRIANGLES, 
                            sizeof(default_vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_data.data(),
                            vertex_color_data.data(),
                            GL_FILL);
}

void Meter::set_value(float value) {
    assert(value >= 0.0 && value <= 1.0);

    std::copy(std::begin(default_vertex_buffer_data), std::end(default_vertex_buffer_data),
              std::begin(vertex_data));

    vertex_data[19] =
    vertex_data[28] =
    vertex_data[31] = value * 2 - 1.0f;

    glBindBuffer(GL_ARRAY_BUFFER, object->VertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(default_vertex_buffer_data), vertex_data.data());

    //glBindBuffer(GL_ARRAY_BUFFER, object->ColorBuffer);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(default_vertex_buffer_data), vertex_color_data.data());
}