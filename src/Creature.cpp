#include "../include//Creature.h"

bool Creature::isMoving() { return moving; }
void Creature::setMove(bool isMove) { this->moving = isMove; }

void Creature::revertLastMove() {
  setPosition(getPositionX() - preDeltaX, getPositionY() - preDeltaY);
}