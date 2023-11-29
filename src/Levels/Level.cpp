#include "Level.hpp"

// Constructor por parámetro de niveles de planetas y sol
Level::Level(int levelNumber): levelNumber(levelNumber)
{ 
    switch (this->levelNumber)
    {
    case 1:
        this->levelName = "Neptuno";
        this->moves = MOVES_LEVEL_1;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_1;
        break;
    case 2:
        this->levelName = "Urano";
        this->moves = MOVES_LEVEL_2;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_2;
        break;
    case 3:
        this->levelName = "Saturno";
        this->moves = MOVES_LEVEL_3;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_3;
        break;
    case 4:
        this->levelName = "Jupiter";
        this->moves = MOVES_LEVEL_4;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_4;
        break;
    case 5:
        this->levelName = "Marte";
        this->moves = MOVES_LEVEL_5;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_5;
        break;
    case 6:
        this->levelName = "Tierra";
        this->moves = MOVES_LEVEL_6;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_6;
        break;
    case 7:
        this->levelName = "Venus";
        this->moves = MOVES_LEVEL_7;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_7;
        break;
    case 8:
        this->levelName = "Mercurio";
        this->moves = MOVES_LEVEL_8;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_8;
        break;
    case 9:
        this->levelName = "Sol";
        this->moves = MOVES_LEVEL_9;
        this->currentScore = 0;
        this->goalScore = GOAL_SCORE_9;
        break;
    default:
        break;
    }
}

bool Level::runLevel(sf::RenderWindow& window) {
    // Inicializar matriz de juego según el tamaño designado para cada nivel
    // si el numero del nivel [1,8], tamaño de 9x9
    currentGameBoard = GameBoard();
    // Tamaño de matriz de juego
    int boardSize = BOARD_SIZE_PLANETS;
    if(this->levelNumber == 9) {
        boardSize = BOARD_SIZE_SUN;
    }
    // Inicializar matriz, si el tamaño es válido
    if(!(currentGameBoard.initMatrix(boardSize))) {
        return EXIT_FAILURE;
    }
    // Imprimir header
    std::cout
    << std::endl
    << "₊ °✦ ‧  ‧ ₊ ˚✧" << std::endl
    << "★ Nivel: " << this->levelName << std::endl
    << "★ Puntuación para sig nivel: " << this->goalScore << std::endl
    << "★ Movimientos restantes: " << this->moves << std::endl
    << "₊ °✦ ‧  ‧ ₊ ˚✧" << std::endl;
    // Correr el tablero de juego
    return currentGameBoard.runGameBoard(this->levelNumber, window, this->moves, this->goalScore);
}

