#ifndef INCLUDE_MODELS_BRONZE_COIN_HPP
#define INCLUDE_MODELS_BRONZE_COIN_HPP

#include "model.hpp"

class BronzeCoin : public ICollision, public IStatic {
public:
    BronzeCoin();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_BRONZE_COIN_HPP */
