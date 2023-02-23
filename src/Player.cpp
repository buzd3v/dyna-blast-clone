#include "../include/Player.h"
#include "../include/Global.h"

Player::Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer *renderer)
    : Creature(texture, renderer) {
  this->m_texture = texture;
  movementUp = std::make_shared<Animation>();
  movementRight = std::make_shared<Animation>();
  movementLeft = std::make_shared<Animation>();
  movementDown = std::make_shared<Animation>();
  int tileWidth = 52;
  int tileheight = 63;
  movementUp->addFrame(Frame(0, 0, tileWidth, tileHeight));
  movementUp->addFrame(Frame(tileWidth * 1, 0, tileWidth, tileHeight));
  movementUp->addFrame(Frame(tileWidth * 2, 0, tileWidth, tileHeight));
  movementUp->addFrame(Frame(tileWidth * 3, 0, tileWidth, tileHeight));
  movementRight->addFrame(Frame(tileWidth * 4, 0, tileWidth, tileHeight));
  movementRight->addFrame(Frame(tileWidth * 5, 0, tileWidth, tileHeight));
  movementRight->addFrame(Frame(tileWidth * 6, 0, tileWidth, tileHeight));
  movementRight->addFrame(Frame(tileWidth * 7, 0, tileWidth, tileHeight));
  movementDown->addFrame(Frame(tileWidth * 8, 0, tileWidth, tileHeight));
  movementDown->addFrame(Frame(tileWidth * 9, 0, tileWidth, tileHeight));
  movementDown->addFrame(Frame(tileWidth * 10, 0, tileWidth, tileHeight));
  movementDown->addFrame(Frame(tileWidth * 11, 0, tileWidth, tileHeight));
  movementLeft->addFrame(Frame(tileWidth * 12, 0, tileWidth, tileHeight));
  movementLeft->addFrame(Frame(tileWidth * 13, 0, tileWidth, tileHeight));
  movementLeft->addFrame(Frame(tileWidth * 14, 0, tileWidth, tileHeight));
  movementLeft->addFrame(Frame(tileWidth * 15, 0, tileWidth, tileHeight));

  movement = movementDown;

  addAnimation(movementUp);
  addAnimation(movementDown);
  addAnimation(movementLeft);
  addAnimation(movementRight);
}

bool Player::isMovingHorizontal() const {
  return (m_direction == Direction::LEFT || m_direction == Direction::RIGHT);
}

bool Player::isMovingVertical() const {
  return (m_direction == Direction::DOWN || m_direction == Direction::UP);
};

void Player::setDirection(Direction dir) {
  m_direction = dir;
  setMove(m_direction != Direction::NONE);
  switch (m_direction) {
  case Direction::LEFT:
    movement = movementLeft;
    break;
  case Direction::RIGHT:
    movement = movementRight;
    break;
  case Direction::UP:
    movement = movementUp;
    break;
  case Direction::DOWN:
    movement = movementDown;
    break;
  case Direction::NONE:
    movement->pause();
    break;
  default:
    break;
  }
}
void Player::update(const uint32_t delta) {
  if (isMoving()) {
    const int posDiff =
        static_cast<int>(std::floor(speed * delta * getWidth()));
    preDeltaX =
        posDiff *
        (isMovingHorizontal() ? (m_direction == Direction::LEFT ? -1 : 1) : 0);
    preDeltaY =
        posDiff *
        (isMovingVertical() ? (m_direction == Direction::UP ? -1 : 1) : 0);
    // move sprite to next tick pos
    setPosition(getPositionX() + preDeltaX, getPositionY() + preDeltaY);
  }

  Creature::update(delta);
}
