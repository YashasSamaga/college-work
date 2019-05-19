#ifndef INCLUDE_MODELS_BOMB_HPP
#define INCLUDE_MODELS_BOMB_HPP

#include "model.hpp"

class Bomb : public ICollision, public IDynamic {
public:
    Bomb();
    void tick();
    InteractionOutput interact(const InteractionInput& input);

    void enable() { state.active = 1; }
    void disable() { state.active = 0; }
    bool status() { return state.active; }

    void set(glm::vec3 origin, glm::vec3 _target) { position = origin; target = _target; }

private:
    glm::vec3 target;
};

#endif /* INCLUDE_MODELS_BOMB_HPP */