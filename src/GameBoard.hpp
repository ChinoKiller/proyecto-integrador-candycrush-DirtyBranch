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
  
  // funciones privadas
  private:
    // Deshabilitar la copia de objetos gameBoard.
    DISABLE_COPY(GameBoard); 
    // leer tamaño de la matriz, retorna bool que indica si lo leyó correctamente
    bool readColRowSize(int rowColSize);
    // crear matriz dinámica, retorna int que indica si lo inicializó correctamente
    int initMatrix(int rowColSize);
    // imprimir la matriz de juego
    int printMatrix();
    // generar tablero aleatoriamente
    int generateRandomBoard();
  
  public:
    // constructor
    GameBoard(){}
    // destructor
    ~GameBoard();
    // Para obtener una instancia de GameBoard.
    static GameBoard& getInstance();
    // función que maneja todas las funciones del GameBoard
    int runGameBoard();

};