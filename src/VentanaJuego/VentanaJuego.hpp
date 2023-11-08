#pragma once
#include <SFML/Graphics.hpp>
#include <map>


class VentanaJuego {
public:
    VentanaJuego(sf::RenderWindow window, int filas, int columnas, int*& matriz);

    void dibujarMatriz();

private:
    sf::RenderWindow &ventana;
    int*& matriz/*= nivel.getMatriz;*/;
    int filas/*= nivel.getFilas;*/;
    int columnas/*= nivel.getColumnas;*/;
    std::map<std::string, sf::Texture> texturasAliens;

    const int celdaAncho = 1280 / columnas;
    const int celdaAlto = 720 / filas;

    void cargarTexturas();
};


