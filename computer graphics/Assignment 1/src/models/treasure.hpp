#ifndef INCLUDE_MODELS_TREASURE_COIN_HPP
#define INCLUDE_MODELS_TREASURE_COIN_HPP

#include "model.hpp"

class Treasure : public ICollision, public IDynamic {
public:
    Treasure();
    void tick();
    InteractionOutput interact(const InteractionInput& input);
private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_TREASURE_COIN_HPP */
