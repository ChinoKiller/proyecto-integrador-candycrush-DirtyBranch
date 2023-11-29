#pragma once
#include "./GameBoard.hpp"
#include "./Levels/Level.hpp"

class Controlador {
public:
  // Default constructor
  Controlador(): currentLevel(currentLevelNumber){}
  ~Controlador(){}
  // Función que corre el juego
  int runGame();
private:
  // Nivel actual
  Level currentLevel;
  // Numero de nivel actual
  int currentLevelNumber = 1;
};