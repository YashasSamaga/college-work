#ifndef INCLUDE_MODELS_SHIELD_HPP
#define INCLUDE_MODELS_SHIELD_HPP

#include "model.hpp"

class Shield : public ICoalesce, public IStatic {
public:
    Shield();

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }
};

#endif /* INCLUDE_MODELS_SHIELD_HPP */
