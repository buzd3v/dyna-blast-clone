#ifndef GAME_H
#define GAME_H

#include "./manager/AssetManager.h"
#include "./manager/SceneManager.h"
#include <SDL2/SDL.h>

#include <cstddef>
#include <iostream>
#include <memory>

class SceneManager;
class Game {
private:
  /* data */
public:
  /**
   * constructor
   * @brief create game
   */
  Game(const std::string &title, const int width, const int height);

  ~Game();

  void run();

  void stop();

  int getWindowWidth() const;

  int getWindowHeight() const;

  SDL_Renderer *getGlobalRenderer();

  auto getAssetManager() const { return this->assetManager; }
  auto getSceneManager() const { return this->sceneManager; }

private:
  SDL_Renderer *g_renderer = nullptr;
  SDL_Window *g_window = nullptr;

  int windowWidth = 0;
  int windowHeight = 0;

  bool isRunning = false;
  uint32_t lastTime = 0;

  std::shared_ptr<AssetManager> assetManager = nullptr;
  std::shared_ptr<SceneManager> sceneManager = nullptr;
};

#endif // GAME_H
