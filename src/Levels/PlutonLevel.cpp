#include "PlutoLevel.hpp"

int PlutoLevel::runLevel(){
  // Inicializar matriz de juego según el tamaño designado para cada nivel
  // si el numero del nivel [1,8], tamaño de 9x9
  currentGameBoard = GameBoard();
  // Inicializar matriz, si el tamaño es válido
  if(!(currentGameBoard.initMatrix(BOARD_SIZE_PLUTO))) {
    return EXIT_FAILURE;
  }
  
  // Imprimir header
  std::cout
    << "₊ °✦ ‧  ‧ ₊ ˚✧" << std::endl
    << "★ Nivel: " << this->levelName << std::endl
    << "★ Tiempo restante: " << this->secondsToEnd << std::endl
    << "★ Movimientos restantes: " << this->moves << std::endl
    << "₊ °✦ ‧  ‧ ₊ ˚✧" << std::endl;
  // Correr el tablero de juego
  currentGameBoard.runGameBoard();
  this->score = currentGameBoard.punctuation;
  return EXIT_SUCCESS;
}