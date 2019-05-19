#ifndef INCLUDE_MODELS_CARRIER_HPP
#define INCLUDE_MODELS_CARRIER_HPP

#include "model.hpp"

class Carrier : public ICollision, public IDynamic {
public:
    Carrier();
    InteractionOutput interact(const InteractionInput& input);

    void tick();
};

#endif /* INCLUDE_MODELS_CARRIER_HPP */
