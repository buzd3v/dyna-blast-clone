#pragma once
#include "Global.h"
#include <stack>

struct Cell {
  int parentRow, parentColumn; // row and column of parent
  double f, g, h;              // f = g + h
};
/**
 * @brief Find best path to destination using A* algorith
 *
 * @param src - source point
 * @param dest - destination point
 * @return std::pair<int, int> - first cell to move
 */
std::pair<int, int> findBestCell(Tile (&grid)[TileArrayHeight][TileArrayWidth],
                                 const std::pair<int, int> &src,
                                 const std::pair<int, int> &dest);