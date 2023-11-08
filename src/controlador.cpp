#include "./GameBoard.hpp"
#include "./Levels/Level.hpp"
#include "./VentanaJuego/VentanaJuego.hpp"


class Controlador {
public:
    Controlador(sf::RenderWindow& ventana);

    void dibujarMatriz();

private:
    sf::RenderWindow& ventana;
    Level& nivel;
    int*& matriz/*= nivel.getMatriz;*/;
    int filas/*= nivel.getFilas;*/;
    int columnas/*= nivel.getColumnas;*/;
    std::map<std::string, sf::Texture> texturasAliens;

    const int celdaAncho = 1280 / columnas;
    const int celdaAlto = 720 / filas;

    void cargarTexturas();
};