#ifndef INCLUDE_MODELS_METER_HPP
#define INCLUDE_MODELS_METER_HPP

#include "model.hpp"
#include <vector>


class Meter : public ICoalesce, public IStatic {
public:
    Meter();
    void set_value(float digit);

    auto get_offset() const { return offset; };
    void set_offset(const glm::vec3& offset) { this->offset = offset; }

private:
    glm::vec3 offset;

    std::vector<GLfloat> vertex_color_data;
    std::vector<GLfloat> vertex_data;
};

#endif /* INCLUDE_MODELS_METER_HPP */