#pragma once
#include "Level.hpp"

// clase para nivel extra pluton (8x8)
class PlutoLevel: public Level {
  // para el nivel bonus, poner un timer
  protected:
    // Puntuación necesaria para pasar al siguiente nivel
    int secondsToEnd;
  public:
    // Constructor del nivel sol
    PlutoLevel() {
      this->levelName = "Pluton";
      this->moves = MOVES_LEVEL_9;
      this->secondsToEnd = SECONDS_BONUS_LEVEL;
    }
    // Correr nivel
    int runLevel() override;
};