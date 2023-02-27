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
  movement->addFrame(Frame(tileWidth * 3, 0, tileWidth, tileHeight));

  die = std::make_shared<Animation>();
  die->addFrame(Frame(tileWidth * 3, 0, tileWidth, tileHeight));
  die->addFrame(Frame(tileWidth * 4, 0, tileWidth, tileHeight));
  die->addFrame(Frame(tileWidth * 5, 0, tileWidth, tileHeight));
  die->addFrame(Frame(tileWidth * 6, 0, tileWidth, tileHeight));

  movement->setSprite(this);

  addAnimation(movement);
  addAnimation(die);
}

void Enemy::moveTo(const int x, const int y) {
  // start a moving, see update func
  movement->play();
  setMove(true);
  // save new position
  newPosX = getPositionX() + x;
  newPosY = getPositionY() + y;
  // flip
}

void Enemy::moveToCell(std::pair<int, int> pathToCell) {
  // save moving path
  path = pathToCell;
  movingToCell = true;
  // move enemy to nearest cell
  newPosX = getPositionX() - ((getPositionX() - newPosX) % getWidth());
  newPosY = getPositionY() - ((getPositionY() - newPosY) % getHeight());
}

bool Enemy::isMoveToCell() const { return movingToCell; }

bool Enemy::canAttack() const { return type == AIType::chasing; }

int Enemy::getAttackRadius() const { return attackRadius * getWidth(); }

void Enemy::setAIType(AIType type) { this->type = type; }

void Enemy::update(const unsigned int delta) {
  Creature::update(delta);
  // simple wandering moving
  if (isMoving()) {
    updateMoveMent(delta);
  }
  // moving to cell
  else if (movingToCell) {
    moveTo(path.second * getWidth(), path.first * getHeight());
  }
  // new random path
  else {
    genNewPath();
  }
}

void Enemy::updateMoveMent(const unsigned int delta) {
  // calculate consts for movement
  const int newPositionDiffX = getPositionX() - newPosX;
  const int newPositionDiffY = getPositionY() - newPosY;
  const char signOfX =
      (newPositionDiffX > 0) ? 1 : ((newPositionDiffX < 0) ? -1 : 0);
  const char signOfY =
      (newPositionDiffY > 0) ? 1 : ((newPositionDiffY < 0) ? -1 : 0);
  const int posDiff = static_cast<int>(
      floor((canAttack() ? attackSpeed : baseAtkspeed) * delta * getWidth()));

  preDeltaX = posDiff * -signOfX;
  preDeltaY = posDiff * -signOfY;

  // finish movement
  if (newPositionDiffX * signOfX <= posDiff &&
      newPositionDiffY * signOfY <= posDiff) {
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

void Enemy::genNewPath() {
  // create random func
  const auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  auto randPath = std::bind(std::uniform_int_distribution<int>(1, 10),
                            std::mt19937(static_cast<unsigned int>(seed)));
  auto randSign = std::bind(std::uniform_int_distribution<int>(0, 4),
                            std::mt19937(static_cast<unsigned int>(seed)));

  // generate direction and cells
  const int randUpDown = randPath();
  direction = randSign();
  switch (direction) {

  case 1:
    moveTo(0, randUpDown * 1 * getHeight());
    break;
  case 2:
    moveTo(0, randUpDown * -1 * getHeight());
    break;
  case 3:
    moveTo(randUpDown * 1 * getHeight(), 0);
    break;
  case 4:
    moveTo(randUpDown * -1 * getHeight(), 0);
    break;
  default:
    break;
  }
  // const int randUpDownSign = randSign();
  // if (randUpDownSign != 0) {
  //   moveTo(0, randUpDown * randUpDownSign * getHeight());
  //   return;
  // }
  // const int randLeftRight = randPath();
  // const int randLeftRightSign = randSign();
  // if (randLeftRightSign != 0) {
  //   moveTo(randLeftRight * randLeftRightSign * getWidth(), 0);
  //   return;
  // }
}
void Enemy::changeDir(int dir) { direction = dir; }