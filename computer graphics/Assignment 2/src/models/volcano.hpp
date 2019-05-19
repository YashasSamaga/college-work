#ifndef INCLUDE_MODELS_VOLCANO_HPP
#define INCLUDE_MODELS_VOLCANO_HPP

#include "model.hpp"

class Volcano : public ICollision, public IStatic {
public:
    Volcano();
    InteractionOutput interact(const InteractionInput& input);

    collision_type check_collision(const collision_box<GLfloat>& box) const;
};

#endif /* INCLUDE_MODELS_VOLCANO_HPP */
