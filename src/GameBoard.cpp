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
  // inicializar matriz
  initMatrix(8);
  // generar una matriz de juego random
  generateRandomBoard();
  // imprimir la matriz
  printMatrix();
  // mientras se hayan encontrado combinaciones
  while(this->combinationFound) {
    // buscar elementos verticales de 5 o mas de largo
    if (searchBigVertical()) {
      std::cout << "Encontró: vertical de 5 o mas" << std::endl;
      printMatrix();
      continue;
    }
    if (searchVertical(4)) {
      std::cout << "Encontró: vertical de 4" << std::endl;
      printMatrix();
      continue;
    }
    if (searchVertical(3)) {
      std::cout << "Encontró: vertical de 3" << std::endl;
      printMatrix();
      continue;
    }
    // horizontales de 5 o mas de largo
    // buscar buscar elementos en forma de L y T
    // buscar elementos verticales y horizontales de 4 o 3 de largo
    // si el programa logra llegar hasta aquí es que no encontró combinaciones
    this->combinationFound = false;
  }
  // no se encontró combinaciones
  std::cout << "No se encontró mas combinaciones realizadas" << std::endl;
  // verificar que hayan combinaciones POSIBLES

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

// Generar números aleatorios (Para después de la gravedad).
int GameBoard::generateRandomNewNumber() {
  std::random_device randomGenerator;
  std::mt19937 gen(randomGenerator());
  std::uniform_int_distribution<int> intDistribution(1,6);

  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // si la celda esta vacía, generar un elemento random
      if (this->gameMatrix[rowIndex][colIndex] == 0) {
        int pseudoRandomNum = intDistribution(gen);
        this->gameMatrix[rowIndex][colIndex] = pseudoRandomNum;
      }
    }
  }
  return EXIT_SUCCESS;
}

// buscar verticales de 5 o mas
bool GameBoard::searchBigVertical(){
  std::cout << "Buscando Verticales de 5 o mas" << std::endl;
  // recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // tomar un elemento
      int elementColor = gameMatrix[rowIndex][colIndex];
      int rowPosition = rowIndex;
      //int colPosition = colIndex;
      bool sameColor = true;
      int verticalLength = 0;
      // verificar si ese elemento tiene combinación vertical
      // mientras tenga el mismo color y no se salga de las filas
      while(sameColor && rowPosition < rowSize) {
        // revisar que elemento sea del mismo color al original
        sameColor = isSameColor(rowPosition, colIndex, elementColor);
        // si son del mismo color
        if (sameColor){
          // aumentar tamaño
          verticalLength++;
          // seguir buscando
          rowPosition++;
        } else {
          break;
        }
      }
      if (verticalLength >= 5) {
        // eliminar vertical de 5 o mas
        eliminateVertical(rowIndex, colIndex, verticalLength);
        // aumentar puntuación
        return true;
      }
    }
  }
  return false;
}

// buscar verticales de verticalLength
bool GameBoard::searchVertical(int verticalLength) {
  std::cout << "Buscando Verticales " << verticalLength << std::endl;
  // recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // tomar un elemento
      int elementColor = gameMatrix[rowIndex][colIndex];
      int rowPosition = rowIndex;
      bool sameColor = true;
      // verificar si ese elemento tiene combinación vertical de verticalLength
      for(int index = 0; index < verticalLength; index++) {
        sameColor = isSameColor(rowPosition + index, colIndex, elementColor);
        if (sameColor == false) {
          break;
        }
      }
      // si el bool sameColor sigue como verdadero, ya encontré una combinación de verticalLength
      if (sameColor) {
        // eliminar combinación
        eliminateVertical(rowIndex, colIndex, verticalLength);
        // aumentar puntuación
        return true;
      }
    }
  }
  return false;
}

bool GameBoard::searchBigHorizontal(){
  return EXIT_SUCCESS;
}


// revisar que no se sale de la matriz
bool GameBoard::withinMatrix(int row, int col) {
  return (row >= 0 
    && col >= 0
    && row < rowSize
    && col < colSize);
}

// revisar si son del mismo color
bool GameBoard::isSameColor(int row, int col, int color) {
  // si se sale de la matriz o el color es 0 retornar falso
  if((withinMatrix(row, col) == false) || (color == 0)) {
    return false;
  } else {
    return(gameMatrix[row][col] == color);
  }
}

void GameBoard::eliminateVertical(int row, int col, int lengthToEliminate){
  for(int index = 0; index < lengthToEliminate; index++) {
    eliminateElement(row + index, col);
  }
}

int GameBoard::eliminateElement(int row, int col) {
  // asegurarse que el elemento a eliminar exista
  if(withinMatrix(row,col)) {
    gameMatrix[row][col] = 0;
    return EXIT_SUCCESS;
  }
  std::cout << "Falló al eliminar elemento" << std::endl;
  return EXIT_FAILURE;
}