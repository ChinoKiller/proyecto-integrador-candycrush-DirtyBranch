#include "GameBoard.hpp"

// Para obtener solo una instancia del ChessBoard.
GameBoard& GameBoard::getInstance() {
  static GameBoard GameBoard;
  return GameBoard;
}

// llama las funciones del GameBoard en el orden necesario
int GameBoard::runGameBoard() {
  std::cout<<"Running GameBoard" << std::endl;
  // test para un nivel de 8x8
  initMatrix(8);
  generateRandomBoard();
  printMatrix();
  // test para un nivel de 9x9
  initMatrix(9);
  generateRandomBoard();
  printMatrix();
  // test para un nivel de 10x10
  initMatrix(10);
  generateRandomBoard();
  printMatrix();
  return EXIT_SUCCESS;
}

// leer y verificar tamaño de la matriz 
bool GameBoard::readColRowSize(int rowColSize) {
  // solo entra si el tamaño es 8,9 o 10
  if ((rowColSize >= 8) && (rowColSize <= 10)) {
    // asignar rowSize y colSize en instancia de GameBoard
    GameBoard::rowSize = GameBoard::colSize = rowColSize;
    std::cout << "Tamaño valido :D" << std::endl;
    return true;
  }
  std::cout << "Tamaño invalido" << std::endl;
  return false;
}

// crear una matriz según el tamaño del nivel (8x8, 9x9, 10x10)
int GameBoard::initMatrix(int rowColSize) {
  // revisar tamaño de la matriz y verificar que sea valida
  // si el tamaño es valido, inicializar una matriz de ese tamaño
  if (readColRowSize(rowColSize)) {
    // inicializar filas
    this->gameMatrix = new int*[rowSize];
    // inicializar columnas
    for (int index = 0; index < this->rowSize; ++index) {
      this->gameMatrix[index] = new int [colSize];
    }
    // poner todos los valores en 0
    for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
      for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
        this->gameMatrix[rowIndex][colIndex] = 0;
      }
    }
    std::cout << "Se inicializo matriz!" << std::endl;
    return EXIT_SUCCESS;
  }
  std::cout << "No se inicializo :(" << std::endl;
  return EXIT_SUCCESS;
}

// imprimir matriz de juego
int GameBoard::printMatrix() {
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      std::cout << this->gameMatrix[rowIndex][colIndex] << " ";
    }
    std::cout<<std::endl;
  }
  return EXIT_SUCCESS;
}

// destructor
GameBoard::~GameBoard() {
  for (int index = 0; index < this->rowSize; index++) {
    delete[] gameMatrix[index];
  }
  delete[] gameMatrix;
  gameMatrix = nullptr;
}

// generar elementos de la matriz de forma aleatoria
int GameBoard::generateRandomBoard() {
  std::random_device randomGenerator;
  std::mt19937 gen(randomGenerator());
  std::uniform_int_distribution<int> intDistribution(1,6);

  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      int pseudoRandomNum = intDistribution(gen);
      this->gameMatrix[rowIndex][colIndex] = pseudoRandomNum;
    }
  }
  return EXIT_SUCCESS;
}

// revisar que hayan jugadas posibles
// revisar que hayan combinaciones
// revisar según prioridad
// eliminar combinaciones 
// aplicar gravedad
// generar nuevos elementos que caigan 

   