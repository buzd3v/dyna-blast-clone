#include "../include/Game.h"
#include <iostream>
#include <memory>
#include <random>
#include <unordered_map>

int main(int argc, char *argv[]) {
  std::shared_ptr<Game> game = std::make_shared<Game>("Bomberman", 900, 600);
  game->run();
}