#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include <vector>

#include "Sprite.h"
// must using forward declaration
class Sprite;

struct Frame {
  uint16_t posX = 0;
  uint16_t posY = 0;
  uint16_t width = 0;
  uint16_t height = 0;
  Frame(const uint16_t pos_x, const uint16_t pos_y, const uint16_t w,
        const uint16_t h)
      : posX(pos_x), posY(pos_y), width(w), height(h){};
};
class Animation {
public:
  void addFrame(Frame entity);
  void setSprite(Sprite *Sprite);
  void setAnimationLong(const uint32_t delayMs);
  void play();
  void playOneTime();

  void pause();
  void reset();
  void unsetSprite();
  void update(const uint32_t delta);

private:
  std::vector<Frame> animation;
  uint16_t timeAnimation = 400;
  uint16_t time = 0;
  bool isPlaying = false;
  uint32_t currentEntity = 0;
  Sprite *sprite = nullptr;
};
