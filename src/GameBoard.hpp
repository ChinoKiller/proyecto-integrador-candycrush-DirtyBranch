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
    
    // eliminar elemento
    int eliminateElement(int row, int col);
    // eliminar combinaciones
    // eliminar verticales
    void eliminateVertical(int row, int col, int lengthToEliminate);
    // aumentar puntuación

    // aplicar gravedad
    // generar nuevos elementos que caigan 
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