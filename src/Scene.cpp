#include "../include/Scene.h"

#include <algorithm>

Scene::Scene(Game *game) {
  this->game = game;
  camera = {0, 0, 0, 0};
}

Scene::~Scene() {}

void Scene::addObject(std::shared_ptr<Object> object) {
  objs.push_back(std::move(object));
}

void Scene::insertObject(std::shared_ptr<Object> object, int pos) {
  objs.insert(objs.begin() + pos, object);
}

void Scene::deleteObject(std::shared_ptr<Object> object) {
  objs.erase(std::remove(objs.begin(), objs.end(), object), objs.end());
}

void Scene::setCamera(const int x, const int y) {
  camera.x = x;
  camera.y = y;
}

void Scene::enter() {}

void Scene::exit() {}

void Scene::event(SDL_Event &event) {}

void Scene::update(const uint32_t delta) {
  for (auto &obj : objs) {
    obj->update(delta);
  }
}

void Scene::draw() const {
  for (auto &obj : objs) {
    obj->draw(camera);
  }
}
