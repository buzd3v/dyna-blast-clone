#include "../include/Animation.h"

void Animation::addFrame(Frame entity) {
  animation.push_back(std::move(entity));
}

void Animation::setSprite(Sprite *sprite) {
  this->sprite = sprite;

  if (!animation.empty()) {
    Frame entity = animation[0];
    this->sprite->setSrcRect(
        static_cast<int>(entity.width), static_cast<int>(entity.height),
        static_cast<int>(entity.posX), static_cast<int>(entity.posY));
  }
}
void Animation::unsetSprite() { this->sprite = nullptr; }
void Animation::play() {
  if (isPlaying)
    return;
  isPlaying = true;
  time = 0;
}
void Animation::playOneTime() {
  if (isPlaying) {
    return;
  }
  isPlaying = true;

  time += 20;
  if (time >= timeAnimation) {
    time = 0;
    Frame frame = animation[currentEntity];
    currentEntity = (currentEntity + 1) % animation.size();
    sprite->setSrcRect(
        static_cast<int>(frame.width), static_cast<int>(frame.height),
        static_cast<int>(frame.posX), static_cast<int>(frame.posY));
  }
}

void Animation::pause() { isPlaying = false; }
void Animation::setAnimationLong(const uint32_t delayMs) {
  timeAnimation = delayMs;
}

void Animation::reset() {
  pause();
  currentEntity = 0;
  time = 0;
}

void Animation::update(const uint32_t delta) {
  if (animation.size() == 0 || !sprite || !isPlaying) {
    return;
  }
  time += delta;
  if (time >= timeAnimation) {
    time = 0;
    Frame frame = animation[currentEntity];
    currentEntity = (currentEntity + 1) % animation.size();
    sprite->setSrcRect(
        static_cast<int>(frame.width), static_cast<int>(frame.height),
        static_cast<int>(frame.posX), static_cast<int>(frame.posY));
  }
}
