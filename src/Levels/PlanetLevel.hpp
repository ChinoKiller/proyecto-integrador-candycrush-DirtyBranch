#pragma once
#include "Level.hpp"

// Clase para los niveles de los planetas (9x9)
class PlanetLevel : public Level {
  protected:
    // Puntuación necesaria para pasar al siguiente nivel
    int scoreToNextLevel;
  public:
    // Constructor default
    PlanetLevel(){}
    // Constructor por parámetro de niveles de planetas
    PlanetLevel(int levelNumber) 
    : Level(levelNumber)
    { 
      switch (this->levelNumber)
      {
      case 1:
        this->levelName = "Neptuno";
        this->moves = MOVES_LEVEL_1;
        this->scoreToNextLevel = GOAL_SCORE_1;
        break;
      case 2:
        this->levelName = "Urano";
        this->moves = MOVES_LEVEL_2;
        this->scoreToNextLevel = GOAL_SCORE_2;
        break;
      case 3:
        this->levelName = "Saturno";
        this->moves = MOVES_LEVEL_3;
        this->scoreToNextLevel = GOAL_SCORE_3;
        break;
      case 4:
        this->levelName = "Jupiter";
        this->moves = MOVES_LEVEL_4;
        this->scoreToNextLevel = GOAL_SCORE_4;
        break;
      case 5:
        this->levelName = "Marte";
        this->moves = MOVES_LEVEL_5;
        this->scoreToNextLevel = GOAL_SCORE_5;
        break;
      case 6:
        this->levelName = "Tierra";
        this->moves = MOVES_LEVEL_6;
        this->scoreToNextLevel = GOAL_SCORE_6;
        break;
      case 7:
        this->levelName = "Venus";
        this->moves = MOVES_LEVEL_7;
        this->scoreToNextLevel = GOAL_SCORE_7;
        break;
      case 8:
        this->levelName = "Mercurio";
        this->moves = MOVES_LEVEL_8;
        this->scoreToNextLevel = GOAL_SCORE_8;
        break;
      default:
        break;
      }
    }
    // Correr nivel
    int runLevel() override;
};