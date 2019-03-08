#ifndef INCLUDE_MODELS_BOOMERANG_HPP
#define INCLUDE_MODELS_BOOMERANG_HPP

#include "model.hpp"

class Boomerang : public ICollision, public IDynamic {
public:
    Boomerang();
    void tick();
    InteractionOutput interact(const InteractionInput& input);

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }
private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_BOOMERANG_HPP */
