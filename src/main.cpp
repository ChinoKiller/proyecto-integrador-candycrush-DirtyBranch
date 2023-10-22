#include "GameBoard.hpp"

int main() {
  // get instance de GameBoard
  GameBoard& matchBoard = GameBoard::getInstance();
  matchBoard.runGameBoard();
  return EXIT_SUCCESS;
}