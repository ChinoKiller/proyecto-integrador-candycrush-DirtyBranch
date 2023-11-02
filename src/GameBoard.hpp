#include <iostream>
#include "common.hpp"
#include <random>

// clase GameBoard
class GameBoard {
  private:
    // tamaño de las filas de la matriz
    int rowSize;
    // tamaño de las columnas de la matriz
    int colSize;
    // matriz dinámica, para que se pueda ajustar según el tamaño del tablero deseado
    int** gameMatrix;
    // se encontró una combinación
    bool combinationFound = true;
    // inicializar sistema de puntuacion.
    int punctuation;
    // matriz con las formas L y T, incluyendo todas sus rotaciones
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

  // funciones privadas
  private:
    // Deshabilitar la copia de objetos GameBoard
    DISABLE_COPY(GameBoard); 
    // leer tamaño de la matriz, retorna bool que indica si lo leyó correctamente
    bool readColRowSize(int rowColSize);
    // crear matriz dinámica, retorna int que indica si lo inicializó correctamente
    int initMatrix(int rowColSize);
    // imprimir la matriz de juego
    int printMatrix();
    // generar tablero aleatoriamente
    int generateRandomBoard();
    // generar números aleatorios en espacios en blanco
    int generateRandomNewNumber();
    // revisar que no nos salgamos de la matriz
    bool withinMatrix(int row, int col);
    // son del mismo color
    bool isSameColor(int row, int col, int color);

    // revisar que hayan combinaciones, revisar según prioridad
    // buscar verticales de 5 o mas
    bool searchBigVertical();
    // buscar vertical de 4 o 3, según parámetro
    bool searchVertical(int verticalLength);
    // buscar horizontales de 5 o mas
    bool searchBigHorizontal();
    // buscar horizontales de 4 o 3, según el parámetro
    bool searchHorizontal(int horizontalLength);
    // buscar en forma de L y T
    bool searchLT();
    

    // eliminar combinaciones
    // eliminar verticales
    void eliminateVertical(int row, int col, int lengthToEliminate);
    // eliminar horizontales 
    void eliminateHorizontal(int row, int col, int horizontalLength);
    // eliminar elemento
    int eliminateElement(int row, int col);
    // eliminar LT
    void eliminateLT(int shapeNumber, int row, int col);

    // aumentar puntuación
    void pointsSystem(int combinationPoints);
    // aplicar gravedad
    int applyGravity();
    // revisar que hayan jugadas posibles
    
  public:
    // constructor
    GameBoard(){}
    // destructor
    ~GameBoard();
    // para obtener una instancia de GameBoard
    static GameBoard& getInstance();
    // función que maneja todas las funciones del GameBoard
    int runGameBoard();

};