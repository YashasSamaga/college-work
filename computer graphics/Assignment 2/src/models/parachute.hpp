#ifndef INCLUDE_MODELS_PARACHUTE_HPP
#define INCLUDE_MODELS_PARACHUTE_HPP

#include "model.hpp"
#include <vector>

class Parachute : public ICoalesce, public IDynamic {
public:
    Parachute();
    void tick();
    InteractionOutput interact(const InteractionInput& input);

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }
};

#endif /* INCLUDE_MODELS_PARACHUTE_HPP */