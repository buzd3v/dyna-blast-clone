#include "../include/LevelScene.h"
#include "../include/Global.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <chrono>
#include <cmath>
#include <functional>
#include <memory>
#include <random>
#include <string>
#include <time.h>
#include <unistd.h>
#include <utility>
LevelScene::LevelScene(Game *game, const uint32_t stage,
                       const uint32_t prevScore)
    : Scene(game), score(prevScore), stage(stage) {
  fieldPositionX = 0;
  fieldPositionY = 70;

  scaledTileSize = 48;
  spawnScoreBoard();
  spawnTextObj();

  initTileMap();
  initEnemies();
  spawnPlayer(fieldPositionX + PlayerStartX * scaledTileSize,
              fieldPositionY + scaledTileSize);

  updateLevelTimer();
}

void LevelScene::spawnScoreBoard() {
  auto scoreBoard = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::ScoreTable),
      game->getGlobalRenderer());
  scoreBoard->setSize(900, 70);
  scoreBoard->setPosition(0, 0);

  addObject(scoreBoard);
};

void LevelScene::spawnTextObj() {
  const int fontWidth = 15;
  const int fontHeight = 15;

  timerNumber = std::make_shared<Text>(game->getAssetManager()->getFont(),
                                       game->getGlobalRenderer(), "000");
  timerNumber->setSize(3 * fontWidth, fontHeight);
  timerNumber->setPosition(400, 26);
  timerNumber->attachToCamera(false);
  addObject(timerNumber);
  backgroundObjectLastNumber++;

  // score
  std::string scoreText = std::to_string(score);
  scoreNumber = std::make_shared<Text>(game->getAssetManager()->getFont(),
                                       game->getGlobalRenderer(), scoreText);
  scoreNumber->setSize(fontWidth * static_cast<int>(scoreText.size()),
                       fontHeight);
  scoreNumber->setPosition(300 - fontWidth * static_cast<int>(scoreText.size()),
                           26);
  scoreNumber->attachToCamera(false);
  addObject(scoreNumber);
  backgroundObjectLastNumber++;

  std::string level = "Level: " + std::to_string(stage);
  auto stageText = std::make_shared<Text>(game->getAssetManager()->getFont(),
                                          game->getGlobalRenderer(), level);
  stageText->setPosition(870 - fontWidth * level.size(), 26);
  stageText->setSize(fontWidth * level.size(), fontHeight);
  stageText->attachToCamera(false);
  addObject(stageText);
  backgroundObjectLastNumber++;
}
void LevelScene::initTileMap() {
  auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  auto randBrick =
      std::bind(std::uniform_int_distribution<int>(0, brickSpawnRandom),
                std::mt19937(static_cast<uint>(seed)));
  for (int i = 0; i < TileArrayHeight; i++) {
    for (int j = 0; j < TileArrayWidth; j++) {
      tiles[i][j] = baseTile[i][j];
      if (tiles[i][j] == Tile::Grass) {
        if (randBrick() == 0 || randBrick() == 1) {
          tiles[i][j] = Tile::Brick;
        }
      }

      if (tiles[i][j] == Tile::Brick) {
        spawnGrass(fieldPositionX + j * scaledTileSize,
                   fieldPositionY + i * scaledTileSize);
        spawnBrick(fieldPositionX + j * scaledTileSize,
                   fieldPositionY + i * scaledTileSize);
      }
      // spawn grass
      if (tiles[i][j] == Tile::Grass || tiles[i][j] == Tile::EmptyGrass) {
        spawnGrass(fieldPositionX + j * scaledTileSize,
                   fieldPositionY + i * scaledTileSize);
      }
      // spawn stone
      if (tiles[i][j] == Tile::Stone) {
        spawnStone(fieldPositionX + j * scaledTileSize,
                   fieldPositionY + i * scaledTileSize);
      }
      // spawn corner
      if (tiles[i][j] == Tile::TopLeftCorner) {
        spawnTopLeftCorner(fieldPositionX + j * scaledTileSize,
                           fieldPositionY + i * scaledTileSize);
      }
      if (tiles[i][j] == Tile::TopRightCorner) {
        spawnTopRightCorner(fieldPositionX + j * scaledTileSize,
                            fieldPositionY + i * scaledTileSize);
      }

      // spawn wall
      if (tiles[i][j] == Tile::LeftWall) {
        spawnLeftWall(fieldPositionX + j * scaledTileSize,
                      fieldPositionY + i * scaledTileSize);
      }
      if (tiles[i][j] == Tile::RightWall) {
        spawnRightWall(fieldPositionX + j * scaledTileSize,
                       fieldPositionY + i * scaledTileSize);
      }
      if (tiles[i][j] == Tile::BottomWall) {
        spawnBottomWall(fieldPositionX + j * scaledTileSize,
                        fieldPositionY + i * scaledTileSize);
      }
      if (tiles[i][j] == Tile::TopWall) {
        spawnTopWall(fieldPositionX + j * scaledTileSize,
                     fieldPositionY + i * scaledTileSize);
      }
    }
  }
}

void LevelScene::spawnGrass(const int x, const int y) {
  auto grass = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::Grass),
      game->getGlobalRenderer());
  grass->setPosition(x, y);
  grass->setSize(tileWidth, tileHeight);
  addObject(grass);
  backgroundObjectLastNumber++;
}
void LevelScene::spawnBrick(const int x, const int y) {
  auto brick = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::Brick),
      game->getGlobalRenderer());
  brick->setPosition(x, y);
  brick->setSize(tileWidth, tileHeight);
  addObject(brick);
  colissions.push_back(std::make_pair(Tile::Brick, brick));
}
void LevelScene::spawnStone(const int x, const int y) {
  auto brick = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::Stone),
      game->getGlobalRenderer());
  brick->setPosition(x, y);
  brick->setSize(tileWidth, tileHeight);
  addObject(brick);
  colissions.push_back(std::make_pair(Tile::Stone, brick));
  backgroundObjectLastNumber++;
}
void LevelScene::spawnTopLeftCorner(const int x, const int y) {
  auto topleft = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::TopLeftCorner),
      game->getGlobalRenderer());
  topleft->setPosition(x, y);
  topleft->setSize(tileWidth, tileHeight);

  addObject(topleft);

  backgroundObjectLastNumber++;
}
void LevelScene::spawnTopRightCorner(const int x, const int y) {
  auto topleft = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::TopRightCorner),
      game->getGlobalRenderer());
  topleft->setPosition(x, y);
  topleft->setSize(tileWidth, tileHeight);

  addObject(topleft);

  backgroundObjectLastNumber++;
}
void LevelScene::spawnBottomLeftCorner(const int x, const int y) {
  auto topleft = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::BottomLeftCorner),
      game->getGlobalRenderer());
  topleft->setPosition(x, y);
  topleft->setSize(tileWidth, tileHeight);

  addObject(topleft);

  backgroundObjectLastNumber++;
}
void LevelScene::spawnBottomRightCorner(const int x, const int y) {
  auto topleft = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::BottomRightCorner),
      game->getGlobalRenderer());
  topleft->setPosition(x, y);
  topleft->setSize(tileWidth, tileHeight);

  addObject(topleft);

  backgroundObjectLastNumber++;
}
void LevelScene::spawnLeftWall(const int x, const int y) {
  auto leftWall = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::LeftWall),
      game->getGlobalRenderer());
  leftWall->setPosition(x, y);
  leftWall->setSize(tileWidth, tileHeight);

  addObject(leftWall);
  colissions.push_back(std::make_pair(Tile::LeftWall, leftWall));
  backgroundObjectLastNumber++;
}
void LevelScene::spawnRightWall(const int x, const int y) {
  auto leftWall = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::RightWall),
      game->getGlobalRenderer());
  leftWall->setPosition(x, y);
  leftWall->setSize(tileWidth, tileHeight);
  colissions.push_back(std::make_pair(Tile::RightWall, leftWall));

  addObject(leftWall);

  backgroundObjectLastNumber++;
}
void LevelScene::spawnTopWall(const int x, const int y) {
  auto leftWall = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::TopWall),
      game->getGlobalRenderer());
  leftWall->setPosition(x, y);
  leftWall->setSize(tileWidth, tileHeight);
  colissions.push_back(std::make_pair(Tile::TopWall, leftWall));

  addObject(leftWall);

  backgroundObjectLastNumber++;
}
void LevelScene::spawnBottomWall(const int x, const int y) {
  auto leftWall = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::BottomWall),
      game->getGlobalRenderer());
  leftWall->setPosition(x, y);
  leftWall->setSize(tileWidth, tileHeight);
  colissions.push_back(std::make_pair(Tile::BottomWall, leftWall));

  addObject(leftWall);

  backgroundObjectLastNumber++;
}

void LevelScene::spawnPlayer(const int x, const int y) {
  player = std::make_shared<Player>(
      game->getAssetManager()->getTexture(Texture::Player),
      game->getGlobalRenderer());
  player->setPosition(x, y);
  player->setSize(48, 48);
  player->setSrcRect(48, 48, 48 * 4, 0);

  addObject(player);
}

void LevelScene::initEnemies() {
  // we need enemy in random tile
  const auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  auto randCount = std::bind(
      std::uniform_int_distribution<int>(minEnemiesOnLevel, maxEnemiesOnLevel),
      std::mt19937(static_cast<unsigned int>(seed)));
  auto randType = std::bind(std::uniform_int_distribution<int>(0, 1),
                            std::mt19937(static_cast<unsigned int>(seed)));
  auto randTexture = std::bind(std::uniform_int_distribution<int>(0, 2),
                               std::mt19937(static_cast<unsigned int>(seed)));
  auto randCellX =
      std::bind(std::uniform_int_distribution<int>(3, TileArrayHeight - 2),
                std::mt19937(static_cast<unsigned int>(seed)));
  auto randCellY =
      std::bind(std::uniform_int_distribution<int>(3, TileArrayWidth - 2),
                std::mt19937(static_cast<unsigned int>(seed)));
  // start enemies spawn
  for (int i = 0; i < randCount(); i++) {
    // try to find suitable tile
    int cellX = randCellX();
    int cellY = randCellY();
    while (tiles[cellX][cellY] == Tile::Brick ||
           tiles[cellX][cellY] == Tile::Stone ||
           tiles[cellX][cellY] == Tile::EmptyGrass) {
      cellX = randCellX();
      cellY = randCellY();
    }
    // spawn enemy
    int textureRand = randTexture();
    spawnEnemy(textureRand == 0
                   ? Texture::Enemy1
                   : (textureRand == 1 ? Texture::Enemy2 : Texture::Enemy3),
               AIType::wandering, fieldPositionX + cellY * scaledTileSize,
               fieldPositionY + cellX * scaledTileSize);
  }
}

void LevelScene::spawnEnemy(Texture texture, AIType type, const int x,
                            const int y) {
  auto enemy = std::make_shared<Enemy>(
      game->getAssetManager()->getTexture(texture), game->getGlobalRenderer());
  enemy->setPosition(x, y);
  enemy->setSize(scaledTileSize, scaledTileSize);
  enemy->setAIType(type);
  addObject(enemy);
  enemies.push_back(enemy);
}

void LevelScene::spawnBomb(Object *object) {
  // one bomb
  if (this->bomb || !object) {
    return;
  }

  //
  int bombX = object->getPositionX() + 52 / 2;
  int bombY = object->getPositionY() + 63 / 2 - 70;

  bombX = std::round(bombX / scaledTileSize);
  bombY = std::round(bombY / scaledTileSize);

  bomb = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::Bomb),
      game->getGlobalRenderer());
  bomb->setSize(scaledTileSize, scaledTileSize);
  bomb->setPosition(bombX * scaledTileSize, bombY * scaledTileSize + 70);
  insertObject(this->bomb, backgroundObjectLastNumber);

  // animation

  auto animation = std::make_shared<Animation>();
  animation->addFrame(Frame(0, 0, tileWidth, tileHeight));
  animation->addFrame(Frame(tileWidth * 1, 0, tileWidth, tileHeight));

  animation->setSprite((bomb.get()));
  bomb->addAnimation(animation);

  const int bomCellX =
      static_cast<int>(round(bomb->getPositionX() - fieldPositionX) /
                       static_cast<float>(scaledTileSize));
  const int bombCellY =
      static_cast<int>(round(bomb->getPositionY() - fieldPositionY) /
                       static_cast<float>(scaledTileSize));
  tiles[bombCellY][bomCellX] = Tile::Bomb;

  // timer
  bombTimer = bombTimerStart;
  animation->play();
}

void LevelScene::spawnBang(Object *object) {
  // change bomb to grass
  const int bombCellX =
      static_cast<int>(round((bomb->getPositionX() - fieldPositionX) /
                             static_cast<float>(scaledTileSize)));
  const int bombCellY =
      static_cast<int>(round((bomb->getPositionY() - fieldPositionY) /
                             static_cast<float>(scaledTileSize)));
  tiles[bombCellY][bombCellX] = Tile::Grass;

  // render bang
  for (int i = 0; i < bangSpawnCells; i++) {
    auto bang = std::make_shared<Sprite>(
        game->getAssetManager()->getTexture(Texture::Explosion),
        game->getGlobalRenderer());
    bang->setSize(scaledTileSize, scaledTileSize);
    bang->setPosition(object->getPositionX() + bangPos[i][0] * scaledTileSize,
                      object->getPositionY() + bangPos[i][1] * scaledTileSize);
    addObject(bang);
    bangs.push_back(bang);
    // change to bang
    const int bangCellX =
        static_cast<int>(round((bang->getPositionX() - fieldPositionX) /
                               static_cast<float>(scaledTileSize)));
    const int bangCellY =
        static_cast<int>(round((bang->getPositionY() - fieldPositionY) /
                               static_cast<float>(scaledTileSize)));
    tiles[bangCellY][bangCellX] = Tile::Bang;
    // animation
    auto animation = std::make_shared<Animation>();
    for (unsigned int j = 1; j < 12; j++) {
      animation->addFrame(Frame(tileWidth * j, 0, tileWidth, tileWidth));
    }
    animation->setSprite(bang.get());
    bang->addAnimation(animation);
    animation->play();
  }
  bangTimer = bangTimerStart;
}

void LevelScene::spawnDoor(Object *object) {
  door = std::make_shared<Sprite>(
      game->getAssetManager()->getTexture(Texture::Door),
      game->getGlobalRenderer());
  door->setSize(scaledTileSize, scaledTileSize);
  door->setPosition(object->getPositionX(), object->getPositionY());
  insertObject(door, backgroundObjectLastNumber);
}

void LevelScene::finish() const {}

void LevelScene::gameOver() const {}

void LevelScene::exit() const {}

void LevelScene::event(SDL_Event &event) {
  Scene::event(event);

  if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) &&
      event.key.repeat == 0) {
    updateMovement(event.type == SDL_KEYDOWN ? true : false,
                   event.key.keysym.scancode);
  }
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
      gameOver();
      isWin = false;
      gameOverTimer = winTimerStart;
    }
    // we can spawn a bomb by space press
    else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
      if (!isGameOver) {
        spawnBomb(player.get());
      }
    }
    // we can pause a game by pressing enter key
    else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
      isPaused = !isPaused;

    }
    // stage complete cheat
    else if (event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
      gameOver();
      isWin = true;
      score += stageCompleteScore * 100;
      gameOverTimer = winTimerStart;
    }
  }
}

void LevelScene::update(const uint32_t delta) {
  Scene::update(delta);
  // pause
  if (isPaused) {
    return;
  }
  Scene::update(delta);
  // update collision of player
  updateplayerColisson();
  // update collision of enemies
  updateEnemyColisson();
  // update collision of bricks
  updateBangColisson();
  // update camera
  updateCamera();
  // update timers
  updateTimer(delta);
}
void LevelScene::updateTimer(const uint32_t delta) {
  // update level timer
  levelTimer -= delta;
  levelTimerDelta += delta;
  if (levelTimerDelta >= levelTimerUpdateText) {
    updateLevelTimer();
  }
  // update bomb timer
  if (bomb != nullptr) {
    updateBombTimer(delta);
  }
  // update bang timer
  if (bangs.size() > 0) {
    updateBangTimer(delta);
  }
  // update game over timer
  if (isGameOver) {
    updateGameOverTimer(delta);
  }

  // finish level if level timer is 0
  if (levelTimer <= 0 && !isGameOver) {
    gameOver();
    isWin = false;
    gameOverTimer = winTimerStart;
  }
}

void LevelScene::updateLevelTimer() {
  if (levelTimer < 0) {
    return;
  }
  levelTimerDelta = 0;
  const int timeInSec = static_cast<int>(levelTimer / 1000.0f);
  std::string timeString = std::to_string(timeInSec);
  while (timeString.size() < 3) {
    timeString = "0" + timeString;
  }
  timerNumber->setText(timeString);
}

void LevelScene::updateBombTimer(const uint32_t delta) {

  if (bombTimer > 0) {
    bombTimer -= delta;
  } else {
    spawnBang(bomb.get());
    deleteObject(bomb);
    bomb = nullptr;
  }
}

void LevelScene::updateBangTimer(const uint32_t delta) {

  if (bangTimer > 0) {
    bangTimer -= delta;
  } else {
    for (auto &bang : bangs) {
      deleteObject(bang);
      // change to grass
      const int bangCellX =
          static_cast<int>(round((bang->getPositionX() - fieldPositionX) /
                                 static_cast<float>(scaledTileSize)));
      const int bangCellY =
          static_cast<int>(round((bang->getPositionY() - fieldPositionY) /
                                 static_cast<float>(scaledTileSize)));
      tiles[bangCellY][bangCellX] = baseTile[bangCellY][bangCellX];
    }
    bangs.clear();
  }
}

void LevelScene::updateGameOverTimer(const uint32_t delta) {
  if (gameOverTimer > 0) {
    gameOverTimer -= delta;
  } else {
    finish();
  }
}

void LevelScene::updateMovement(const bool isPressed, const int keycode) {
  if (player == nullptr) {
    return;
  }
  // on press we start movement
  if (isPressed) {
    switch (keycode) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      PlayerDirectionY -= 1;
      break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      PlayerDirectionY += 1;
      break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
      PlayerDirectionX -= 1;
      break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
      PlayerDirectionX += 1;
      break;
    default:
      break;
    }
  }
  // on release we stop moving
  else {
    switch (keycode) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      PlayerDirectionY += 1;
      break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      PlayerDirectionY -= 1;
      break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
      PlayerDirectionX += 1;
      break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
      PlayerDirectionX -= 1;
      break;
    default:
      break;
    }
  }
  Direction direction = Direction::NONE;
  if (PlayerDirectionX != 0) {
    if (PlayerDirectionX > 0) {
      direction = Direction::RIGHT;
    } else {
      direction = Direction::LEFT;
    }
  } else if (PlayerDirectionY != 0) {
    if (PlayerDirectionY > 0) {
      direction = Direction::DOWN;
    } else {
      direction = Direction::UP;
    }
  }
  // apply direction
  player->setDirection(direction);
}

void LevelScene::updateCamera() {}

void LevelScene::updateScore() {
  std::string scoreText = std::to_string(score);
  scoreNumber->setText(scoreText);
  scoreNumber->setSize(static_cast<int>(timerNumber->getWidth() / 3.0f) *
                           static_cast<int>(scoreText.size()),
                       scoreNumber->getHeight());
  scoreNumber->setPosition(game->getWindowWidth() / 2 -
                               scoreNumber->getWidth() / 2,
                           scoreNumber->getPositionY());
}

void LevelScene::updateplayerColisson() {
  if (player == nullptr) {
    return;
  }
  if (!player->isMoving()) {
    return;
  }
  SDL_Rect playerRect = player->getRect();
  playerRect.w = static_cast<int>(playerRect.w * 0.9);
  playerRect.h = static_cast<int>(playerRect.h * 0.9);

  for (const auto collison : colissions) {
    if (isColissonDetect(playerRect, collison.second->getRect())) {

      // std::cout << "collison with " << collison.first << std::endl;
      int posX = std::round(player->getRect().x / 48.0f);
      std::cout << player->getRect().x << " " << player->getRect().y
                << std::endl;
      int posY = std::round((player->getRect().y - 70) / 48.0f);
      std::cout << posX << " " << posY << std::endl;
      player->setPosition(posX * scaledTileSize, posY * scaledTileSize + 70);
    }
  }
}

void LevelScene::updateEnemyColisson() {
  for (const auto &enemy : enemies) {
    // iterate drawables for collision
    for (const auto &collisionObject : colissions) {
      // check for block collision
      if (isColissonDetect(enemy->getRect(),
                           collisionObject.second->getRect())) {
        // stop moving on collision detection
        enemy->setMove(false);
        int posX = std::round(enemy->getRect().x / 48.0f);
        std::cout << enemy->getRect().x << " " << enemy->getRect().y
                  << std::endl;
        int posY = std::round((enemy->getRect().y - 70) / 48.0f);
        std::cout << posX << " " << posY << std::endl;
        enemy->setPosition(posX * scaledTileSize, posY * scaledTileSize + 70);
      }
    }
    // if (bomb && isColissonDetect(enemy->getRect(), bomb->getRect())) {
    //   // stop moving on collision detection
    //   enemy->setMove(false);
    //   enemy->revertLastMove();
    // }
    // // check for player collision
    // if (player != nullptr) {
    //   // set width to smaller size
    //   SDL_Rect playerRect = player->getRect();
    //   playerRect.w = static_cast<int>(playerRect.w * 0.2);
    //   playerRect.h = static_cast<int>(playerRect.h * 0.2);
    //   if (isColissonDetect(playerRect, enemy->getRect())) {
    //     // player killed by enemy
    //     deleteObject(player);
    //     player = nullptr;
    //     gameOver();
    //   }
    // }
    // if (player != nullptr) {
    //   // can attack?
    //   if (!enemy->isMoveToCell() && enemy->canAttack()) {
    //     // check for attack radius
    //     if (abs(player->getPositionX() + player->getWidth() / 2 -
    //             enemy->getPositionX() - enemy->getWidth() / 2) <
    //             enemy->getAttackRadius() &&
    //         abs(player->getPositionY() + player->getHeight() / 2 -
    //             enemy->getPositionY() - enemy->getHeight() / 2) <
    //             enemy->getAttackRadius()) {
    //       // start follow to player
    //       toFollowPlayer(enemy);
    //     }
    //   }
    // }
  }
}

void LevelScene::updateBangColisson() {}

bool LevelScene::isColissonDetect(const SDL_Rect &rect1,
                                  const SDL_Rect &rect2) {
  // check for collision
  if (rect1.x + rect1.w / 2 <= rect2.x - rect2.w / 2)
    return false;
  if (rect1.x - rect1.w / 2 >= rect2.x + rect2.w / 2)
    return false;
  if (rect1.y + rect1.h / 2 <= rect2.y - rect2.h / 2)
    return false;
  if (rect1.y - rect1.h / 2 >= rect2.y + rect2.h / 2)
    return false;

  return true;
}

void LevelScene::destroyBrick(std::shared_ptr<Object> brick) {}

void LevelScene::toFollowPlayer(std::shared_ptr<Enemy> enemy) {}
