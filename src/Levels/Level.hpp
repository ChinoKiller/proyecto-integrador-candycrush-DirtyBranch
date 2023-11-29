#pragma once
#include <iostream>
#include <string>
#include "../GameBoard.hpp"
#include "../DEFINITIONS.HPP"

// Clase Level
class Level {
  protected:
    // Instancia del tablero de juego
    GameBoard currentGameBoard;
    // Numero del nivel en el que estamos, (son 9 niveles y un nivel extra) 
    int levelNumber;
    // Nombre del nivel 
    std::string levelName;
    // Movimientos restantes
    int moves;
    // Puntuación
    int currentScore;
    // Puntuación a alcanzar
    int goalScore;
  public:
    // Constructor por default
    Level(){}
    // Constructor por parámetro 
    Level(int levelNumber);
    // Destructor
    ~Level(){}
    // Get instance de Level
    static Level& getInstance();
    // Correr nivel
    bool runLevel();
};
