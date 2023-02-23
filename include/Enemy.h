#pragma once

#include "Creature.h"
#include <cstdint>
#include <memory>
#include <utility>

enum AIType { chasing, wandering };

class Enemy : public Creature {
public:
  /**
   * @brief Construct a new Enemy object
   *
   * @param texture
   * @param renderer
   */
  Enemy(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer);
  void moveTo(const int x, const int y);
  void moveToCell(std::pair<int, int> pathToCell);
  bool isMoveToCell() const;
  bool canAttack() const;
  int getAttackRadius() const;
  void setAIType(AIType type);
  virtual void update(const uint32_t delta) override;
  void genNewPath();

private:
  void updateMoveMent(const uint32_t delta);

  int newPosX = 0;
  int newPosY = 0;
  bool movingToCell = false;
  std::pair<int, int> path;

  AIType type = AIType::wandering;

  const float baseAtkspeed = 0.0018f;
  const float attackSpeed = 0.0025f;
  const int attackRadius = 4;

  std::shared_ptr<Animation> movement;
  std::shared_ptr<Animation> die;
};
