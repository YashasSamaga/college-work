#ifndef INCLUDE_MODELS_FIRELINE_HPP
#define INCLUDE_MODELS_FIRELINE_HPP

#include "model.hpp"

class Fireline : public ICollision, public IStatic {
public:
    Fireline();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_FIRELINE_HPP */
