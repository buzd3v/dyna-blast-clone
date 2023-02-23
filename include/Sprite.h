#pragma once

#include "Object.h"
#include "Animation.h"

#include <memory>

class Animation;

class Sprite : public Object
{

public:
    Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);

    void addAnimation(std::shared_ptr<Animation> animation);
    virtual void update(const uint32_t delta) override;

private:
    std::vector<std::shared_ptr<Animation>> animations;
};
