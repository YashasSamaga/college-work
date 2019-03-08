#ifndef INCLUDE_MODELS_ICEBALL_HPP
#define INCLUDE_MODELS_ICEBALL_HPP

#include "model.hpp"

class Iceball : public ICollision, public IDynamic {
public:
    Iceball();
    void tick();
    InteractionOutput interact(const InteractionInput& input);

    void reset() { tick_count = 0; }

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }

private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_ICEBALL_HPP */
