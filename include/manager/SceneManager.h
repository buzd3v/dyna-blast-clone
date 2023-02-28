#pragma once

#include "../Scene.h"
#include <SDL2/SDL_events.h>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>

class Scene;
class SceneManager {
public:
  void addScene(const std::string &name, std::shared_ptr<Scene> scene);
  void activeScene(const std::string &name);
  void removeScene(const std::string &name);
  void onEvent(SDL_Event &event);
  void update(const uint delta);
  void draw();

  void logScene();

private:
  std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
  std::queue<std::shared_ptr<Scene>> removedScenes;
  std::shared_ptr<Scene> currentScene;
};