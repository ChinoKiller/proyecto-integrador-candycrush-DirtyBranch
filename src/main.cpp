#include "Controlador.hpp"

int main() {
	// Crear instancia del controlador
	Controlador gameController = Controlador();
	// Controlador crea Nivel y empieza a jugar
	gameController.runGame();
	return EXIT_SUCCESS;
}