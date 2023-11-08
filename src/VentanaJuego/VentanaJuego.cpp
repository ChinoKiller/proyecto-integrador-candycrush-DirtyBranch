#include "VentanaJuego.hpp"

VentanaJuego::VentanaJuego(sf::RenderWindow ventana, int filas, int columnas, int*& matriz)
    : ventana(ventana), matriz(matriz), filas(filas), columnas(columnas){
    cargarTexturas();

}

void VentanaJuego::cargarTexturas() {
    // Carga las texturas de los planetas en texturasAliens
    texturasAliens["amarillo"] = sf::Texture();
    texturasAliens["azul"] = sf::Texture();
    texturasAliens["morado"] = sf::Texture();
    texturasAliens["naranja"] = sf::Texture();
    texturasAliens["rojo"] = sf::Texture();
    texturasAliens["verde"] = sf::Texture();

    texturasAliens["amarillo"].loadFromFile("./aliens/amarillo.png");
    texturasAliens["azul"].loadFromFile("./aliens/azul.png");
    texturasAliens["morado"].loadFromFile("./aliens/morado.png");
    texturasAliens["naranja"].loadFromFile("./aliens/naranja.png");
    texturasAliens["rojo"].loadFromFile("./aliens/rojo.png");
    texturasAliens["verde"].loadFromFile("./aliens/verde.png");
    
}

void VentanaJuego::dibujarMatriz() {
    ventana.clear();

     for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int alien = matriz[i * filas + j];

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
            alienSprite.setPosition(j * celdaAncho, i * celdaAlto);

            ventana.draw(alienSprite);
        }
    }

    ventana.display();
}