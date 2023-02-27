#include "../include/StageScene.h"
#include "../include/Game.h"
#include "../include/LevelScene.h"
#include "../include/Text.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unistd.h>

StageScene::StageScene(Game *game, const uint level, const uint score)
    : Scene(game), stage(level), score(score) {
  auto text = std::make_shared<Text>(game->getAssetManager()->getFont(),
                                     game->getGlobalRenderer(),
                                     "Stage " + std::to_string(level));
  text->setSize(game->getWindowWidth() / 2, game->getWindowHeight() / 2);
  text->setPosition(game->getWindowWidth() / 2 - text->getWidth() / 2,
                    game->getWindowHeight() / 2 - text->getHeight() / 2);
  addObject(text);
}

void StageScene::update(uint32_t delta) {
  utilNextScene += delta;
  if (utilNextScene >= sceneTimer) {
    utilNextScene = 0;
    game->getSceneManager()->addScene(
        "level", std::make_shared<LevelScene>(game, stage, score));
    game->getSceneManager()->activeScene("level");
    game->getSceneManager()->removeScene("stage");
    // sleep(10);
  }
}
