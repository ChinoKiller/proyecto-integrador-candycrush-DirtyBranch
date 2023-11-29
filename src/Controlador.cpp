#include "Controlador.hpp"

int Controlador::runGame() {
    // Si se gana el nivel seguir al otro
    while (this->currentLevelNumber < 10 /*&& (sigue en ventana de juego)*/) {
        this->currentLevel = Level(currentLevelNumber);
        currentLevel.runLevel();
        std::cout<< "Gano el nivel" <<std::endl;
        this->currentLevelNumber++;
        std::cout<< this->currentLevelNumber <<std::endl;
    }
    return EXIT_SUCCESS;
}
