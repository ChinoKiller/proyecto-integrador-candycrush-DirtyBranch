#pragma once
#include "Level.hpp"

// clase para el nivel del sol (10x10)
class SunLevel: public Level {
  protected:
    // Puntuación necesaria para pasar al siguiente nivel
    int scoreToNextLevel;
  public:
    // Constructor del nivel sol
    SunLevel() {
      this->levelName = "Sol";
      this->moves = MOVES_LEVEL_9;
      this->scoreToNextLevel = GOAL_SCORE_9;
    }
    // Correr nivel
    int runLevel() override;
};
