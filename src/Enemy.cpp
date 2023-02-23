#include "../include/Enemy.h"
#include "../include/Global.h"

#include <chrono>
#include <functional>
#include <memory>
#include <random>

Enemy::Enemy(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer)
    : Creature(texture, renderer) {
  movement = std::make_shared<Animation>();
  movement->addFrame(Frame(0, 0, tileWidth, tileHeight));
  movement->addFrame(Frame(tileWidth * 1, 0, tileWidth, tileHeight));
  movement->addFrame(Frame(tileWidth * 2, 0, tileWidth, tileHeight));

  die = std::make_shared<Animation>();
  die->addFrame(Frame(tileWidth * 3, 0, tileWidth, tileHeight));
  die->addFrame(Frame(tileWidth * 4, 0, tileWidth, tileHeight));
  die->addFrame(Frame(tileWidth * 5, 0, tileWidth, tileHeight));
  die->addFrame(Frame(tileWidth * 6, 0, tileWidth, tileHeight));

  addAnimation(movement);
  addAnimation(die);
}

void Enemy::moveTo(const int x, const int y) {
  movement->play();
  setMove(true);

  newPosX = getPositionX() + x;
  newPosY = getPositionY() + y;
}

void Enemy::moveToCell(std::pair<int, int> pathToCell) {
  path = pathToCell;
  movingToCell = true;

  newPosX = getPositionX() - ((getPositionX() - newPosX) % getWidth());
  newPosY = getPositionY() - ((getPositionY() - newPosY) % getHeight());
}

bool Enemy::isMoveToCell() const { return movingToCell; }

bool Enemy::canAttack() const { return type == AIType::chasing; }

int Enemy::getAttackRadius() const { return attackRadius; }

void Enemy::setAIType(AIType type) { this->type = type; }

void Enemy::update(const uint32_t delta) {
  Creature::update(delta);
  if (isMoving()) {
    updateMoveMent(delta);
  }

  else if (movingToCell) {
    moveTo(path.second * getWidth(), path.first * getHeight());
  }

  else {
    genNewPath();
  }
}

void Enemy::genNewPath() {
  const auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();

  /**
  functor uniform_int_distribution
  functor mt19937
  functor 1 add functor 2 as parameter so binding it for randPath and randSign
  */

  auto randPath = std::bind(std::uniform_int_distribution<int>(1, 10),
                            std::mt19937(static_cast<uint>(seed)));
  auto randSign = std::bind(std::uniform_int_distribution<int>(-1, 1),
                            std::mt19937(static_cast<uint>(seed)));
  const int randUpDown = randPath();
  const int randUpDownSign = randSign();
  if (randUpDownSign != 0) {
    moveTo(0, randUpDown * randUpDownSign * getHeight());
    return;
  }
  const int randLeftRight = randPath();
  const int randLeftRightSign = randSign();
  if (randLeftRightSign != 0) {
    moveTo(randLeftRight * randLeftRightSign * getWidth(), 0);
  }
}

void Enemy::updateMoveMent(const uint32_t delta) {
  const int newPosDiffX = getPositionX() - newPosX;
  const int newPosDiffY = getPositionY() - newPosY;
  const char signOfX = (newPosDiffX > 0) ? 1 : ((newPosDiffX < 0) ? -1 : 0);
  const char signOfY = (newPosDiffY > 0) ? 1 : ((newPosDiffY < 0) ? -1 : 0);
  const int posDiff = static_cast<int>(
      floor((canAttack() ? attackSpeed : baseAtkspeed) * delta * getWidth()));

  preDeltaX = posDiff * -signOfX;
  preDeltaY = posDiff * -signOfY;

  // finish movement
  if (newPosDiffX * signOfX <= posDiff && newPosDiffY * signOfY <= posDiff) {
    movement->pause();
    setMove(false);
    movingToCell = false;
    setPosition(newPosX, newPosY);
    return;
  }
  // move sprite to next tick pos
  setPosition(getPositionX() - static_cast<int>(floor(posDiff)) * signOfX,
              getPositionY() - static_cast<int>(floor(posDiff)) * signOfY);
}
