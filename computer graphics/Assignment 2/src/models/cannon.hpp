#ifndef INCLUDE_MODELS_CANNON_HPP
#define INCLUDE_MODELS_CANNON_HPP

#include "model.hpp"

class Cannon : public ICollision, public IDynamic {
public:
    Cannon();
    void tick();
    InteractionOutput interact(const InteractionInput& input);

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }

    void set(glm::vec3 origin, glm::vec3 _target) { position = origin; target = _target; }

private:
    glm::vec3 target;
};

#endif /* INCLUDE_MODELS_CANNON_HPP */