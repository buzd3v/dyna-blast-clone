#pragma once
#include <SDL2/SDL.h>
#include <memory>

#include "Scene.h"
#include "Text.h"

class GameOverScene : public Scene {
public:
  /**
   * @brief Construct a new Game Over Scene
   *
   * @param game
   */
  GameOverScene(Game *game);
  virtual void update(const unsigned int delta) override;

private:
  // timer until switch to next menu
  int untilNextSceneTimer = 0;
  // const
  const int sceneTimer = 2000;
};
