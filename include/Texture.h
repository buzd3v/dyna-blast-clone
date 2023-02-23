#include "Global.h"
#pragma one
#include <iostream>

enum class Texture : int {
  MenuBack,
  Stone,
  Grass,
  Brick,
  Player,
  Enemy1,
  Enemy2,
  Enemy3,
  Bomb,
  Explosion,
  Door,
  TopLeftCorner,
  TopRightCorner,
  BottomLeftCorner,
  BottomRightCorner,
  TopWall,
  BottomWall,
  LeftWall,
  RightWall,
  ScoreTable
};
class EnumHash {
public:
  template <typename T> std::size_t operator()(T &t) const {
    return static_cast<std::size_t>(t);
  }
};