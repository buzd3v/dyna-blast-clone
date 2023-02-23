#pragma once

#include "Scene.h"
#include <cstdint>

class StageScene : public Scene {
public:
  StageScene(Game *game, const uint level, const uint score);
  virtual void update(uint32_t delta);

private:
  int utilNextScene = 0;
  const int sceneTimer = 1200;
  uint stage = 0;
  uint score = 0;
};