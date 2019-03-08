#ifndef INCLUDE_MODELS_FLOOR_HPP
#define INCLUDE_MODELS_FLOOR_HPP

#include "model.hpp"

class Floor : public ICollision, public IStatic {
public:
    Floor();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_FLOOR_HPP */
