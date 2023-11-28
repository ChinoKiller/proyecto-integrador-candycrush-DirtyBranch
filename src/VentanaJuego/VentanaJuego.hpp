#pragma once
#include <SFML/Graphics.hpp>
#include <map>


class VentanaJuego {
public:
    VentanaJuego(sf::RenderWindow &window, int filas, int columnas, int*& matriz, int levelNumber);

    void dibujarPantalla();
    void actualizarPantalla();


private:
    sf::RenderWindow &ventana;
    int*& matriz;
    int filas;
    int columnas;
    std::map<std::string, sf::Texture> texturasAliens;
    sf::Texture texturaFondo;
    sf::Font font;
    sf::Sprite planet;
    sf::Texture texturePlanet;
    sf::RectangleShape board;
    int levelNumber;
    std::string levelName;
    sf::Text textPlanets;
    sf::Text textMovimientos;
    sf::Text textScore;
    sf::Text textNext;
    sf::Sprite fondo;

    const int celdaAncho = 1280 / columnas;
    const int celdaAlto = 720 / filas;

    void ajustarNivel();
    void cargarTexturas();
    void dibujarMatriz();
};


