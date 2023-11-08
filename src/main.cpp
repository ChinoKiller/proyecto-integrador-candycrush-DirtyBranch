#include "Levels/Level.hpp"
#include "Levels/PlanetLevel.hpp"
#include "Levels/SunLevel.hpp"
#include "Levels/PlutoLevel.hpp"
#include "GameBoard.hpp"

int main() {
  // Nivel que quiero iniciar
  int currentLevelNumber = 1;
  // Si quiero inicializar el nivel de los planetas
  if (currentLevelNumber >= 1 && currentLevelNumber <= 8) {
    // Obtener una instancia de Level, que represente al nivel de juego actual
    // Se pasa por parámetro el numero del nivel actual de juego
    PlanetLevel currentLevel = PlanetLevel(currentLevelNumber);
    currentLevel.runLevel();
  } 
  // Si quiero inicializar el nivel del sol
  else if (currentLevelNumber == 9) {
    SunLevel currentLevel = SunLevel();
    currentLevel.runLevel();
  }
  // Si quiero inicializar el nivel de pluton
  else if (currentLevelNumber == 10) {
    PlutoLevel currentLevel = PlutoLevel();
    currentLevel.runLevel();
  }
  // Input invalido
  else {
    std::cout << "Nivel Invalido" << std::endl;
  }
  return EXIT_SUCCESS;
}