#include "GameBoard.hpp"
#include <SFML/Graphics.hpp>

// Para obtener solo una instancia del ChessBoard.
GameBoard& GameBoard::getInstance() {
  static GameBoard GameBoard;
  return GameBoard;
}

// Llama las funciones del GameBoard en el orden necesario
int GameBoard::runGameBoard() {
  // Generar una matriz de juego random
  generateRandomBoard();
  
  // Muestra la ventana de juego
  //showWindow();

  sf::RenderWindow window(sf::VideoMode(1280, 720), "Alienigenas Alineados");
    sf::RectangleShape board;
    sf::Sprite planet;
    sf::Texture texturePlanet;
    sf::Font font;
    
    sf::Text textPlanets;
    sf::Text textMovimientos;
    sf::Text textScore;
    sf::Text textNext;

    //hacerlo dinamico para el planeta actual
    texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/VenusActivo.png");
    font.loadFromFile("./MenusSfml/Fuentes/prstart.ttf");

    textPlanets.setFont(font);
    textPlanets.setString("Venus");
    textPlanets.setCharacterSize(36);
    textPlanets.setFillColor(sf::Color::White);
    textPlanets.setPosition(50, 50);  // Coordenas X e Y

    planet.setTexture(texturePlanet);
    planet.setScale(0.35, 0.35);
    planet.setPosition(70, 105);

    textMovimientos.setFont(font);
    textMovimientos.setString("Movimientos Restantes =");
    textMovimientos.setCharacterSize(20);
    textMovimientos.setFillColor(sf::Color::White);
    textMovimientos.setPosition(50, 250);  // Coordenas X e Y

    textScore.setFont(font);
    textScore.setString("Puntaje =");
    textScore.setCharacterSize(20);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(50, 450-50);  // Coordenas X e Y

    textNext.setFont(font);
    textNext.setString("Siguiente Nivel =");
    textNext.setCharacterSize(20);
    textNext.setFillColor(sf::Color::White);
    textNext.setPosition(50, 650-100);  // Coordenas X e Y


    board.setSize(sf::Vector2f(540, 540));
    board.setFillColor(sf::Color(128, 128, 128));
    board.setPosition(390-25+300, 110-25);

    sf::Texture textureFondo;
    textureFondo.loadFromFile("./MenusSfml/menuPrincipal/menuFondo1.png");
    sf::Sprite fondo(textureFondo);
    cargarTexturas();
  // Imprimir la matriz inicial
  printMatrix();
  // Mientras hayan movimientos, move >= 0 porque hay que eliminar la ultima jugada
  while(this->moves >= 0) {

        window.clear();
        window.draw(fondo);
        window.draw(board);
        window.draw(textPlanets);
        window.draw(textMovimientos);
        window.draw(textScore);
        window.draw(textNext);
        window.draw(planet);
 

        for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            int alien = gameMatrix[i * rowSize + j];

            std::string clave;

            switch (alien) {
                case 1:
                    clave = "amarillo";
                    break;
                case 2:
                    clave = "azul";
                    break;
                case 3:
                    clave = "morado";
                    break;
                case 4:
                    clave = "naranja";
                    break;
                case 5:
                    clave = "rojo";
                    break;
                case 6:
                    clave = "verde";
                    break;
                default:
                    break;
            
            }

            sf::Sprite alienSprite(texturasAliens[clave]);
            alienSprite.setScale(0.5, 0.5);
            alienSprite.setPosition(j * (500 / colSize) +690, i * (500 / rowSize) +110);

            window.draw(alienSprite);
        }
    }
           window.display();
    // Eliminar todas las combinaciones hechas
    searchOrDestroy(DESTROY);
    // Si no estamos en la ultima ronda
    if (this->moves > 0) {
      // Revisar que hayan combinaciones posibles
      if (findPosibleCombinations()) {
        // Si hay combinaciones posibles y movimientos restantes
        // Pedirle al usuario que haga una jugada (restar movimientos)
         window.clear();
        window.draw(fondo);
        window.draw(board);
        window.draw(textPlanets);
        window.draw(textMovimientos);
        window.draw(textScore);
        window.draw(textNext);
        window.draw(planet);
        for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            int alien = gameMatrix[i * rowSize + j];

            std::string clave;

            switch (alien) {
                case 1:
                    clave = "amarillo";
                    break;
                case 2:
                    clave = "azul";
                    break;
                case 3:
                    clave = "morado";
                    break;
                case 4:
                    clave = "naranja";
                    break;
                case 5:
                    clave = "rojo";
                    break;
                case 6:
                    clave = "verde";
                    break;
                default:
                    break;
            
            }

            sf::Sprite alienSprite(texturasAliens[clave]);
            alienSprite.setScale(0.5, 0.5);
            alienSprite.setPosition(j * (500 / colSize) +690, i * (500 / rowSize) +110);

            window.draw(alienSprite);
        }
    }
                   window.display();
                   
        play();
           window.clear();
        window.draw(fondo);
        window.draw(board);
        window.draw(textPlanets);
        window.draw(textMovimientos);
        window.draw(textScore);
        window.draw(textNext);
        window.draw(planet);
          for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            int alien = gameMatrix[i * rowSize + j];

            std::string clave;

            switch (alien) {
                case 1:
                    clave = "amarillo";
                    break;
                case 2:
                    clave = "azul";
                    break;
                case 3:
                    clave = "morado";
                    break;
                case 4:
                    clave = "naranja";
                    break;
                case 5:
                    clave = "rojo";
                    break;
                case 6:
                    clave = "verde";
                    break;
                default:
                    break;
            
            }

            sf::Sprite alienSprite(texturasAliens[clave]);
            alienSprite.setScale(0.5, 0.5);
            alienSprite.setPosition(j * (500 / colSize) +690, i * (500 / rowSize) +110);

            window.draw(alienSprite);
        }
    }
                   window.display();
        this->moves = this->moves - 1;
      } else {
        // Si no hay combinaciones posibles y hay movimientos restantes
        // Generar nueva matriz de juego
        generateRandomBoard();
      }
    }
    // Restarle a movimientos para salir del while loop
    this->moves = this->moves - 1;
  }

  // Puntos totales
  std::cout << "Puntos totales: " << punctuation << std::endl;
  return EXIT_SUCCESS;
}



// Busca combinaciones posibles, las destruye si la configuración indica DESTROY.
bool GameBoard::searchOrDestroy(enum combinationSetting setSearchOrDestroy) {
  // DESTROY == 1 o SEARCH == 0
  bool combinationFound = setSearchOrDestroy;
  // DESTROY, mientras hayan combinaciones que destruir seguir eliminando las combinaciones.
  // SEARCH, entra al mientras solo una vez. Dentro de la función retorna true si encontró alguna combinación.
  // o se sale del while y retorna false si no se encontró ninguna combinación.
  while(combinationFound == setSearchOrDestroy) {
    // Buscar elementos verticales de 5 o mas de largo
    if (searchBigVertical(setSearchOrDestroy)) {
      std::cout << "Encontró: vertical de 5 o mas" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // Buscar horizontales de 5 o mas de largo
    if (searchBigHorizontal(setSearchOrDestroy)) {
      std::cout << "Encontró: horizontal de 5 o mas" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // Buscar elementos en forma de L y T
    if (searchLT(setSearchOrDestroy)) {
      std::cout << "Encontró: LT" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // Buscar elementos verticales de 4
    if (searchVertical(setSearchOrDestroy, 4)) {
      std::cout << "Encontró: vertical de 4" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // Buscar elementos horizontales de 4
    if (searchHorizontal(setSearchOrDestroy, 4)) {
      std::cout << "Encontró: horizontal de 4" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // Buscar elementos verticales de 3
    if (searchVertical(setSearchOrDestroy, 3)) {
      std::cout << "Encontró: vertical de 3" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // Buscar elementos horizontales de 3
    if (searchHorizontal(setSearchOrDestroy, 3)) {
      std::cout << "Encontró: horizontal de 3" << std::endl;
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      std::cout << "Matriz después de gravedad." << std::endl;
      printMatrix();
      std::cout << "Matriz después de nuevos elementos." << std::endl;
      generateRandomNewNumber();
      printMatrix();
      std::cout << "Puntuación : " << punctuation << std::endl;
      std::cout << "" << std::endl;
      continue;
    }
    // No se encontró combinaciones
    // Si el programa logra llegar hasta aquí es que no encontró combinaciones
    // Salirse del while
    combinationFound = !setSearchOrDestroy;
  }
  return false;
}

// Buscar que hayan posibles combinaciones
bool GameBoard::findPosibleCombinations(){
  // Atravesar la matriz tomando un elemento a la vez, 
  // ese elemento ir cambiándolo de posición con sus adyacentes y buscar si forma combinaciones.
  for(int rowIndex = 0; rowIndex < rowSize; rowIndex++) {
    for(int colIndex = 0; colIndex < colSize; colIndex++) {
      // Revisar si elemento se puede mover arriba
      if(withinMatrix(rowIndex-1, colIndex)) {
        // Mover elemento para arriba
        swapElement(rowIndex-1, colIndex, rowIndex, colIndex);
        // Revisar si hay combinaciones 
        if (searchOrDestroy(SEARCH)) {
          // Devolver elemento a su lugar
          swapElement(rowIndex-1, colIndex, rowIndex, colIndex);
          return true;
        }
        // Devolver elemento a su lugar
        swapElement(rowIndex-1, colIndex, rowIndex, colIndex);
      }
      // Revisar si elemento se puede mover izquierda
      if(withinMatrix(rowIndex, colIndex-1)) {
        // Mover elemento para izquierda
        swapElement(rowIndex, colIndex-1, rowIndex, colIndex);
        // Revisar si hay combinaciones 
        if (searchOrDestroy(SEARCH)) {
          // Devolver elemento a su lugar
          swapElement(rowIndex, colIndex-1, rowIndex, colIndex);
          return true;
        }
        // Devolver elemento a su lugar
        swapElement(rowIndex, colIndex-1, rowIndex, colIndex);
      }
      // Revisar si elemento se puede mover derecha
      if(withinMatrix(rowIndex, colIndex+1)) {
        // Mover elemento para derecha
        swapElement(rowIndex, colIndex+1, rowIndex, colIndex);
        // Revisar si hay combinaciones 
        if (searchOrDestroy(SEARCH)) {
          // Devolver elemento a su lugar
          swapElement(rowIndex, colIndex+1, rowIndex, colIndex);
          return true;
        }
        // Devolver elemento a su lugar
        swapElement(rowIndex, colIndex+1, rowIndex, colIndex);
      }
      // Revisar si elemento se puede mover abajo
      if(withinMatrix(rowIndex+1, colIndex)) {
        // Mover elemento para abajo
        swapElement(rowIndex+1, colIndex, rowIndex, colIndex);
        // Revisar si hay combinaciones 
        if (searchOrDestroy(SEARCH)) {
          // Devolver elemento a su lugar
          swapElement(rowIndex+1, colIndex, rowIndex, colIndex);
          return true;
        }
        // Devolver elemento a su lugar
        swapElement(rowIndex+1,colIndex, rowIndex, colIndex);
      }
    }
  } 
  return false;
}

void GameBoard::play() {
  int rowCurrent, colCurrent;
  bool keepReading = true;
  // Mientras el input sea incorrecto, seguir preguntando
  std::cout << "₊˚⊹ ⋆ Ingrese fila y columnas separados de espacios ₊˚⊹ ⋆" << std::endl;
  while(keepReading) {
    std::cout << "★ Posición del elemento que quiere cambiar: " << std::endl;
    // Si logra leer bien dos valores enteros
    if(std::cin >> rowCurrent >> colCurrent) {
      // Verificar que input este correcto
      switch (withinMatrix(rowCurrent, colCurrent)) {
        case true:
          // Si input es correcto, no seguir preguntando
          
          keepReading = false;
          break;
        case false:
          // Si el input es incorrecto, imprimir mensaje y seguir preguntando
          std::cout << "Ingrese filas y columnas válidas (╥﹏╥)" << std::endl;
          break;
      }
    } else {
      std::cin.clear();    // Limpiar el estado de error
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
      std::cout << "Ingrese números válidos pls (╥﹏╥)" << std::endl;
    }
  }
  
  keepReading = true;
  int rowDestination, colDestination;
  while(keepReading) {
    std::cout << "★ Posición posición destino: " << std::endl;
    // Si logra leer bien dos valores enteros
    if(std::cin >> rowDestination >> colDestination) {
      // Verificar que input este dentro del rango de la matriz
      switch (withinMatrix(rowDestination, rowDestination)) {
        case true:
          // Revisar si son adyacentes
          if (elementsAreAdjacent(rowCurrent, colCurrent, rowDestination, colDestination)) {
            // Si input es correcto, no seguir preguntando
            keepReading = false;
            break;
          } else {
            std::cout << "Elementos no son adyacentes! (╥﹏╥)" << std::endl;
          }
          break;
        case false:
          // Si el input es incorrecto, imprimir mensaje y seguir preguntando
          std::cout << "Ingrese filas y columnas válidas (╥﹏╥)" << std::endl;
          break;
      }
    } else {
      std::cin.clear();    // Limpiar el estado de error
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar entrada inválida
      std::cout << "Ingrese números válidos pls (╥﹏╥)" << std::endl;
    }
  }
  // Intercambiar 
  swapElement(rowCurrent, colCurrent, rowDestination, colDestination);
  std::cout << "After Swap" << std::endl;
  printMatrix();
  if (!searchOrDestroy(SEARCH)) {
    std::cout << "No combinations, undo swap" << std::endl;
    swapElement(rowDestination, colDestination, rowCurrent, colCurrent);
    printMatrix();
  }
}

bool GameBoard::elementsAreAdjacent(int rowCurrent, int colCurrent, int rowDestination, int colDestination) {
  if(rowCurrent == rowDestination) {
    // Izquierda o derecha
    if((colCurrent-1 == colDestination) || (colCurrent+1 == colDestination)){
      return true;
    }
  } else if (colCurrent == colDestination) {
    // Arriba o abajo
    if((rowCurrent-1 == rowDestination) || (rowCurrent+1 == rowDestination)) {
      return true;
    }
  }
  return false;
}


void GameBoard::swapElement(int rowDestination, int colDestination, int rowCurrent, int colCurrent) {
  // Agarra el elemento actual a ser cambiado
  int currentElement = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowCurrent,colCurrent);
  int auxElement;
  // Poner elemento en posición destino en un auxiliar, para no perderlo
  auxElement = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowDestination,colDestination);
  // Cambiar elemento actual a posición destino (moverlo arriba)
  _setValue(this->gameMatrix, this->rowSize, this->colSize, rowDestination, colDestination, currentElement);
  // Elemento que estaba arriba moverlo abajo
  _setValue(this->gameMatrix, this->rowSize, this->colSize, rowCurrent, colCurrent, auxElement);
  // Listo, los elementos ya se intercambiaron de lugar 
}

// Función para el sistema de puntos.
void GameBoard::pointsSystem(int combinationPoints) {
  // Se suma los puntos de la combinación a los puntos que ya se tienen
  punctuation = punctuation + combinationPoints;
}

// leer y verificar tamaño de la matriz 
bool GameBoard::readColRowSize(int rowColSize) {
  // solo entra si el tamaño es 8,9 o 10
  if ((rowColSize >= 8) && (rowColSize <= 10)) {
    // asignar rowSize y colSize en instancia de GameBoard
    GameBoard::rowSize = GameBoard::colSize = rowColSize;
    return true;
  }
  std::cout << "Tamaño invalido" << std::endl;
  return false;
}


// crear una matriz según el tamaño del nivel (8x8, 9x9, 10x10)
bool GameBoard::initMatrix(int rowColSize) {
  // revisar tamaño de la matriz y verificar que sea valida
  // si el tamaño es valido, inicializar una matriz de ese tamaño
  if (readColRowSize(rowColSize)) {
    // guardar memoria matriz (matriz cuadrada)
    this->gameMatrix = new int[rowColSize * rowColSize]; 
    // llamar a la funcion que inicializa la matriz en 0
    _initMatrix(this->gameMatrix, rowColSize);
    std::cout << "Se inicializo matriz!" << std::endl;
    return true;
  }
  std::cout << "No se inicializo :(" << std::endl;
  return false;
}

// imprimir matriz de juego
int GameBoard::printMatrix() {
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      //std::cout << this->gameMatrix[rowIndex][colIndex] << " ";
      std::cout<<_getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex) << " ";
    }
    std::cout<<std::endl;
  } 
  return EXIT_SUCCESS;
}

// imprimir matriz de juego
void GameBoard::showWindow() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Alienigenas Alineados");
    sf::RectangleShape board;
    sf::Sprite planet;
    sf::Texture texturePlanet;
    sf::Font font;
    
    sf::Text textPlanets;
    sf::Text textMovimientos;
    sf::Text textScore;
    sf::Text textNext;

    //hacerlo dinamico para el planeta actual
    texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/VenusActivo.png");
    font.loadFromFile("./MenusSfml/Fuentes/prstart.ttf");

    textPlanets.setFont(font);
    textPlanets.setString("Venus");
    textPlanets.setCharacterSize(36);
    textPlanets.setFillColor(sf::Color::White);
    textPlanets.setPosition(50, 50);  // Coordenas X e Y

    planet.setTexture(texturePlanet);
    planet.setScale(0.35, 0.35);
    planet.setPosition(70, 105);

    textMovimientos.setFont(font);
    textMovimientos.setString("Movimientos Restantes =");
    textMovimientos.setCharacterSize(20);
    textMovimientos.setFillColor(sf::Color::White);
    textMovimientos.setPosition(50, 250);  // Coordenas X e Y

    textScore.setFont(font);
    textScore.setString("Puntaje =");
    textScore.setCharacterSize(20);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(50, 450-50);  // Coordenas X e Y

    textNext.setFont(font);
    textNext.setString("Siguiente Nivel =");
    textNext.setCharacterSize(20);
    textNext.setFillColor(sf::Color::White);
    textNext.setPosition(50, 650-100);  // Coordenas X e Y


    board.setSize(sf::Vector2f(540, 540));
    board.setFillColor(sf::Color(128, 128, 128));
    board.setPosition(390-25+300, 110-25);

    sf::Texture textureFondo;
    textureFondo.loadFromFile("./MenusSfml/menuPrincipal/menuFondo1.png");
    sf::Sprite fondo(textureFondo);
    cargarTexturas();

        window.clear();
        window.draw(fondo);
        window.draw(board);
        window.draw(textPlanets);
        window.draw(textMovimientos);
        window.draw(textScore);
        window.draw(textNext);
        window.draw(planet);
    

}

void GameBoard::cargarTexturas(){
    // Carga las texturas de los planetas en texturasAliens
    texturasAliens["amarillo"] = sf::Texture();
    texturasAliens["azul"] = sf::Texture();
    texturasAliens["morado"] = sf::Texture();
    texturasAliens["naranja"] = sf::Texture();
    texturasAliens["rojo"] = sf::Texture();
    texturasAliens["verde"] = sf::Texture();

    texturasAliens["amarillo"].loadFromFile("./src/VentanaJuego/aliens/amarillo.png");
    texturasAliens["azul"].loadFromFile("./src/VentanaJuego/aliens/azul.png");
    texturasAliens["morado"].loadFromFile("./src/VentanaJuego/aliens/morado.png");
    texturasAliens["naranja"].loadFromFile("./src/VentanaJuego/aliens/naranja.png");
    texturasAliens["rojo"].loadFromFile("./src/VentanaJuego/aliens/rojo.png");
    texturasAliens["verde"].loadFromFile("./src/VentanaJuego/aliens/verde.png");

}

// destructor
GameBoard::~GameBoard() {
  delete[] gameMatrix;
  gameMatrix = nullptr;
}

// generar elementos de la matriz de forma aleatoria
int GameBoard::generateRandomBoard() {

  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      int pseudoRandomNum = generateNumberAtRandom();
      _setValue(this->gameMatrix, this->rowSize, this->colSize, rowIndex, colIndex, pseudoRandomNum);
    }
  }
  return EXIT_SUCCESS;
}

// Generar números aleatorios (Para después de la gravedad).
int GameBoard::generateRandomNewNumber() {

  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // si la celda esta vacía, generar un elemento random
      if (_getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex) == 0) {
        int pseudoRandomNum = generateNumberAtRandom();
        _setValue(this->gameMatrix, this->rowSize, this->colSize, rowIndex, colIndex, pseudoRandomNum);
      }
    }
  }
  return EXIT_SUCCESS;
}


//genera un numero aleatorio
int GameBoard::generateNumberAtRandom(){
  std::random_device randomGenerator;
  std::mt19937 gen(randomGenerator());
  std::uniform_int_distribution<int> intDistribution(1,6);
  return intDistribution(gen);
}


// buscar verticales de 5 o mas
bool GameBoard::searchBigVertical(enum combinationSetting setSearchOrDestroy){
  // recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // tomar un elemento
      int elementColor = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);
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
        if (setSearchOrDestroy == SEARCH) {
          return true;
        } else {
          // eliminar vertical de 5 o mas
          eliminateVertical(rowIndex, colIndex, verticalLength);
          // aumentar puntuación
          pointsSystem(10); // combinaciones verticales de 5 o mas elementos son de 10 puntos.
          return true;
        }
      }
    }
  }
  return false;
}

// buscar verticales de verticalLength
bool GameBoard::searchVertical(enum combinationSetting setSearchOrDestroy, int verticalLength) {
  // recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // tomar un elemento
      int elementColor = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);
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
        if (setSearchOrDestroy == SEARCH) {
          return true;
        } else {
          // eliminar combinación
          eliminateVertical(rowIndex, colIndex, verticalLength);
          // aumentar puntuación
          pointsSystem(verticalLength * 2); // combinaciones verticales de 3 o 4 elementos son de 6 o 8, respectivamente.
          return true;
        }
      }
    }
  }
  return false;
}

bool GameBoard::searchBigHorizontal(enum combinationSetting setSearchOrDestroy) {
  // recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // tomar un elemento
      int elementColor = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);
      int colPosition = colIndex;
      bool sameColor = true;
      int horizontalLength = 0;
      // verificar si ese elemento tiene combinación horizontal
      // mientras tenga el mismo color y no se salga de las columnas
      while(sameColor && colPosition < colSize) {
        // revisar que elemento sea del mismo color al original
        sameColor = isSameColor(rowIndex, colPosition, elementColor);
        // si son del mismo color
        if (sameColor){
          // aumentar tamaño
          horizontalLength++;
          // seguir buscando
          colPosition++;
        } else {
          break;
        }
      }
      if (horizontalLength >= 5) {
        if (setSearchOrDestroy == SEARCH) {
          return true;
        } else {
          // eliminar horizontal de 5 o mas
          eliminateHorizontal(rowIndex, colIndex, horizontalLength);
          // aumentar puntuación
          pointsSystem(10); // combinaciones horizontales de 5 o mas elementos son de 10 puntos.
          return true;
        }
      }
    }
  }
  return false;
}

// buscar horizontales de 4 o 3, según el parámetro
bool GameBoard::searchHorizontal(enum combinationSetting setSearchOrDestroy, int horizontalLength) {
  // recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // tomar un elemento
      int elementColor = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);
      int colPosition = colIndex;
      bool sameColor = true;
      // verificar si ese elemento tiene combinación horizontal de horizontalLength
      for(int index = 0; index < horizontalLength; index++) {
        sameColor = isSameColor(rowIndex, colPosition + index, elementColor);
        if (sameColor == false) {
          break;
        }
      }
      // si el bool sameColor sigue como verdadero, ya encontré una combinación de horizontalLength
      if (sameColor) {
        if (setSearchOrDestroy == SEARCH) {
          return true;
        } else {
          // eliminar combinación
          eliminateHorizontal(rowIndex, colIndex, horizontalLength);
          // aumentar puntuación
          pointsSystem(horizontalLength * 2);  // combinaciones horizontales de 3 o 4 elementos son de 6 o 8, respectivamente.
          return true;
        }
      }
    }
  }
  return false;
}

// eliminar combinación horizontal
void GameBoard::eliminateHorizontal(int row, int col, int horizontalLength) {
  for(int index = 0; index < horizontalLength; index++) {
    eliminateElement(row, col+index);
  }
  applyGravity();
}

// Buscar combinaciones de la forma L y T y todas sus rotaciones
bool GameBoard::searchLT(enum combinationSetting setSearchOrDestroy) {
  // Recorrer la matriz
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      // Tomar elemento 
      int elementColor = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);
      // Si el elemento no es 0, existe elemento en esa celda
      if (elementColor != 0) {
        bool sameColor = true;
        int arrayCounter = 0;
        int rowPosition = rowIndex;
        int colPosition = colIndex;
        // Mientras no haya encontrado forma LT y hay mas que buscar
        while(arrayCounter < 8) {
          for(int rowLTmatrix = 0; rowLTmatrix < 5; rowLTmatrix++) {
            int rowOffset = this->LTshapes[arrayCounter][rowLTmatrix][0];
            int colOffset = this->LTshapes[arrayCounter][rowLTmatrix][1];
            sameColor = isSameColor((rowPosition+rowOffset),(colPosition+colOffset), elementColor);
            if(sameColor==false){
              break;  // Salir del for loop
            }
          }
          if(sameColor == true) {
            if (setSearchOrDestroy == SEARCH) {
            return true;
          } else {
              // eliminar forma LT
              eliminateLT(arrayCounter, rowIndex, colIndex);
              // aumentar puntuación
              if (arrayCounter < 4) {   // las primeras 4 son combinaciones de las L
                pointsSystem(15); // las combinaciones L son de 15 puntos
              } else {    // si no son las 4 combinaciones de las L, son las combinaciones de las T
                pointsSystem(17);  // las combinaciones T son de 17 puntos.
              }
              return true;
          }
          } else {
            arrayCounter++;
          }
        }

      }
    }
  }
  return false;
}



// eliminar forma LT
void GameBoard::eliminateLT(int shapeNumber, int row, int col) {
  for (int rowLTmatrix = 0; rowLTmatrix < 5; rowLTmatrix++) {
    int rowOffset = this->LTshapes[shapeNumber][rowLTmatrix][0];
    int colOffset = this->LTshapes[shapeNumber][rowLTmatrix][1];
    eliminateElement((row + rowOffset), (col + colOffset));
  }
  applyGravity();
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
    return _isSameColor(this->gameMatrix,row,col,color,this->rowSize);
  }
}

// elimina la combinación vertical según el largo pasado
void GameBoard::eliminateVertical(int row, int col, int lengthToEliminate){
  for(int index = 0; index < lengthToEliminate; index++) {
    eliminateElement(row + index, col);
  }
  applyGravity();
}

// elimina un elemento, poniendo su valor en 0
int GameBoard::eliminateElement(int row, int col) {
  // asegurarse que el elemento a eliminar exista
  if(withinMatrix(row,col)) {
    _setValue(this->gameMatrix,this->rowSize,this->colSize,row,col,0);
    return EXIT_SUCCESS;
  }
  std::cout << "Falló al eliminar elemento" << std::endl;
  return EXIT_FAILURE;
}

// Gravedad
int GameBoard::applyGravity() {
  for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
    // Mover los elementos hacia abajo en una columna
    int destinationRow = this->rowSize - 1; // Empezar desde la fila más baja
    for (int rowIndex = this->rowSize - 1; rowIndex >= 0; rowIndex--) {
      int cellValue = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);
      if (cellValue!= 0) {
        // Si el elemento no es cero, se mueve a la fila de destino
        _setValue(this->gameMatrix,this->rowSize,this->colSize,destinationRow,colIndex, cellValue);
        //this->gameMatrix[destinationRow * this->rowSize + colIndex] = this->gameMatrix[rowIndex * this->rowSize + colIndex];
        // Si la fila de destino es diferente de la fila de origen, se pone el elemento original en cero
        if (destinationRow != rowIndex) {
          //this->gameMatrix[rowIndex * this->rowSize + colIndex] = 0;
          _setValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex,0);
        }
        destinationRow--; // Mueve la fila de destino hacia arriba
      }
    }
  }
  return EXIT_SUCCESS;
}
