#ifndef INCLUDE_MODELS_PLAYER_HPP
#define INCLUDE_MODELS_PLAYER_HPP

#include "../main.h"

#include "model.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>

struct key_state_t {
    bool W, A, S, D;
    bool Q, E;
    bool up, down;
    bool space;
    bool lshift;
    bool lctrl, lalt;
    bool lbutton, rbutton;
};

class Player {
public:
    Player();
    void draw(glm::mat4 VP);

    void input(key_state_t keys);
    void tick(const std::vector<std::shared_ptr<IModel>>& models);

    void set_position(glm::vec3 position) { this->position = position; }
    auto get_position() const { return position; }

    auto get_velocity() const { return velocity; }

    auto get_rotation() const { return rotation; }

    auto get_fuel() const { return fuel; }
    auto set_fuel(float fuel) { this->fuel = fuel; }

    void give_score(int delta) { score += delta; }
    int get_score() const { return score; }

private:
    void process_interaction(const InteractionOutput& interaction);

    glm::vec3 position;
    struct {
        glm::vec3 global;
        glm::vec3 local;
    } rotation;
    
    glm::vec3 scale;
    glm::vec3 size;

    struct {
        glm::vec3 translational;
        glm::vec3 rotational;  
    } velocity;

    float fuel;
    int score;
    
    VAO *object;  
};

#endif /* INCLUDE_MODELS_PLAYER_HPP */
