#include <iostream>

#include "player.hpp"
#include "../colors.hpp"
#include "../utils.hpp"

#include "../tools/objloader.hpp"

Player::Player() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation.global = glm::vec3(0.0f, 90.0f, 0.0f);
    rotation.local = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

    size = glm::vec3(0.75f, 1.0f, 1.0f);

    velocity.translational = glm::vec3(0.0f, 0.0f, 0.0f);
    velocity.rotational = glm::vec3(0.0f, 0.0f, 0.0f);

    fuel = 1.0f;
    score = 0;

    std::vector<GLfloat> vertices;
    assert(load_object("../resources/airplane.obj", vertices, size));

    std::vector<GLfloat> color_data_buffer(vertices.size());
    for(int i = 0; i < vertices.size(); i++) {
        color_data_buffer[i] = rand()/float(RAND_MAX);
    }

    object = create3DObject(GL_TRIANGLES,
                            vertices.size()/3,
                            vertices.data(),
                            color_data_buffer.data(),
                            GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 T = glm::translate(position);
    glm::mat4 Rlz = glm::rotate(glm::radians(rotation.local.z), glm::vec3(0, 0, 1));
    glm::mat4 Rly = glm::rotate(glm::radians(rotation.local.y), glm::vec3(0, 1, 0));
    glm::mat4 Rlx = glm::rotate(glm::radians(rotation.local.x), glm::vec3(1, 0, 0));
    glm::mat4 Rgy = glm::rotate(glm::radians(rotation.global.y), glm::vec3(0, 1, 0));
    glm::mat4 S = glm::scale(scale);
    Matrices.model *= (T * Rgy * Rly * Rlz * Rlx * S);

    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(object);
}

void Player::input(key_state_t keys) {
    if(fuel < 0.0f) {
        return;
    }

    /* trusters */
    if(keys.W) {
        auto &v = velocity.translational;
        v.z -= 0.01;
        v.z = std::max(v.z, -0.05f * 15);
    }

    if(keys.S) {
        auto &v = velocity.translational;
        v.z += 0.01;
        v.z = std::min(v.z, -0.02f * 15);
    }

    /* aielrons */
    if(keys.A) {
        auto &r = rotation.local;
        r.z += 0.25f;
    }

    if(keys.D) {
        auto &r = rotation.local;
        r.z -= 0.25;
    }

    /* rudder */
    if(keys.Q) {
        auto &r = rotation.local;
        r.y = std::min(r.y + 0.25, 10.0);
    }

    if(keys.E) {
        auto &r = rotation.local;
        r.y = std::max(r.y - 0.25, -10.0);
    }

    /* elevators */
    if(keys.up) {
        auto &r = rotation.local;
        r.x -= 0.25f;
    }

    if(keys.down) {
        auto &r = rotation.local;
        r.x += 0.25;
    }

    /* lift */
    if(keys.space) {
        auto &v = velocity.translational;
        v.y = std::min(v.y + 0.05, 0.2);
    }

    if(keys.lshift) {
        auto &v = velocity.translational;
        v.y = std::max(v.y - 0.05,  -0.2);
    }
}

void Player::process_interaction(const InteractionOutput& interaction) {
    if(interaction.kill)
        std::exit(0);

    fuel = std::min(fuel + interaction.fuel, 0.99f);
    score += interaction.score;
}

void Player::tick(const std::vector<std::shared_ptr<IModel>>& models) {
    glm::mat4 Ry = glm::rotate(glm::radians(rotation.global.y), glm::vec3(0, 1, 0));
    glm::mat4 Rx = glm::rotate(glm::radians(rotation.local.x), glm::vec3(1, 0, 0));

    while(rotation.local.x > 180.0)
        rotation.local.x -= 360.0;

    while(rotation.local.z > 180.0)
        rotation.local.z -= 360.0;

    while(rotation.local.x < -180.0)
        rotation.local.x += 360.0;

    while(rotation.local.y < -180.0)
        rotation.local.x += 360.0;

    auto local_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    local_velocity.z = velocity.translational.z;
    local_velocity.y = velocity.translational.y;
    local_velocity.x = glm::clamp(rotation.local.y, -15.0f, 15.0f) * 0.001 + glm::clamp(rotation.local.z, -15.0f, 15.0f) * 0.002;
    velocity.translational.x = local_velocity.x;

    auto global_velocity = Ry * Rx * glm::vec4(local_velocity, 0.0f) + glm::vec4(0.0f, -0.05f, 0.0f, 0.0f);
    position += glm::vec3(global_velocity);

    glm::vec3 rotational_delta(0, 0, 0);
    rotational_delta.y = (rotation.local.y * 0.01 + rotation.local.z * 0.02);
    rotation.global += rotational_delta;

    if(std::abs(rotation.local.x) > 0.01)
        rotation.local.x -= signum(rotation.local.x) * 0.01;
    if(std::abs(rotation.local.y) > 0.01)
        rotation.local.y -= signum(rotation.local.y) * 0.1;
    if(std::abs(rotation.local.z) > 0.01)
        rotation.local.z -= signum(rotation.local.z) * 0.1;
    if(std::abs(velocity.translational.z) > 0.001)
        velocity.translational.z -= signum(velocity.translational.z) * 0.001;

    fuel -= 0.000025;

    InteractionInput input;
    input.position = position;
    input.rotation = rotation.global;
    collision_box<GLfloat> box(position.x, position.y, position.z, size.x, size.y, size.z);
    for(auto& m : models) {
        if(m->has_collision()) {
            auto c = std::dynamic_pointer_cast<ICollision, IModel>(m);
            if(c->check_collision(box) != ICollision::collision_type::none) {
                process_interaction(c->interact(input));
            }
        }
    }
}