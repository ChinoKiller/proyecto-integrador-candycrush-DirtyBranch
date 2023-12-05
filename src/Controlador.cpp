#include "Controlador.hpp"


void Controlador::setCurrentLevel(int newLevel) { 
    this->currentLevelNumber = newLevel;
}



bool Controlador::runGame() {
    // Crear level
    this->currentLevel = Level(currentLevelNumber, sfxEnable);
    // Verificar si gano el juego
    if (currentLevel.runLevel(this->window)) {
        return true;
    }
    return false;
}
