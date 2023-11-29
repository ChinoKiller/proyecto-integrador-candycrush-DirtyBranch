#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>


// Declaración funciones ensambla
extern "C" {
    void _initMatrix(int* matriz, int size);
    void _setValue(int* matriz, int rows, int cols, int row, int col, int value);
    bool _isSameColor(int* matriz, int row, int col, int color, int tam);
    int _getCellValue(int* matriz, int rows, int cols, int row, int col);
    int _pointsSystem(int combinationPoints, int currentScore); 
    bool _readColRowSize(int rowColSize); 
    //bool _withinMatrix(int row, int col, int rowSize, int colSize);
    //bool _elementsAreAdjacent(int rowCurrent, int colCurrent, int rowDestination, int colDestination);
    //bool _eliminateElement(int* matriz, int rowSize, int colSize, int row, int col);
    
}


// clase GameBoard
class GameBoard {
  private:
    std::map<std::string, sf::Texture> texturasAliens;
    std::string levelName;
    // Tamaño de las filas de la matriz
    int rowSize;
    // Tamaño de las columnas de la matriz
    int colSize;
    // Matriz dinámica, para que se pueda ajustar según el tamaño del tablero deseado
    int* gameMatrix;
    // Inicializar sistema de puntuación
    int currentScore = 0;
    // Nivel actual en numero

    // Matriz con las formas L y T, incluyendo todas sus rotaciones
    int LTshapes[8][5][2] = {
      // 1         2         3         4         5
      {{+0, +0}, {+1, +0}, {+2, +0}, {+2, +1}, {+2, +2}},  // L1
      {{+0, +0}, {+1, +0}, {+2, -2}, {+2, -1}, {+2, +0}},  // L2
      {{+0, +0}, {+0, +1}, {+0, +2}, {+1, +0}, {+2, +0}},  // L3
      {{+0, +0}, {+0, +1}, {+0, +2}, {+1, +2}, {+2, +2}},  // L4
      {{+0, +0}, {+0, +1}, {+0, +2}, {+1, +1}, {+2, +1}},  // T1
      {{+0, +0}, {+1, +0}, {+2, -1}, {+2, +0}, {+2, +1}},  // T2
      {{+0, +0}, {+1, +0}, {+1, +1}, {+1, +2}, {+2, +0}},  // T3
      {{+0, +0}, {+1, -2}, {+1, -1}, {+1, +0}, {+2, +0}},  // T4
    };
    // Configuración que indica si solo se van a buscar combinaciones 
    // o si también se van a eliminar las combinaciones encontradas. 
    enum combinationSetting {
      SEARCH = 0,
      DESTROY = 1
    };

  // Funciones privadas
  private:
    void dibujarMatriz(sf::RenderWindow& ventana);
    void cargarTexturas();
    void showWindow(int currentLevelNumber, sf::RenderWindow& window);
    // Leer tamaño de la matriz, retorna bool que indica si lo leyó correctamente
    bool readColRowSize(int rowColSize);
    // Crear matriz dinámica, retorna int que indica si lo inicializó correctamente
    bool initMatrix(int rowColSize);
    // Imprimir la matriz de juego
    int printMatrix();
    // Generar tablero aleatoriamente
    int generateRandomBoard();
    // Generar números aleatorios en espacios en blanco
    int generateRandomNewNumber();
    // Revisar que no nos salgamos de la matriz
    bool withinMatrix(int row, int col);
    // Son del mismo color
    bool isSameColor(int row, int col, int color);
    // Función que busca combinaciones, puede o eliminarlas o solo buscarlas
    bool searchOrDestroy(enum combinationSetting setSearchOrDestroy);
    // Buscar posibles jugadas
    bool findPosibleCombinations();
    // Cambiar elementos
    void swapElement(int rowDestination, int colDestination, int rowCurrent, int colCurrent); 
    // Hacer una jugada
    void play();
    // Revisar si 2 elementos son adyacentes
    bool elementsAreAdjacent(int rowCurrent, int colCurrent, int rowDestination, int colDestination);
    //genera un numero aleatorio del 1 al 6
    int generateNumberAtRandom();
    // Revisar que hayan combinaciones, revisar según prioridad
    // Buscar verticales de 5 o mas
    bool searchBigVertical(enum combinationSetting setSearchOrDestroy);
    // Buscar vertical de 4 o 3, según parámetro
    bool searchVertical(enum combinationSetting setSearchOrDestroy, int verticalLength);
    // Buscar horizontales de 5 o mas
    bool searchBigHorizontal(enum combinationSetting setSearchOrDestroy);
    // Buscar horizontales de 4 o 3, según el parámetro
    bool searchHorizontal(enum combinationSetting setSearchOrDestroy, int horizontalLength);
    // Buscar en forma de L y T
    bool searchLT(enum combinationSetting setSearchOrDestroy);

    // Eliminar combinaciones
    // Eliminar verticales
    void eliminateVertical(int row, int col, int lengthToEliminate);
    // Eliminar horizontales 
    void eliminateHorizontal(int row, int col, int horizontalLength);
    // Eliminar elemento
    int eliminateElement(int row, int col);
    // Eliminar LT
    void eliminateLT(int shapeNumber, int row, int col);

    // Aumentar puntuación
    void pointsSystem(int combinationPoints);
    // Aplicar gravedad
    int applyGravity();
    // Revisar que hayan jugadas posibles
    
  public:
    // Constructor
    GameBoard(){}
    // Destructor
    ~GameBoard();
    // Para obtener una instancia de GameBoard
    static GameBoard& getInstance();
    // Función que maneja todas las funciones del GameBoard
    bool runGameBoard(int currentLevelNumber, sf::RenderWindow& window, int moves, int goalScore);

    int*& getMatriz(){
      return this->gameMatrix;
    };

    int getColumnas(){
      return this->colSize;
    };

    int getFilas(){
      return this->rowSize;
    };



  // Clase amiga
  friend class Level;
  friend class PlanetLevel;
  friend class SunLevel;
  friend class PlutoLevel;
};