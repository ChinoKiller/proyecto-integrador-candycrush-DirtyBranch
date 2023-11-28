#include "VentanaJuego.hpp"

VentanaJuego::VentanaJuego(sf::RenderWindow &ventana, int filas, int columnas, int*& matriz, int levelNumber)
    : ventana(ventana), matriz(matriz), filas(filas), columnas(columnas), levelNumber(levelNumber){
    cargarTexturas();
    ajustarNivel();

}

void VentanaJuego::ajustarNivel() {
    switch (levelNumber) {
        case 1:
            this->levelName = "Neptuno";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/NeptunoActivo.png");
            break;
        case 2:
            this->levelName = "Urano";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/UranoActivo.png");
            break;
        case 3:
            this->levelName = "Saturno";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/SaturnoActivo.png");
            break;
        case 4:
            this->levelName = "Jupiter";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/JupiterActivo.png");
            break;
        case 5:
            this->levelName = "Marte";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/MarteActivo.png");
            break;
        case 6:
            this->levelName = "Tierra";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/TierraActivo.png");
            break;
        case 7:
            this->levelName = "Venus";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/VenusActivo.png");
            break;
        case 8:
            this->levelName = "Mercurio";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/MercurioActivo.png");
            break;
        case 9:
            this->levelName = "Sol";
            this->texturePlanet.loadFromFile("./MenusSfml/niveles/Planetas/SolActivo.png");
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

    this->fondo.setTexture(texturaFondo);
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
    texturaFondo.loadFromFile("./MenusSfml/menuPrincipal/menuFondo1.png");
    font.loadFromFile("./MenusSfml/Fuentes/prstart.ttf");
    
}

void VentanaJuego::dibujarMatriz() {


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


void VentanaJuego::dibujarPantalla() {    
    ventana.clear();
    ventana.draw(fondo);
    ventana.draw(board);
    ventana.draw(textPlanets);
    ventana.draw(textMovimientos);
    ventana.draw(textScore);
    ventana.draw(textNext);
    ventana.draw(planet);
    dibujarMatriz();
}


void VentanaJuego::actualizarPantalla() {

}