#include "Level.hpp"

// Para obtener solo una instancia del Level
Level& Level::getInstance() {
  static Level Level;
  return Level;
}

int Level::generateLevel(){
  // Obtener instancia de gameBoard (tablero de juego)
  this->currentGameBoard = GameBoard::getInstance();
  // Inicializar matriz de juego según el tamaño designado para cada nivel
  // revisar que el numero de nivel este correcto
  // si el numero del nivel [1-7], tamaño de 9x9
  // si el numero del nivel == 8, tamaño de 10x10
  // si el numero del nivel == 9, tamaño de 8x8 
  // Correr el tablero de juego
  currentGameBoard.runGameBoard();
  return EXIT_SUCCESS;
}
