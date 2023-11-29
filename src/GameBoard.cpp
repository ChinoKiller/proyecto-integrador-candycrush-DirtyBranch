#include "GameBoard.hpp"
#include <SFML/Graphics.hpp>

// Para obtener solo una instancia del ChessBoard.
GameBoard& GameBoard::getInstance() {
	static GameBoard GameBoard;
	return GameBoard;
}

// Llama las funciones del GameBoard en el orden necesario
bool GameBoard::runGameBoard(int currentLevelNumber, sf::RenderWindow& window, int moves, int goalScore) {
	// Generar una matriz de juego random
	generateRandomBoard();
	this->localMoves = moves;
	this->localGoalScore = goalScore; 
  // Muestra la ventana de juego
  cargarTexturas();
    cuadro.setOutlineColor(sf::Color::Black);
	showWindow(currentLevelNumber, window);
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }

      //cargarTexturas();

      // Mientras hayan movimientos, move >= 0 porque hay que eliminar la ultima jugada
    
      while((moves >= 0) && (this->currentScore < goalScore)) {
        cuadro.setOutlineColor(sf::Color::Black);
				//showWindow(window);
        // Eliminar todas las combinaciones hechas
        searchOrDestroy(DESTROY);
				printMatrix();
				std::cout << "⊹ ₊ Puntuación: " << this->currentScore << " ₊ ⊹" << std::endl << std::endl;
        // Si no estamos en la ultima ronda
        if ((moves > 0) && (this->currentScore < goalScore)) {
          // Revisar que hayan combinaciones posibles
          if (findPosibleCombinations()) {
            // Si hay combinaciones posibles y movimientos restantes
            // Pedirle al usuario que haga una jugada (restar movimientos)
			this->localMoves = moves;
			this->localGoalScore = goalScore; 
            showWindow(currentLevelNumber, window);
            play(currentLevelNumber, window);
			this->localMoves = moves;
			this->localGoalScore = goalScore; 
            showWindow(currentLevelNumber, window);
            moves = moves - 1;
          } else {
            // Si no hay combinaciones posibles y hay movimientos restantes
            // Generar nueva matriz de juego
            generateRandomBoard();
          }
        }
        // Restarle a movimientos para salir del while loop
        //moves = moves - 1;
      }
    
			// Puntos totales
			std::cout << "⊹ ₊ Puntuación total: " << this->currentScore << " ₊ ⊹" << std::endl;
			// Si NO se llega a la puntuación meta
			if (this->currentScore < goalScore) {
				return false;
			} 
			// Si llega a la puntuación meta, devolver verdadero
			return true;

    }
  }
	return false;
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
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      generateRandomNewNumber();
      continue;
    }
    // Buscar horizontales de 5 o mas de largo
    if (searchBigHorizontal(setSearchOrDestroy)) {
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      continue;
    }
    // Buscar elementos en forma de L y T
    if (searchLT(setSearchOrDestroy)) {
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      generateRandomNewNumber();
      continue;
    }
    // Buscar elementos verticales de 4
    if (searchVertical(setSearchOrDestroy, 4)) {
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      generateRandomNewNumber();
      continue;
    }
    // Buscar elementos horizontales de 4
    if (searchHorizontal(setSearchOrDestroy, 4)) {
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      generateRandomNewNumber();
      continue;
    }
    // Buscar elementos verticales de 3
    if (searchVertical(setSearchOrDestroy, 3)) {
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      generateRandomNewNumber();
      continue;
    }
    // Buscar elementos horizontales de 3
    if (searchHorizontal(setSearchOrDestroy, 3)) {
      // Si estoy en modo solo búsqueda retorna que se encontró combinación
      if (setSearchOrDestroy == SEARCH) {
        return true;
      }
      // Si llega aquí se encuentra en en modo eliminación 
      generateRandomNewNumber();
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
		if(_withinMatrix(rowIndex-1, colIndex, this->rowSize, this->colSize)) {
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
		if(_withinMatrix(rowIndex, colIndex-1, this->rowSize, this->colSize)) {
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
		if(_withinMatrix(rowIndex, colIndex+1, this->rowSize, this->colSize)) {
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
		if(_withinMatrix(rowIndex+1, colIndex, this->rowSize, this->colSize)) {
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


void GameBoard::play(int currentLevelNumber, sf::RenderWindow& window) {
  sf::Event event;
  bool keepReading = true;
  while(keepReading) {
    while (window.pollEvent(event) && keepReading) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {       
        if (event.key.code == sf::Keyboard::Right) {
          if(currentCol < colSize-1){
            currentCol++;
            showWindow(currentLevelNumber, window);
          }

        } else if (event.key.code == sf::Keyboard::Left) {
          if(currentCol > 0){
            currentCol--;
            showWindow(currentLevelNumber, window);
          }

        } else if (event.key.code == sf::Keyboard::Up) { 
          if(currentRow > 0){
            currentRow--;
            showWindow(currentLevelNumber, window);
          }

        } else if (event.key.code == sf::Keyboard::Down) { 
          if(currentRow < rowSize-1){
            currentRow++;
            showWindow(currentLevelNumber, window);
          }

        } else if (event.key.code == sf::Keyboard::X) {      
          switch (_withinMatrix(currentRow, currentCol, this->rowSize, this->colSize)) {
            case true:
                      // Si input es correcto, no seguir preguntando
                        // Configurar el color del borde (en este caso, negro)
              cuadro.setOutlineColor(sf::Color::Yellow);
              showWindow(currentLevelNumber, window);
              keepReading = false;
              break;
            case false:
                      // Si el input es incorrecto, imprimir mensaje y seguir preguntando
              std::cout << "Ingrese filas y columnas válidas (╥﹏╥)" << std::endl;
              break;
          }
        }
      }
    }
  }



  keepReading = true;
  int rowDestination, colDestination;

  while(keepReading) {
    while (window.pollEvent(event) && keepReading) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (event.type == sf::Event::KeyPressed) {   
        if (event.key.code == sf::Keyboard::Right) {
          if(currentCol < colSize-1){
            colDestination = currentCol+1;
            rowDestination = currentRow;
            keepReading = false;
          }
        } else if (event.key.code == sf::Keyboard::Left) {
          if(currentCol > 0){
            colDestination = currentCol-1;
            rowDestination = currentRow;
            keepReading = false;
          }
        } else if (event.key.code == sf::Keyboard::Up) { 
          if(currentRow > 0){
            rowDestination = currentRow-1;
            colDestination = currentCol;
            keepReading = false;
          }
        } else if (event.key.code == sf::Keyboard::Down) { 
          if(currentRow < rowSize-1){
            rowDestination = currentRow+1;
            colDestination = currentCol;
            keepReading = false;
          }
        } 
    
      }
    }         
  }
  // Intercambiar 
  swapElement(currentRow, currentCol, rowDestination, colDestination);
  std::cout << "After Swap" << std::endl;
  //printMatrix();
  if (!searchOrDestroy(SEARCH)) {
    std::cout << "No combinations, undo swap" << std::endl;
    swapElement(rowDestination, colDestination, currentRow, currentCol);
    //printMatrix();
  }
}


/*bool GameBoard::elementsAreAdjacent(int rowCurrent, int colCurrent, int rowDestination, int colDestination) {
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
}*/
/*
include en c++ de la funcion:
bool _elementsAreAdjacent(int rowCurrent, int colCurrent, int rowDestination, int colDestination);

Creo que esta funcion se puede poner totalmente a ensamblador
global _elementsAreAdjacent
; Funcion que revisa si los elementos son adyancentes
; Parametros
; rdi rowCurrent
; rsi colCurrent
; rdx rowDestination
; rcx colDestination

_elementsAreAdjacent:
	mov r8, rsi
	dec r8
	mov r9, rsi
	inc r9
	mov r10, rdi
	dec r10
	mov r11, rdi
	inc r11
; ya estan los valores correctos
	cmp rdi, rdx
	jne revisarColumnas

	; si son iguales 
	cmp r8, rcx
	je sonAdyacentes
	cmp r9, rcx
	je sonAdyacentes
	jmp noAdyacentes

revisarColumnas:
	cmp rsi, rcx
	jne noAdyacente

	; si son iguales
	cmp r10, rdx
	je sonAdyacentes
	cmp r11, rdx
	je sonAdyacentes
	jmp noAdyacentes

sonAdyacentes:
	mov rax, 1
	jmp exit

noAdyacentes:
	xor rax, rax

exit:
	ret
*/


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

/*void swapElement(this->gameMatrix,this->rowSize,this->colSize, int rowDestination, int colDestination, int rowCurrent, int colCurrent)

;funcion de ensambla para hacer el sawp entre dos elementos adyacentes
  ;	parametros
  ; rdi = this->gameMatrix
  ; rsi = this->rowSize
  ; rdx = this->colSize
  ; rcx = rowDestination
  ; r8 = colDestination
  ; r9 = rowCurrent
  ; r10 = colCurrent
_swapElement:
	;push rbp
	;mov rbp, rsp

    mov     rdi, qword [rbp]    ; this->gameMatrix (primer argumento)
    mov     rsi, qword [rbp + 8]   ; this->rowSize (segundo argumento)
    mov     rdx, qword [rbp + 16]   ; this->colSize (tercer argumento)
    mov     rcx, qword [rbp + 24]   ; rowDestination (cuarto argumento)
    mov     r8, qword [rbp + 32]    ; colDestination (quinto argumento)
    mov     r9, qword [rbp + 40]    ; rowCurrent (sexto argumento)
    mov     r10, qword [rbp + 48]   ; Acceso a colCurrent desde la pila

	;guardar parametros iniciales
    mov rax, rdi ; rdi = dirección de memoria de la matriz
    mov rbx, rsi ; rsi = tamaño filas
    mov r11, rdx ; rdx = tamaño columnas
    mov r12, rcx ; rcx = rowDestination
	mov r13, r8  ; r8 = colDestination
	mov r14, r9	 ; r9 = rowCurrent
	mov r15, r10 ; r10 = colCurrent	

	;push rbp
	;mov rax,

	;poner parametros para llamar funcion
	;int currentElement = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowCurrent,colCurrent);
	mov rdi, rax
	mov rsi, rbx
	mov rdx, r11
	mov rcx, r14
	mov r8, r15
	call _getCellValue


	
    
    ;cambiar parametros orden
    ;mov rdi, r14 ; rdi = this->gameMatrix
    ;mov rsi, r8 ; rsi = col
    ;mov rdx, r11 ; rdx = this->rowSize
    ;mov rcx, r12 ; rcx = this->colSize

	;int currentElement = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowCurrent,colCurrent);
    ;call _getCellValue
    ;cmp rax, 0
    ;je error

    ;cambiar parametros orden
    ;mov rdi, r10 ; rdi = row
    ;mov rsi, r11 ; rsi = col
    ;mov rdx, r12 ; rdx = this->rowSize
    ;mov rcx, r13 ; rcx = this->colSize
    ;mov r9, 0 ; r9 = newValue (0 en este caso)

    ;call _setValue
    ;mov rax, 1
    ;ret

;error:
  ;xor rax, rax
  ;ret

*/

/*
// Función para el sistema de puntos.

void GameBoard::pointsSystem(int combinationPoints) {
	// Se suma los puntos de la combinación a los puntos que ya se tienen
	this->currentScore = this->currentScore + combinationPoints;
}
*/

void GameBoard::pointsSystem(int combinationPoints) {
	// Se suma los puntos de la combinación a los puntos que ya se tienen
	this->currentScore = _pointsSystem(combinationPoints, this->currentScore);
}

/*
void GameBoard::pointsSystem(int combinationPoints) {
	// Se suma los puntos de la combinación a los puntos que ya se tienen
	this->currentScore = combinationPoints + this->currentScore;
  std::cout << "puntuacion en este momento: " << this->currentScore << std::endl;
}	
*/

/*
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
*/


bool GameBoard::readColRowSize(int rowColSize) {
	if (_readColRowSize) {
		GameBoard::rowSize = GameBoard::colSize = rowColSize;
		return true;
	}else {	
		std::cout << "Tamaño invalido" << std::endl;
		//return false;
	}
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
  std::cout<<std::endl;
  std::cout << "   ";
  for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
    std::cout << colIndex << " ";
  }
  std::cout << std::endl;
  for (int colIndex = 0; colIndex <= this->colSize; colIndex++) {
    std::cout << " ★";
  }
  std::cout << std::endl;
  for (int rowIndex = 0; rowIndex < this->rowSize; rowIndex++) {
    // Imprimir numero de rows, para localizar elementos con mas facilidad
    std::cout << rowIndex << "★ ";
    for (int colIndex = 0; colIndex < this->colSize; colIndex++) {
      //std::cout << this->gameMatrix[rowIndex][colIndex] << " ";
      std::cout<<_getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex) << " ";
    }
    std::cout<<std::endl;
  } 
  std::cout<<std::endl;
  return EXIT_SUCCESS;
}



// imprimir matriz de juego
void GameBoard::showWindow(int currentLevelNumber, sf::RenderWindow& window) {
    sf::RectangleShape board;
    sf::Sprite planet;
    sf::Texture texturePlanet;
    sf::Font font;

    sf::Text textPlanets;
    sf::Text textMovimientos;
    sf::Text textScore;
    sf::Text textNext;

	sf::Text textMovimientosNumber;
    sf::Text textScoreNumber;
    sf::Text textNextNumber;

    //hacerlo dinamico para el planeta actual
 
    font.loadFromFile("./assets/Fuentes/prstart.ttf");

	    switch (currentLevelNumber) {
        case 1:
            this->levelName = "Neptuno";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/NeptunoActivo.png");
						planet.setScale(0.28, 0.28);
            break;
        case 2:
            this->levelName = "Urano";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/UranoActivo.png");
						planet.setScale(0.28, 0.28);
            break;
        case 3:
            this->levelName = "Saturno";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/SaturnoActivo.png");
						planet.setScale(0.30, 0.30);
            break;
        case 4:
            this->levelName = "Jupiter";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/JupiterActivo.png");
						planet.setScale(0.25, 0.25);
            break;
        case 5:
            this->levelName = "Marte";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/MarteActivo.png");
						planet.setScale(0.30, 0.30);
            break;
        case 6:
            this->levelName = "Tierra";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/TierraActivo.png");
						planet.setScale(0.30, 0.30);
            break;
        case 7:
            this->levelName = "Venus";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/VenusActivo.png");
						planet.setScale(0.30, 0.30);
            break;
        case 8:
            this->levelName = "Mercurio";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/MercurioActivo.png");
						planet.setScale(0.30, 0.30);
            break;
        case 9:
            this->levelName = "Sol";
            texturePlanet.loadFromFile("./assets/niveles/Planetas/SolActivo.png");
						planet.setScale(0.20, 0.20);
            break;
        default:
            break;
    }

    textPlanets.setFont(font);
    textPlanets.setString(levelName);
    textPlanets.setCharacterSize(36);
    textPlanets.setFillColor(sf::Color::White);
    textPlanets.setPosition(50, 50);  // Coordenas X e Y

    planet.setTexture(texturePlanet);
    planet.setPosition(70, 103);

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
	
	std::stringstream lm;
	std::stringstream cs;
	std::stringstream gs;
	lm << localMoves;

	textMovimientosNumber.setFont(font);
    textMovimientosNumber.setString(lm.str());
    textMovimientosNumber.setCharacterSize(20);
    textMovimientosNumber.setFillColor(sf::Color::White);
    textMovimientosNumber.setPosition(50, 250+50);  // Coordenas X e Y

	cs << currentScore; 
    textScoreNumber.setFont(font);
    textScoreNumber.setString(cs.str());
    textScoreNumber.setCharacterSize(20);
    textScoreNumber.setFillColor(sf::Color::White);
    textScoreNumber.setPosition(50, 450-50+50);  // Coordenas X e Y

	gs << localGoalScore; 
    textNextNumber.setFont(font);
    textNextNumber.setString(gs.str());
    textNextNumber.setCharacterSize(20);
    textNextNumber.setFillColor(sf::Color::White);
    textNextNumber.setPosition(50, 650-100+50);  // Coordenas X e Y


    board.setSize(sf::Vector2f(540, 540));
    board.setFillColor(sf::Color(128, 128, 128));
    board.setPosition(390-25+300, 110-25);

	cuadro.setSize(sf::Vector2f(45, 45));
    cuadro.setOutlineThickness(2.f);
    cuadro.setPosition(currentCol * (500 / colSize) +690, currentRow * (500 / rowSize) +110);


    sf::Texture textureFondo;
    textureFondo.loadFromFile("./assets/menuPrincipal/menuFondo1.png");
    sf::Sprite fondo(textureFondo);
    cargarTexturas();

        window.clear();
        window.draw(fondo);
        window.draw(board);
		window.draw(cuadro);
        window.draw(textPlanets);
        window.draw(planet);
        window.draw(textMovimientos);
        window.draw(textScore);
        window.draw(textNext);
		window.draw(textMovimientosNumber);
        window.draw(textScoreNumber);
        window.draw(textNextNumber);
    dibujarMatriz(window);
    

}

void GameBoard::cargarTexturas(){
    // Carga las texturas de los planetas en texturasAliens
    texturasAliens["amarillo"] = sf::Texture();
    texturasAliens["azul"] = sf::Texture();
    texturasAliens["morado"] = sf::Texture();
    texturasAliens["naranja"] = sf::Texture();
    texturasAliens["rojo"] = sf::Texture();
    texturasAliens["verde"] = sf::Texture();

    texturasAliens["amarillo"].loadFromFile("./assets/aliens/amarillo.png");
    texturasAliens["azul"].loadFromFile("./assets/aliens/azul.png");
    texturasAliens["morado"].loadFromFile("./assets/aliens/morado.png");
    texturasAliens["naranja"].loadFromFile("./assets/aliens/naranja.png");
    texturasAliens["rojo"].loadFromFile("./assets/aliens/rojo.png");
    texturasAliens["verde"].loadFromFile("./assets/aliens/verde.png");

}

void GameBoard::dibujarMatriz(sf::RenderWindow& ventana){
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

            ventana.draw(alienSprite);
        }
    }

    ventana.display();
}


// destructor
GameBoard::~GameBoard() {
	//delete[] gameMatrix;
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
/*

*/

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
/*bool GameBoard::withinMatrix(int row, int col) {
	return (row >= 0 
	&& col >= 0
	&& row < rowSize
	&& col < colSize);
}*/


/* Corregir esta funcion en c++.
_withinMatrix(int row, int col, this->rowSize, this->colSize)
}*/

/*include en c++ de la funcion:
bool _withinMatrix(int row, int col, int rowSize, int colSize); 
 
Copiar esta parte a ensamblador

*/

// revisar si son del mismo color
bool GameBoard::isSameColor(int row, int col, int color) {
	// si se sale de la matriz o el color es 0 retornar falso
	if((_withinMatrix(row, col, this->rowSize, this->colSize) == false) || (color == 0)) {
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
// int GameBoard::eliminateElement(int row, int col) {
// 	// asegurarse que el elemento a eliminar exista
// 	if(!_eliminateElement(this->gameMatrix, this->rowSize, this->colSize, row,col)) {
//     std::cout << "Falló al eliminar elemento" << std::endl;
// 	  return EXIT_FAILURE;
	
// 	}
//   return EXIT_SUCCESS;

// }

int GameBoard::eliminateElement(int row, int col) {
	// asegurarse que el elemento a eliminar exista
	if(_withinMatrix(row,col, this->rowSize, this->colSize)) {
	_setValue(this->gameMatrix,this->rowSize,this->colSize,row,col,0);
	return EXIT_SUCCESS;
	}
	std::cout << "Falló al eliminar elemento" << std::endl;
	return EXIT_FAILURE;
}
/*
funcion en c++

// elimina un elemento, poniendo su valor en 0
int GameBoard::eliminateElement(int row, int col) {
	// asegurarse que el elemento a eliminar exista
	if(!_eliminateElement(this->matrix, this->rowSize, this->colSize, row,col)) {
    std::cout << "Falló al eliminar elemento" << std::endl;
	  return EXIT_FAILURE;
	
	}
  return EXIT_SUCCESS;

}
include de la funcion c++:
bool _eliminateElement(int* matriz, int rowSize, int colSize, int row, int col);

funcion de ensambla para eliminar un valor especifico, retorna un booleano de si se elimino bien
global _eliminateElement
  parametros eliminate
  ; rdi = dirección de memoria de la matriz
  ; rsi = tamaño filas (this-> rowSize)
  ; rdx = tamaño columnas (this-> colSize)
  ; rcx = row
  ; r8 = col
  _eliminateElement:	
    ;guardar parametros iniciales
    mov r10, rdi ; rdi = dirección de memoria de la matriz
    mov r11, rsi ; rsi = tamaño filas
    mov r12, rdx ; rdx = tamaño columnas
    mov r13, rcx ; rcx = row
    
    ;cambiar parametros orden
    mov rdi, r13 ; rdi = row
    mov rsi, r8 ; rsi = col
    mov rdx, r11 ; rdx = this->rowSize
    mov rcx, r12 ; rcx = this->colSize

    call _withinMatrix
    cmp rax, 0
    je error

    ;cambiar parametros orden
    mov rdi, r10 ; rdi = row
    mov rsi, r11 ; rsi = col
    mov rdx, r12 ; rdx = this->rowSize
    mov rcx, r13 ; rcx = this->colSize
    mov r9, 0 ; r9 = newValue (0 en este caso)

    call _setValue
    mov rax, 1
    ret

error:
  xor rax, rax
  ret
*/



// Gravedad
//int GameBoard::applyGravity(int* gameMatrix) { prueba para pasar la funcion a ensambla
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

/*
poner en gameboard
int _applyGravity(int* matriz, int rowSize, int colSize);


funcion de ensambla para hacer la gravedad
global _applyGravity
  parametros eliminate
  ; rdi = dirección de memoria de la matriz
  ; rsi = tamaño filas (this-> rowSize)
  ; rdx = tamaño columnas (this-> colSize)
;_applyGravity:
	;guardar parametros iniciales
    ;mov r10, rdi ; rdi = dirección de memoria de la matriz
    ;mov r11, rsi ; rsi = tamaño filas
    ;mov r12, rdx ; rdx = tamaño columnas
	
	; primer for
	;for (int colIndex = 0; colIndex < this->colSize; colIndex++)
	;mov r15, 0		;colIndex	
;for1:
	;;mov r15, 0		;colIndex
	;cmp r15, r12	;colIndex < this->colSize
	;jge salirFor1
	; si r15 es menor que this->colSize
	;mov r8, r11 
	;dec r8			;	int destinationRow = this->rowSize - 1

	;segundo for
	;for (int rowIndex = this->rowSize - 1; rowIndex >= 0; rowIndex--) 
	;mov rbx, r11 	
	;dec rbx			; int rowIndex = this->rowSize - 1
;for2:
	;;mov rbx, r11 	
	;;dec rbx			; int rowIndex = this->rowSize - 1
	;cmp rbx, 0
	;jl salirFor2

	;;int cellValue = _getCellValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex);

	;mov rdi, r10	;this->gameMatrix
	;mov rsi, r11	;this->rowSize
	;mov rdx, r12	;this->colSize
	;mov rcx, rbx	;rowIndex
	;mov r8, r15		;colIndex
	;call _getCellValue

	;mov r14, rax	;int cellValue
	;cmp r14, 0		if (cellValue!= 0)
	;je aumentarFor2
	;_setValue(this->gameMatrix,this->rowSize,this->colSize,destinationRow,colIndex,cellValue);
	;mov rdi, r10	;this->gameMatrix
	;mov rsi, r11	;this->rowSize
	;mov rdx, r12	;this->colSize
	;mov rcx, rbx	;rowIndex
	;mov r8, r15		;colIndex
	;mov r9, r14 	;cellValue
	;call setValue

	;cmp r8, rbx 	;if (destinationRow != rowIndex)
	;je seguir
	;_setValue(this->gameMatrix,this->rowSize,this->colSize,rowIndex,colIndex,0);
	;mov rdi, r10	;this->gameMatrix
	;mov rsi, r11	;this->rowSize
	;mov rdx, r12	;this->colSize
	;mov rcx, rbx	;rowIndex
	;mov r8, r15		;colIndex
	;mov r9, 0 	;0
	;call setValue

;seguir:
	;dec r8			;destinationRow--

;aumentarFor2:
	;dec rbx 	; rowIndex--
	;jmp for2

;salirFor2:
	;inc r15		; colIndex++
	;jmp for1
	
;salirFor1
	;ret
*/