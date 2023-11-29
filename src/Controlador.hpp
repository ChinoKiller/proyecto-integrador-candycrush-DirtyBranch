#pragma once
#include "./GameBoard.hpp"
#include "./Levels/Level.hpp"

class Controlador {
public:
  // Default constructor
  Controlador(sf::RenderWindow& window):window(window){}
  ~Controlador(){}
  // Función que corre el juego
  int runGame();
private:
  sf::RenderWindow& window;
  // Nivel actual
  Level currentLevel;
  // Numero de nivel actual
  int currentLevelNumber = 1;
};