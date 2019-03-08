#include <iostream>

#include "player.hpp"
#include "../utils.hpp"

Player::Player() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(0.5f, 1.0f, 1.0f);

    size = glm::vec3(0.75f, 1.0f, 1.0f);

    velocity = glm::vec3(0.0f, 0.0f, 0.0f);

    score = 0; 
    lives = 3;
    shield = false;
   
    static const GLfloat vertex_buffer_data[] = {
        /* face */
        -0.25f, 0.5f, 0.0f,
        0.25f, 0.5f, 0.0f,
        0.25f, 0.25f, 0.0f,

        -0.25f, 0.5f, 0.0f,
        -0.25f, 0.25f, 0.0f,
        0.25f, 0.25f, 0.0f,

        /* eyes */
        0.15f, 0.40f, 0.0f,
        0.10f, 0.37f, 0.0f,
        0.20f, 0.37f, 0.0f,

        /* body */
        -0.25f, 0.25f, 0.0f,
        0.25f, 0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,

        -0.25f, 0.25f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,

        /* jetpack */
        -0.50f, 0.20f, 0.0f,
        -0.25f, 0.20f, 0.0f,
        -0.25, -0.20f, 0.0f,

        -0.50f, 0.20f, 0.0f,
        -0.50f, -0.20f, 0.0f,
        -0.25, -0.20f, 0.0f,

        /* exhaust */
        -0.40f, -0.20f, 0.0f,
        -0.35f, -0.30f, 0.0f,
        -0.30f, -0.20f, 0.0f
    };

    static const GLfloat vertex_color_data[sizeof(vertex_buffer_data)/sizeof(GLfloat)] = {
        REPEAT3(COLOR_PINK_3f),
        REPEAT3(COLOR_PINK_3f),

        REPEAT3(COLOR_BLACK_3f),

        REPEAT3(COLOR_ORANGE_3f),
        REPEAT3(COLOR_ORANGE_3f),

        REPEAT3(COLOR_GREY_3f),
        REPEAT3(COLOR_GREY_3f),

        REPEAT3(COLOR_RED_3f)
    };

    object = create3DObject(GL_TRIANGLES,
                            sizeof(vertex_buffer_data)/sizeof(GLfloat)/3,
                            vertex_buffer_data,
                            vertex_color_data,
                            GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 T = glm::translate(position);
    glm::mat4 R = glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 S = glm::scale(scale);
    Matrices.model *= (T * R * S);

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object);
}

void Player::input(key_state_t keys) {
    if(keys.W || keys.space) {
        velocity.y = std::min(velocity.y + step_velocity_y, max_velocity_y);
    }

    if(keys.S) {
        velocity.y = std::max(velocity.y - step_velocity_y, -2*max_velocity_y);
    }

    if(keys.A) {
        velocity.x = std::max(velocity.x - max_velocity_y, -max_velocity_x);
    }

    if(keys.D) {
        velocity.x = std::min(velocity.x + max_velocity_y, max_velocity_x);
    }
}

void Player::process_interaction(const InteractionOutput& interaction) {
    score += interaction.score;
    lives += interaction.lives;

    if(!shield) {
        if(interaction.kill)
        lives--;

        if(lives == 0) {
            std::cout << "Game Over!\n";
            std::cout << "Score: " << score;
            std::exit(0);
        }
    }    
}

void Player::tick(const std::vector<std::shared_ptr<IModel>>& models) {
    auto check_col = [&models, this](glm::vec3 peek = glm::vec3(0.0f, 0.0f, 0.0f)) {
        rotated_rectangle<GLfloat> rect(position.x + peek.x, position.y + peek.y, size.x * scale.x, size.y * scale.y, rotation.z);
        for(auto& m : models) {
            if(m->has_collision()) {
                auto c = std::dynamic_pointer_cast<ICollision, IModel>(m);
                auto type = c->check_collision(rect);
                if(type != ICollision::collision_type::none)
                    return std::make_pair(c, type);              
            }
        }
        return std::make_pair(std::shared_ptr<ICollision>(), ICollision::collision_type::none);
    };

    for(int i = 0; i <= std::abs(std::round(velocity.x/precision)); i++) {
        glm::vec3 peek(precision * signum(velocity.x), 0.0f, 0.0f);
        auto collision = check_col(peek);
        auto m = collision.first;
        if(m) {
            auto interaction = m->interact({});
            process_interaction(interaction);
            if(interaction.stop) {
                velocity.x = 0;
                break;
           }
       }
       position.x += peek.x;
    }

    for(int i = 0; i <= std::abs(std::round(velocity.y/precision)); i++) {   
        glm::vec3 peek(0.0f, precision * signum(velocity.y), 0.0f);
        auto collision = check_col(peek);
        auto m = collision.first;
        if(m) {
            auto interaction = m->interact({});
            process_interaction(interaction);
            if(interaction.stop) {
                velocity.y = 0;
                break;
           }
        }
        position.y += peek.y;
    }

    switch(signum(velocity.x)) {
        case -1:
            velocity.x = std::min(0.0f, velocity.x + step_velocity_x/2);
            break;
        case 1:
            velocity.x = std::max(0.0f, velocity.x - step_velocity_x/2);
            break;
    }
    velocity.y = std::max(velocity.y - step_velocity_y/10, -max_velocity_y*2);
}