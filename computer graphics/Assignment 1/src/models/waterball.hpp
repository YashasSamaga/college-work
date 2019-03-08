#ifndef INCLUDE_MODELS_WATERBALL_HPP
#define INCLUDE_MODELS_WATERBALL_HPP

#include "model.hpp"

class WaterBall : public ICoalesce, public IDynamic {
public:
    WaterBall();
    void tick();
    InteractionOutput interact(const InteractionInput& input);

    void reset() { tick_count = 0; }

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }

private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_WATERBALL_HPP */
