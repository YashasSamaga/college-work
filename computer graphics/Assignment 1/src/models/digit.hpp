#ifndef INCLUDE_MODELS_DIGIT_HPP
#define INCLUDE_MODELS_DIGIT_HPP

#include "model.hpp"
#include <vector>


class Digit : public ICoalesce, public IStatic {
public:
    Digit();
    void set_digit(char digit);

private:
    std::vector<GLfloat> vertex_color_data;
};

#endif /* INCLUDE_MODELS_DIGIT_HPP */