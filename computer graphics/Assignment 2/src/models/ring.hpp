#ifndef INCLUDE_MODELS_RING_HPP
#define INCLUDE_MODELS_RING_HPP

#include "model.hpp"

class Ring : public ICollectable {
public:
    Ring();
    InteractionOutput interact(const InteractionInput& input);
    collision_type check_collision(const collision_box<GLfloat>& box) const;
};

#endif /* INCLUDE_MODELS_RING_HPP */