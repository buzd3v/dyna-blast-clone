#include "../include/manager/SceneManager.h"
#include <SDL2/SDL_events.h>
#include <iterator>
#include <utility>

void SceneManager::addScene(const std::string &name,
                            std::shared_ptr<Scene> scene) {
  const auto it = scenes.find(name);
  if (it != scenes.end() && it->second) {
    std::cout << "Scene Manager added: " + name +
                     " not success cause it already have in the Scenes"
              << std::endl;
    // it->second = scene;
    return;
  }
  scenes[name] = std::move(scene);
}

void SceneManager::activeScene(const std::string &name) {
  const auto it = scenes.find(name);
  if (it != scenes.end()) {
    if (currentScene) {
      currentScene->exit();
    }
    currentScene = it->second;
    currentScene->enter();
  } else {
    std::cout << "Scene Manager - active " + name + " do not exist"
              << std::endl;
  }
}

void SceneManager::removeScene(const std::string &name) {
  const auto it = scenes.find(name);
  if (it != scenes.end()) {
    if (currentScene == it->second) {
      {
        currentScene->exit();
        currentScene = nullptr;
      }
    }
    removedScenes.push(it->second);
    scenes.erase(name);

  } else {
    std::cout << "Scene Manager - remove " + name + " do not exist"
              << std::endl;
  }
}

void SceneManager::onEvent(SDL_Event &event) { currentScene->event(event); }

void SceneManager::update(const uint delta) {
  while (removedScenes.size() > 0) {
    removedScenes.pop();
  }
  currentScene->update(delta);
}
void SceneManager::draw() { currentScene->draw(); }

void SceneManager::logScene() {
  for (auto &scene : scenes) {
    std::cout << scene.first << " ";
  }
  std::cout << std::endl;
}