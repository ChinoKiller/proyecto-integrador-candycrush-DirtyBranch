#pragma once
#include <iostream>
#include <string>
#include "../GameBoard.hpp"
#include "../DEFINITIONS.HPP"

// Clase Level
class Level {
  protected:
    // Instancia del GameBoard
    GameBoard& getGameBoard(){
      return this->currentGameBoard;
    };
  //GameBoard currentGameBoard;
    GameBoard currentGameBoard;
    // Numero del nivel en el que estamos, (son 10 niveles) 
    int levelNumber;
    // Nombre del nivel 
    std::string levelName;
    // Movimientos restantes
    int moves;
    // Puntuación
    int score = 0;
    // Booleano que me indica si tengo que pasar al siguiente nivel o no
    bool toNextLevel = false;
    // validar numero del nivel (no virtual, igual para todos los niveles)
    // generar nombre del nivel (para sol y pluton, se pone en el constructor)
    // generar puntuación a obtener para seguir al prox nivel (para sol y planetas)
    // generar numero de movimientos (para sol y planetas)
    // revisar si sigue al proximo nivel (no virtual, igual para todos los niveles)
    // generar tamaño del tablero de juego según el nivel
    // mensaje de ganado/siguiente nivel
  public:
    // Constructor por default
    Level(){}
    // Constructor por parámetro 
    Level(int levelNumber) : levelNumber(levelNumber){}
    // Destructor
    ~Level(){}
    // Get instance de Level
    static Level& getInstance();




    // Correr nivel
    virtual int runLevel() = 0;
};
