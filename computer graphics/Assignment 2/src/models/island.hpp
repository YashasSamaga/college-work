#ifndef INCLUDE_MODELS_ISLAND_HPP
#define INCLUDE_MODELS_ISLAND_HPP

#include "model.hpp"

class Island : public ICollision, public IDynamic {
public:
    Island();
    void tick();
    void sink() { destroyed = true; }
    bool status() { return !destroyed; }
    InteractionOutput interact(const InteractionInput& input);

private:
    bool destroyed;
};

#endif /* INCLUDE_MODELS_ISLAND_HPP */
