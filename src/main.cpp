#include "Level.hpp"

int main() {
  // Obtener una instancia de Level, que represente al nivel de juego actual
  Level& currentLevel = Level::getInstance();
  // Generar el nivel actual 
  currentLevel.generateLevel();
  return EXIT_SUCCESS;
}