#include "../include/MenuScene.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/StageScene.h"
#include "../include/manager/AssetManager.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <memory>

MenuItem &operator++(MenuItem &c) {
  using type = std::underlying_type<MenuItem>::type;
  c = static_cast<MenuItem>(static_cast<type>(c) + 1);
  if (c == MenuItem::Last) {
    c = static_cast<MenuItem>(static_cast<type>(MenuItem::None) + 1);
  }
  return c;
}
MenuItem &operator--(MenuItem &c) {
  using type = std::underlying_type<MenuItem>::type;
  c = static_cast<MenuItem>(static_cast<type>(c) - 1);
  if (c == MenuItem::None) {
    c = static_cast<MenuItem>(static_cast<type>(MenuItem::Last) - 1);
  }
  return c;
}

MenuItem operator--(MenuItem &c, int) {
  auto k = c;
  --c;
  return k;
}
MenuItem operator++(MenuItem &c, int) {
  auto k = c;
  ++c;
  return k;
}
MenuScene::MenuScene(Game *game) : Scene(game) {
  auto background = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::MenuBack),
      game->getGlobalRenderer());
  background->setPosition(0, 0);
  background->setSize(game->getWindowWidth(),
                      static_cast<int>(game->getWindowHeight()));
  addObject(background);

  start = std::make_shared<Text>(game->getAssetManager()->getFont(),
                                 game->getGlobalRenderer(), "START");
  start->setColor(choose);
  start->setSize(game->getWindowWidth() / 4, game->getWindowHeight() / 20);
  start->setPosition(game->getWindowWidth() / 2 - start->getWidth() / 2,
                     game->getWindowHeight() - 300);

  addObject(start);

  end = std::make_shared<Text>(game->getAssetManager()->getFont(),
                               game->getGlobalRenderer(), "EXIT");
  end->setColor(normal);
  end->setSize(start->getWidth(), start->getHeight());
  end->setPosition(start->getPositionX(), start->getPositionY() + 100);
  addObject(end);
}

void MenuScene::enter() {}

void MenuScene::exit() {}

void MenuScene::event(SDL_Event &event) {
  Scene::event(event);
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      if (currentItem == MenuItem::Start)
        currentItem = MenuItem::Exit;
      else
        currentItem = MenuItem::Start;
      MenuItemSelect();
      break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      if (currentItem == MenuItem::Start)
        currentItem = MenuItem::Exit;
      else
        currentItem = MenuItem::Start;
      MenuItemSelect();
      break;
    case SDL_SCANCODE_SPACE:
      MenuItemPress();
      break;
    default:
      break;
    }
  }
}

void MenuScene::MenuItemSelect() {
  start->setColor(normal);
  end->setColor(normal);

  switch (currentItem) {
  case MenuItem::Start:
    start->setColor(choose);
    break;
  case MenuItem::Exit:
    end->setColor(choose);
    break;
  default:
    break;
  }
}

void MenuScene::MenuItemPress() {
  switch (currentItem) {
  case MenuItem::Start:
    game->getSceneManager()->addScene("stage",
                                      std::make_shared<StageScene>(game, 1, 0));
    game->getSceneManager()->activeScene("stage");
    break;
  case MenuItem::Exit:
    game->stop();
    break;
  default:
    break;
  }
}
