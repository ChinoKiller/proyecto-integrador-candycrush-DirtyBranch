//#include "./VentanaJuego/VentanaJuego.hpp"
#include <ctime>
#include <map>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class VentanaDeJuego{
public:
    //VentanaJuego(sf::RenderWindow &ventana, int filas, int columnas, int*& matriz, int levelNumber);
    //VentanaJuego(int filas, int columnas, int*& matriz, int levelNumber);

    VentanaDeJuego(int filas, int columnas, int* matriz, int levelNumber)
    : matriz(matriz), filas(filas), columnas(columnas), levelNumber(levelNumber){
    cargarTexturas();
    ajustarNivel();
    }
    

    
    void dibujarPantalla(sf::RenderWindow &ventana){   
    ventana.clear();
    ventana.draw(fondo);
    ventana.draw(board);
    ventana.draw(textPlanets);
    ventana.draw(textMovimientos);
    ventana.draw(textScore);
    ventana.draw(textNext);
    ventana.draw(planet);
    dibujarMatriz(ventana);
    }
    
    void actualizarPantalla();


protected:
    //sf::RenderWindow ventana;
    int* matriz;
    int filas;
    int columnas;
    std::map<std::string, sf::Texture> texturasAliens;
    sf::Texture texturaFondo;
    sf::Font font;
    sf::Sprite planet;
    sf::Texture texturePlanet;
    sf::RectangleShape board;
    int levelNumber = 1;
    std::string levelName;
    sf::Text textPlanets;
    sf::Text textMovimientos;
    sf::Text textScore;
    sf::Text textNext;
    sf::Sprite fondo;

    const int celdaAncho = 500 / columnas;
    const int celdaAlto = 500 / filas;

    void ajustarNivel(){
        switch (levelNumber) {
            case 1:
                this->levelName = "Neptuno";
                this->texturePlanet.loadFromFile("./niveles/Planetas/NeptunoActivo.png");
                break;
            case 2:
                this->levelName = "Urano";
                this->texturePlanet.loadFromFile("./niveles/Planetas/UranoActivo.png");
                break;
            case 3:
                this->levelName = "Saturno";
                this->texturePlanet.loadFromFile("./niveles/Planetas/SaturnoActivo.png");
                break;
            case 4:
                this->levelName = "Jupiter";
                this->texturePlanet.loadFromFile("./niveles/Planetas/JupiterActivo.png");
                break;
            case 5:
                this->levelName = "Marte";
                this->texturePlanet.loadFromFile("./niveles/Planetas/MarteActivo.png");
                break;
            case 6:
                this->levelName = "Tierra";
                this->texturePlanet.loadFromFile("./niveles/Planetas/TierraActivo.png");
                break;
            case 7:
                this->levelName = "Venus";
                this->texturePlanet.loadFromFile("./niveles/Planetas/VenusActivo.png");
                break;
            case 8:
                this->levelName = "Mercurio";
                this->texturePlanet.loadFromFile("./niveles/Planetas/MercurioActivo.png");
                break;
            case 9:
                this->levelName = "Sol";
                this->texturePlanet.loadFromFile("./niveles/Planetas/SolActivo.png");
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


    void cargarTexturas(){
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
        texturaFondo.loadFromFile("./menuPrincipal/menuFondo1.png");
        font.loadFromFile("./Fuentes/prstart.ttf");
    }
    
    void dibujarMatriz(sf::RenderWindow &ventana){
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
                alienSprite.setScale(0.5, 0.5);
                alienSprite.setPosition((j * celdaAncho) +690, (i * celdaAlto) +110);

                ventana.draw(alienSprite);
            }
        }

        ventana.display();
    }
};



struct VentanaJuegos {
    int filas = 9;
    int columnas = 9;

    const int celdaAncho = 500 / columnas;
    const int celdaAlto = 500 / filas;
};
 
static int matriz [81]; 

void llenarMatriz(){

    // Semilla para la generación de números aleatorios
    std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));

    // Distribución para números enteros entre 1 y 6
    std::uniform_int_distribution<int> distribution(1, 6);

    // Llenar el arreglo con números aleatorios
    for (int i = 0; i < 81; i++) {
        matriz[i] = distribution(rng);
    }
};


int main() {
    VentanaJuegos datos;
    static sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Alienigenas Alineados");
    llenarMatriz();
    sf::Event event;
    VentanaDeJuego VDJ(datos.filas, datos.columnas, matriz, 1);

    while (ventana.isOpen()) {
        ventana.display();
        while (ventana.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                ventana.close();
            }
            VDJ.dibujarPantalla(ventana);
        }
    }



    //VentanaJuegos datosVentana;
    //VentanaDeJuego *VDJ = new VentanaDeJuego(datosVentana.filas, datos.columnas, matriz, 1);




    //ventanaPRUEBA VentanaDeJuego(9, 9, matriz, 1);

    //VentanaDeJuego ventanaTEST(9, 9, matriz, 1);
    
    
    //VentanaJuego ventanaTablero(window, 9, 9, matriz);

    return 0;
}