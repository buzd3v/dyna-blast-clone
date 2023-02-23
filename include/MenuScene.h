#pragma once
#include "Scene.h"
#include "Text.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <memory>
#include <type_traits>

enum class MenuItem { None, Start, Exit, Last };

class MenuScene : public Scene {
public:
  MenuScene(Game *game);
  virtual void enter() override;
  virtual void exit() override;
  virtual void event(SDL_Event &event);

private:
  void MenuItemSelect();
  void MenuItemPress();

  std::shared_ptr<Text> start = nullptr;
  MenuItem currentItem = MenuItem::Start;
  std::shared_ptr<Text> end = nullptr;

  const SDL_Color normal = {255, 255, 255, 255};
  const SDL_Color choose = {51, 153, 255, 255};
};