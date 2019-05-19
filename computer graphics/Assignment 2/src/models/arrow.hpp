#ifndef INCLUDE_MODELS_ARROW_HPP
#define INCLUDE_MODELS_ARROW_HPP

#include "model.hpp"
#include <vector>


class Arrow : public ICoalesce, public IStatic {
public:
    Arrow();
    
    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }
};

#endif /* INCLUDE_MODELS_ARROW_HPP */