#pragma once
#include <iostream>

// clase Levels
class Levels {
  protected: 
    int levelNumber;
    std::string levelName;
    int moves;
    int score;
    int scoreToNextLevel;
    bool toNextLevel;
  public:
    // constructor
    Levels();
    // destructor
    ~Levels();
    // generar nivel
    virtual int generateLevel();
    // validar numero del nivel (no virtual, igual para todos los niveles)
    // generar nombre del nivel (para sol y pluton, se pone en el constructor)
    // generar puntuación a obtener para seguir al prox nivel (para sol y planetas)
    // generar numero de movimientos (para sol y planetas)
    // revisar si sigue al proximo nivel (no virtual, igual para todos los niveles)
    // generar tamaño del tablero de juego según el nivel
    // mensaje de ganado/siguiente nivel
};

// clases que heredan de Levels
// clase para los niveles de los planetas (9x9)
class PlanetLevel : public Levels {

};

// clase para el nivel del sol (10x10)
class SunLevel: public Levels {
  
};

// clase para nivel extra pluton (8x8)
class PlutoLevel: public Levels {
  // para el nivel bonus, poner un timer
};