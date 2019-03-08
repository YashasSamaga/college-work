#ifndef INCLUDE_MODELS_DRAGON_HPP
#define INCLUDE_MODELS_DRAGON_HPP

#include "model.hpp"

class Dragon : public ICollision, public IDynamic {
public:
    Dragon();
    InteractionOutput interact(const InteractionInput& input);

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }

    void tick();
private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_DRAGON_HPP */
