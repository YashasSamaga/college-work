#ifndef INCLUDE_MODELS_FIREBEAM_HPP
#define INCLUDE_MODELS_FIREBEAM_HPP

#include "model.hpp"

class Firebeam : public ICollision, public IDynamic {
public:
    Firebeam();
    void tick();
    InteractionOutput interact(const InteractionInput& input);
private:
    int tick_count;
};

#endif /* INCLUDE_MODELS_FIREBEAM_HPP */
