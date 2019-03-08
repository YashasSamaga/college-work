#ifndef INCLUDE_MODELS_LIFE_HPP
#define INCLUDE_MODELS_LIFE_HPP

#include "model.hpp"

class Life : public ICollision, public IDynamic {
public:
    Life();
    void tick();
    InteractionOutput interact(const InteractionInput& input);
private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_LIFE_HPP */
