#ifndef INCLUDE_MODELS_MAGNET_HPP
#define INCLUDE_MODELS_MAGNET_HPP

#include "model.hpp"

class Magnet : public ICoalesce, public IStatic {
public:
    Magnet();
    
    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }
};

#endif /* INCLUDE_MODELS_MAGNET_HPP */
