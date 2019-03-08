#ifndef INCLUDE_MODELS_SILVER_COIN_HPP
#define INCLUDE_MODELS_SILVER_COIN_HPP

#include "model.hpp"

#include "../main.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SilverCoin : public ICollision, public IStatic {
public:
    SilverCoin();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_SILVER_COIN_HPP */
