#pragma once

#include "Bonus.h"
#include "Enemy.h"
#include "Game.h"
#include "Global.h"
#include "Object.h"
#include "Player.h"
#include "Scene.h"
#include "Text.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <sys/types.h>
#include <utility>
#include <vector>

class LevelScene : public Scene {
public:
  LevelScene(Game *game, const uint32_t stage, const uint32_t prevScore);

  virtual void event(SDL_Event &event) override;

  virtual void update(const uint32_t delta) override;

private:
  void spawnTextObj();
  void initTileMap();
  void initEnemies();
  void spawnGrass(const int x, const int y);
  void spawnBrick(const int x, const int y);
  void spawnTopLeftCorner(const int x, const int y);
  void spawnTopRightCorner(const int x, const int y);
  void spawnBottomLeftCorner(const int x, const int y);
  void spawnBottomRightCorner(const int x, const int y);
  void spawnLeftWall(const int x, const int y);
  void spawnRightWall(const int x, const int y);
  void spawnTopWall(const int x, const int y);
  void spawnBottomWall(const int x, const int y);

  void spawnStone(const int x, const int y);
  void spawnPlayer(const int x, const int y);
  void spawnEnemy(Texture texture, AIType type, const int x, const int y);
  void spawnBomb(Object *object);
  void spawnBang(Object *object);
  void spawnDoor(Object *object);
  void spawnScoreBoard();
  void spawnBonus(Texture texture, BonusType type, const int x, const int y);
  void initBonus(Object *object);

  void finish() const;
  void gameOver();
  void Exit() const;

  // timers

  void updateTimer(const uint32_t delta);
  void updateLevelTimer();
  void updateBombTimer(const uint32_t delta);
  void updateBangTimer(const uint32_t delta);
  void updateGameOverTimer(const uint32_t delta);

  void updateMovement(const bool isPressed, const int keyCode);

  void updateCamera();

  void updateScore();

  void updateplayerColisson();
  void updateEnemyColisson();
  void updateBangColisson();

  bool isColissonDetect(const SDL_Rect &obj1, const SDL_Rect &obj2);

  void destroyBrick(std::shared_ptr<Sprite> brick);

  void toFollowPlayer(std::shared_ptr<Enemy> enemy);

  // const timer
  const int levelTimerStart = 200500;
  const int levelTimerUpdateText = 1000;
  const int bombTimerStart = 1500;
  const int bangTimerStart = 800;
  const int gameOverTimerStart = 1000;
  const int winTimerStart = 200;

  const int killScore = 200;
  const int stageCompleteScore = 1000;

  std::shared_ptr<Text> timerNumber = nullptr;
  std::shared_ptr<Text> scoreNumber = nullptr;
  std::shared_ptr<Player> player = nullptr;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::shared_ptr<Sprite> bomb = nullptr;
  std::shared_ptr<Object> door = nullptr;
  // std::shared_ptr<Object> bbonus = nullptr;
  Bonus *bonus = nullptr;

  // colisson
  std::vector<std::pair<Tile, std::shared_ptr<Sprite>>> colissions;
  std::vector<std::shared_ptr<Object>> bangs;
  Tile tiles[TileArrayHeight][TileArrayWidth];

  int PlayerDirectionX = 0;
  int PlayerDirectionY = 0;
  // timer variables
  int levelTimer = levelTimerStart;
  int levelTimerDelta = 0;
  int bombTimer = 0;
  int bangTimer = 0;
  int gameOverTimer = 0;
  // bool flags
  bool isGameOver = false;
  bool isPaused = false;
  bool isWin = false;
  // variables
  unsigned int score = 0;
  unsigned int stage = 0;

  // level positioning
  int fieldPositionX = 0;
  int fieldPositionY = 0;
  // size of tiles
  int scaledTileSize = 48;
  // last object that used as background (grass)
  int backgroundObjectLastNumber = 0;
  bool isBonus = false;
};