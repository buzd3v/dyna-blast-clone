#pragma once

#include "Animation.h"
#include "Creature.h"

enum Direction { UP, DOWN, LEFT, RIGHT, NONE };

class Player : public Creature {
public:
  Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
  void setDirection(Direction dir);
  virtual void update(const uint32_t delta) override;
  std::shared_ptr<Animation> movementLeft;
  std::shared_ptr<Animation> movementRight;
  std::shared_ptr<Animation> movementUp;
  std::shared_ptr<Animation> movementDown;

  std::shared_ptr<Animation> movement;

private:
  bool isMovingHorizontal() const;
  bool isMovingVertical() const;
  Direction m_direction = Direction::NONE;
  const float speed = 0.002f;
};