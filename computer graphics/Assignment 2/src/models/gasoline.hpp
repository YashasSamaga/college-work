#ifndef INCLUDE_MODELS_GASOLINE_HPP
#define INCLUDE_MODELS_GASOLINE_HPP

#include "model.hpp"

class Gasoline : public ICollectable {
public:
    Gasoline();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_GASOLINE_HPP */