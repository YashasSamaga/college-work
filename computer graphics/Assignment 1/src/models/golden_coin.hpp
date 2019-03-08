#ifndef INCLUDE_MODELS_GOLDEN_COIN_HPP
#define INCLUDE_MODELS_GOLDEN_COIN_HPP

#include "model.hpp"

class GoldenCoin : public ICollision, public IStatic {
public:
    GoldenCoin();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_GOLDEN_COIN_HPP */
