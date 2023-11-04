#pragma once
#include <iostream>
#include "GameBoard.hpp"

// clase Level
class Level {
  protected:
    // Instancia del GameBoard
    GameBoard currentGameBoard;
    // Numero del nivel en el que estamos, (son 9 niveles) 
    int levelNumber;
    // Nombre del nivel 
    std::string levelName;
    // Movimientos restantes
    int moves;
    // Puntuación
    int score;
    // Puntuación necesaria para pasar al siguiente nivel
    int scoreToNextLevel;
    // Booleano que me indica si tengo que pasar al siguiente nivel o no
    bool toNextLevel;
    // validar numero del nivel (no virtual, igual para todos los niveles)
    // generar nombre del nivel (para sol y pluton, se pone en el constructor)
    // generar puntuación a obtener para seguir al prox nivel (para sol y planetas)
    // generar numero de movimientos (para sol y planetas)
    // revisar si sigue al proximo nivel (no virtual, igual para todos los niveles)
    // generar tamaño del tablero de juego según el nivel
    // mensaje de ganado/siguiente nivel
  public:
    // constructor por default
    Level(){}
    // constructor por parámetro 
    Level(int levelNumber, std::string levelName, int moves, int score, int scoreToNextLevel)
      : levelNumber(levelNumber)
      , levelName(levelName)
      , moves(moves)
      , score(score)
      , scoreToNextLevel(scoreToNextLevel)
    {}
    // destructor
    ~Level(){}
    // get instance de Level
    static Level& getInstance();
    // generar nivel a jugar
    int generateLevel();
};

// clases que heredan de Level
// clase para los niveles de los planetas (9x9)
class PlanetLevel : public Level {

};

// clase para el nivel del sol (10x10)
class SunLevel: public Level {
  
};

// clase para nivel extra pluton (8x8)
class PlutoLevel: public Level {
  // para el nivel bonus, poner un timer
};