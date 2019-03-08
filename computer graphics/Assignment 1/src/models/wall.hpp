#ifndef INCLUDE_MODELS_WALL_HPP
#define INCLUDE_MODELS_WALL_HPP

#include "model.hpp"

class Wall : public ICoalesce, public IStatic {
public:
    Wall();
    InteractionOutput interact(const InteractionInput& input);
};

#endif /* INCLUDE_MODELS_WALL_HPP */
