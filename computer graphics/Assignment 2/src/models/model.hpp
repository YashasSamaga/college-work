#ifndef INCLUDE_MODEL_HPP
#define INCLUDE_MODEL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../utils.hpp"

#include "../main.h"

struct InteractionInput {
    glm::vec3 position;
    glm::vec3 rotation;
};

struct InteractionOutput {
    InteractionOutput() : kill(false), fuel(0.0), score(0) { }

    bool kill;
    float fuel;
    int score;
};

class IModel {
public:
    IModel() {
        state.active = 1;

        position = glm::vec3(0.0f, 0.0f, 0.0f);
        rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    virtual void draw(glm::mat4 VP) {
        if(state.active == 0)
            return;

        Matrices.model = glm::mat4(1.0f);
        glm::mat4 T = glm::translate(position);
        glm::mat4 R = glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
        R *= glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
        R *= glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));
        glm::mat4 S = glm::scale(scale);
        Matrices.model *= (T * R * S);

        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(object);
    }

    virtual void set_position(glm::vec3 position) { this->position = position; };
    virtual glm::vec3 get_position() const { return position; };

    virtual void set_rotation(glm::vec3 rotation) { this->rotation = rotation; }
    virtual glm::vec3 get_rotation() const { return rotation; }

    virtual void set_scale(glm::vec3 scale) { this->scale = scale; }
    virtual glm::vec3 get_scale() const { return scale; }

    virtual glm::vec3 get_size() const { return size; }    

    virtual bool has_collision() const = 0;
    virtual bool is_dynamic() const = 0;

protected:
    struct {
        unsigned active : 1;
    } state;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 size;
    VAO *object;
};

class ICoalesce : virtual public IModel {
public:
    bool has_collision() const override final {
        return false;
    }
};

class ICollision : virtual public IModel {
public:
    enum class collision_type {
        none,
        top,
        bottom,
        left,
        right
    };

    bool has_collision() const override final {
        return true;
    }

    virtual collision_type check_collision(const collision_box<GLfloat>& box) const {
        if(state.active == 0)
            return collision_type::none;
        
        glm::vec3 effective_size(size.x * scale.x, size.y * scale.y, size.z * scale.z);
        return (glm::length(glm::vec3(box.x, box.y, box.z) - position)) <
               (glm::length(effective_size * 0.5f)) ?
               collision_type::top : collision_type::none;
    }

    virtual InteractionOutput interact(const InteractionInput& input) = 0;
};

class IStatic : virtual public IModel {
public:
    bool is_dynamic() const override final {
        return false;
    }
};

class IDynamic : virtual public IModel {
public:
    bool is_dynamic() const override final {
        return true;
    }

    virtual void tick() = 0;
};

/* specialization */
class ICollectable : virtual public ICollision, virtual public IDynamic {
public:
    virtual void tick() {
        rotation.y += 1.0;
        if(rotation.y > 180.0)
            rotation.y -= 360.0;
    }
};

#endif /* INCLUDE_MODEL_HPP */