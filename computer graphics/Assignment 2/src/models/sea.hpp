#ifndef INCLUDE_MODELS_SEA_HPP
#define INCLUDE_MODELS_SEA_HPP

#include "model.hpp"

class Sea : public ICollision, public IStatic {
public:
    Sea();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_SEA_HPP */
