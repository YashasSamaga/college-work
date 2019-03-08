#ifndef INCLUDE_MODELS_PLAYER_HPP
#define INCLUDE_MODELS_PLAYER_HPP

#include "../main.h"

#include "model.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <memory>

const GLfloat max_velocity_x = 0.03;
const GLfloat step_velocity_x = 0.01;
const GLfloat max_velocity_y = 0.02;
const GLfloat step_velocity_y = 0.01;

struct key_state_t {
    bool W, A, S, D;
    bool space;
};

class Player {
public:
    Player();
    void draw(glm::mat4 VP);
    
    void push(glm::vec3 velocity) { this->velocity += velocity; };

    void input(key_state_t keys);
    void tick(const std::vector<std::shared_ptr<IModel>>& models);

    void set_position(glm::vec3 position) { this->position = position; };
    glm::vec3 get_position() const { return position; };

    int get_score() const { return score; }
    int get_lives() const { return lives; }

    void set_shield(bool enable) { shield = enable; };

private:
    int score;
    int lives;

    bool shield;

    void process_interaction(const InteractionOutput& interaction);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 size;

    glm::vec3 velocity;  

    VAO *object;  
};

#endif /* INCLUDE_MODELS_PLAYER_HPP */
