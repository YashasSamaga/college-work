#ifndef INCLUDE_MODELS_DESTROYERE_HPP
#define INCLUDE_MODELS_DESTROYERE_HPP

#include "model.hpp"

class DestroyerE : public ICollision, public IStatic {
public:
    DestroyerE();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_DESTROYERE_HPP */
