#pragma once

#include <iostream>

enum Tile {
  TopLeftCorner,
  TopRightCorner,
  BottomLeftCorner,
  BottomRightCorner,
  TopWall,
  BottomWall,
  LeftWall,
  RightWall,
  Stone,
  Grass,
  Brick,
  Bomb,
  Bang,
  EmptyGrass,
};

const int PlayerStartX = 1;
const int PlayerStartY = 1;

const int tileWidth = 48;
const int tileHeight = 48;

const uint brickSpawnRandom = 10;          // less value => more brick
const uint doorSpawnRandom = 10;           // less value => further door
const unsigned int bangSpawnCells = 5;     // bang spawn number of cells
const unsigned int minEnemiesOnLevel = 2;  // minimum enemies count on level
const unsigned int maxEnemiesOnLevel = 10; // maximum enemies count on level
const int bangPos[9][2] = {{0, 0},  {0, 1}, {0, -1}, {1, 0}, {-1, 0},
                           {-2, 0}, {2, 0}, {0, -2}, {0, 2}};

const int TileArrayWidth = 19;
const int TileArrayHeight = 11;

const Tile baseTile[11][19]{
    {Tile::TopLeftCorner, Tile::TopWall, Tile::TopWall, Tile::TopWall,
     Tile::TopWall, Tile::TopWall, Tile::TopWall, Tile::TopWall, Tile::TopWall,
     Tile::TopWall, Tile::TopWall, Tile::TopWall, Tile::TopWall, Tile::TopWall,
     Tile::TopWall, Tile::TopWall, Tile::TopWall, Tile::TopWall,
     Tile::TopRightCorner},
    {Tile::LeftWall, Tile::EmptyGrass, Tile::EmptyGrass, Tile::EmptyGrass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::EmptyGrass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::EmptyGrass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass,
     Tile::Stone, Tile::Grass, Tile::Stone, Tile::Grass, Tile::Stone,
     Tile::Grass, Tile::Stone, Tile::Grass, Tile::RightWall},
    {Tile::LeftWall, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass, Tile::Grass,
     Tile::Grass, Tile::Grass, Tile::Grass, Tile::RightWall},
    {Tile::BottomWall, Tile::BottomWall, Tile::BottomWall, Tile::BottomWall,
     Tile::BottomWall, Tile::BottomWall, Tile::BottomWall, Tile::BottomWall,
     Tile::BottomWall, Tile::BottomWall, Tile::BottomWall, Tile::BottomWall,
     Tile::BottomWall, Tile::BottomWall, Tile::BottomWall, Tile::BottomWall,
     Tile::BottomWall, Tile::BottomWall, Tile::BottomWall}};
