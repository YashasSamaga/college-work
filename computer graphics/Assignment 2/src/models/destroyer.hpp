#ifndef INCLUDE_MODELS_DESTROYER_HPP
#define INCLUDE_MODELS_DESTROYER_HPP

#include "model.hpp"

class Destroyer : public ICollision, public IStatic {
public:
    Destroyer();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_DESTROYER_HPP */
