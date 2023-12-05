#pragma once
#include "./GameBoard.hpp"
#include "./Levels/Level.hpp"

class Controlador {
public:
  // Default constructor
  Controlador(sf::RenderWindow& window, int& currentLevelNumber, int& sfxEnable)
    :window(window), currentLevelNumber(currentLevelNumber), sfxEnable(sfxEnable){}
  ~Controlador(){}
  // Función que corre el juego
  bool runGame();
  int getCurrentLevel() { return this->currentLevelNumber;}
  void setCurrentLevel(int newLevel); 
private:
  sf::RenderWindow& window;
  // Nivel actual
  Level currentLevel;
  // Numero de nivel actual
  int& currentLevelNumber;
  int& sfxEnable;
};