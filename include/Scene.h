#pragma once

#include "Object.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <memory>
#include <sys/types.h>
#include <vector>

class Game;

class Scene {
public:
  /**
   * @brief Construct a new Scene object
   *
   * @param game
   */
  Scene(Game *game);
  /**
   * @brief Destroy the Scene object
   *
   */
  virtual ~Scene();

  /**
   * @brief
   *
   * @param object
   */
  void addObject(std::shared_ptr<Object> object);
  /**
   * @brief
   *
   * @param object
   */
  void insertObject(std::shared_ptr<Object> object, int pos);
  /**
   * @brief
   *
   * @param object
   */
  void deleteObject(std::shared_ptr<Object> object);
  void setCamera(const int x, const int y);
  virtual void enter();
  virtual void exit();
  virtual void event(SDL_Event &event);
  virtual void update(const uint32_t delta);
  void draw() const;

protected:
  Game *game = nullptr;

private:
  std::vector<std::shared_ptr<Object>> objs;
  SDL_Rect camera;
};