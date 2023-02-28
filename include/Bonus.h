#pragma once

#include "Sprite.h"
#include "manager/AssetManager.h"
#include <SDL2/SDL_render.h>
#include <memory>

enum class BonusType { speed, maxbomb, doublebomb };
class Bonus : public Sprite {
public:
  Bonus(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer)
      : Sprite(texture, renderer) {}

  BonusType type = BonusType::speed;
  void setType(BonusType type) { this->type = type; }
  void setTransParentTexture(std::shared_ptr<SDL_Texture> texture) {
    this->m_texture = texture;
  }
};
