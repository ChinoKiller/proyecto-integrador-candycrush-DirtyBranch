#include <iostream>
#include <random>

// clase GameBoard
class GameBoard {
  private:
    // Tamaño de las filas de la matriz
    int rowSize;
    // Tamaño de las columnas de la matriz
    int colSize;
    // Matriz dinámica, para que se pueda ajustar según el tamaño del tablero deseado
    int** gameMatrix;
    // Se encontró una combinación
    bool combinationFound = true;
    // Inicializar sistema de puntuación
    int punctuation;
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

  // Funciones privadas
  private:
    // Leer tamaño de la matriz, retorna bool que indica si lo leyó correctamente
    bool readColRowSize(int rowColSize);
    // Crear matriz dinámica, retorna int que indica si lo inicializó correctamente
    int initMatrix(int rowColSize);
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

    // Revisar que hayan combinaciones, revisar según prioridad
    // Buscar verticales de 5 o mas
    bool searchBigVertical();
    // Buscar vertical de 4 o 3, según parámetro
    bool searchVertical(int verticalLength);
    // Buscar horizontales de 5 o mas
    bool searchBigHorizontal();
    // Buscar horizontales de 4 o 3, según el parámetro
    bool searchHorizontal(int horizontalLength);
    // Buscar en forma de L y T
    bool searchLT();

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
    int runGameBoard();

};