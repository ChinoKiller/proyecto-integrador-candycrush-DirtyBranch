#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "../src/VentanaJuego/VentanaJuego.hpp"
#include <random>
#include <ctime>


enum Menu { MAIN_MENU, LEVEL_MENU, INSTRUCTIONS_MENU, SETTINGS_MENU, EXIT, TABLERO};
int crrntTxreMsc = 0;   //esto debe estar ligado al booleano de la musica
int crrntTxreSfx = 0;   // este al booleando de los efectos de sonido
int currentLevel = 1;


struct VentanaJuegos {
    int filas = 9;
    int columnas = 9;

    const int celdaAncho = 500 / columnas;
    const int celdaAlto = 500 / filas;
};

int matriz [81]; 
std::map<std::string, sf::Texture> texturasAliens;

void cargarTexturas() {
    // Carga las texturas de los planetas en texturasAliens
    texturasAliens["amarillo"] = sf::Texture();
    texturasAliens["azul"] = sf::Texture();
    texturasAliens["morado"] = sf::Texture();
    texturasAliens["naranja"] = sf::Texture();
    texturasAliens["rojo"] = sf::Texture();
    texturasAliens["verde"] = sf::Texture();

    texturasAliens["amarillo"].loadFromFile("../src/VentanaJuego/aliens/amarillo.png");
    texturasAliens["azul"].loadFromFile("../src/VentanaJuego/aliens/azul.png");
    texturasAliens["morado"].loadFromFile("../src/VentanaJuego/aliens/morado.png");
    texturasAliens["naranja"].loadFromFile("../src/VentanaJuego/aliens/naranja.png");
    texturasAliens["rojo"].loadFromFile("../src/VentanaJuego/aliens/rojo.png");
    texturasAliens["verde"].loadFromFile("../src/VentanaJuego/aliens/verde.png");
    
}

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


void dibujarMatriz(sf::RenderWindow &window, int filas, int columnas, int celdaAncho, int celdaAlto) {
    //window.clear();

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
            alienSprite.setPosition(j * celdaAncho +690, i * celdaAlto +110);

            window.draw(alienSprite);
        }
    }

    window.display();
}


Menu menuP(sf::RenderWindow &window, Menu &currentMenu){
    int NUM_FRAMES = 7;
    // Cargar una serie de imágenes en un vector
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= NUM_FRAMES; i++) {
        sf::Texture texture;
        if (texture.loadFromFile("./menuPrincipal/MENU_RESIZED" + std::to_string(i) + ".png")) {
            frames.push_back(texture);
        }
    }
    // Variables para controlar la animación menu principal
    int currentFrame = 0;
        float frameTime = 0.1f;
    
    while (window.isOpen()&& currentMenu==MAIN_MENU) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == MAIN_MENU) {
                    if (event.key.code == 72) {
                        currentMenu = SETTINGS_MENU;

                    } else if (event.key.code == 71) {
                        currentMenu = INSTRUCTIONS_MENU;

                    } else if (event.key.code == sf::Keyboard::X) { 
                        currentMenu = LEVEL_MENU;
                    } else if (event.key.code == sf::Keyboard::T) { 
                        currentMenu = TABLERO;
                    }
                }
            }
        }
        // Mostrar el cuadro actual
        window.clear();
        sf::Sprite sprite(frames[currentFrame]);
        window.draw(sprite);
        window.display();

        // Avanzar al siguiente cuadro
        sf::sleep(sf::seconds(frameTime));
        currentFrame = (currentFrame + 1) % frames.size();

       
    }
    return currentMenu;
}



Menu menuC(sf::RenderWindow &window, Menu &currentMenu){
    sf::Texture textureFondo;
    sf::Texture textureconfigBoard;
    sf::Texture textureMusica;
    sf::Texture textureSfx;
    std::vector<sf::Texture> texturasMusica;
    std::vector<sf::Texture> texturasSfx;
    //sf::Sprite sprite(frames[currentFrame]);
    textureFondo.loadFromFile("./menuPrincipal/menuFondo1.png");
    textureconfigBoard.loadFromFile("./menuConfiguracion/configBoard.png");
    textureMusica.loadFromFile("./menuConfiguracion/musicaActivada.png");
    texturasMusica.push_back(textureMusica);
    textureMusica.loadFromFile("./menuConfiguracion/musicaDesactivada.png");
    texturasMusica.push_back(textureMusica);
    textureSfx.loadFromFile("./menuConfiguracion/sfxActivados.png");
    texturasSfx.push_back(textureSfx);
    textureSfx.loadFromFile("./menuConfiguracion/sfxDesactivados.png");
    texturasSfx.push_back(textureSfx);


    while (window.isOpen()&& currentMenu==SETTINGS_MENU) {
        sf::Event event;
        window.clear();
        sf::Sprite spriteFondo(textureFondo);
        sf::Sprite spriteBoard(textureconfigBoard);
        sf::Sprite musica(texturasMusica[crrntTxreMsc]);
        sf::Sprite sfx(texturasSfx[crrntTxreSfx]);
        musica.setPosition(790, 245);
        sfx.setPosition(790, 360);
        musica.setScale(0.3f, 0.3f);
        sfx.setScale(0.3f, 0.3f);
        spriteBoard.scale(0.375, 0.375);
        spriteBoard.setPosition(280, 1);
        window.draw(spriteFondo);
        window.draw(spriteBoard);
        window.draw(musica);
        window.draw(sfx);
        window.display();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == SETTINGS_MENU) {
                    if (event.key.code == 72) {
                        currentMenu = SETTINGS_MENU;   
                    } else if (event.key.code == 71) {
                        currentMenu = MAIN_MENU;
                    } 
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    if(crrntTxreMsc == 0){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreMsc = 1;
                    } else if(crrntTxreMsc == 1){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreMsc = 0;
                    }
                } else if (event.key.code == sf::Keyboard::S) {
                    if(crrntTxreSfx == 0){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreSfx = 1;
                    } else if(crrntTxreSfx == 1){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreSfx = 0;
                    }
                }
            }
        }
    }
    return currentMenu;
}



Menu menuI(sf::RenderWindow &window, Menu &currentMenu){
    std::vector<sf::Texture> frames;
    sf::Texture texture;
    texture.loadFromFile("./menuInstrucciones/instrucciones.png");
    while (window.isOpen()&& currentMenu==INSTRUCTIONS_MENU) {
        sf::Event event;
        window.clear();
        sf::Sprite sprite(texture);
        window.draw(sprite);
        window.display();
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == INSTRUCTIONS_MENU) {
                    if (event.key.code == 72) {
                        currentMenu = MAIN_MENU;
                    } else if (event.key.code == 71) {
                        currentMenu = INSTRUCTIONS_MENU;   
                    } else if (event.key.code == sf::Keyboard::P) {
                        texture.loadFromFile("./menuInstrucciones/puntos.png");   
                    } else if (event.key.code == sf::Keyboard::C) {
                        texture.loadFromFile("./menuInstrucciones/combinaciones.png");  
                    } 
                }
            }
        }
    }
    return currentMenu;
}

Menu menuN(sf::RenderWindow &window, Menu &currentMenu){
    sf::Texture texture;
    sf::RectangleShape background;
    std::map<std::string, sf::Texture> texturasPlanetasActivos;  // Mapa de planetas encendidos
    std::map<std::string, sf::Texture> texturasPlanetasInactivos;  // Mapa de planetas apagados


    // Crea las texturas y le asigna un nombre dentro de cada mapa (pasar a subfuncion para mas limpieza)
    //encendidos
    texturasPlanetasActivos["sol"] = sf::Texture();
    texturasPlanetasActivos["mercurio"] = sf::Texture();
    texturasPlanetasActivos["venus"] = sf::Texture();
    texturasPlanetasActivos["tierra"] = sf::Texture();
    texturasPlanetasActivos["marte"] = sf::Texture();
    texturasPlanetasActivos["jupiter"] = sf::Texture();
    texturasPlanetasActivos["saturno"] = sf::Texture();
    texturasPlanetasActivos["urano"] = sf::Texture();
    texturasPlanetasActivos["neptuno"] = sf::Texture();
    //apagados
    texturasPlanetasInactivos["sol"] = sf::Texture();
    texturasPlanetasInactivos["mercurio"] = sf::Texture();
    texturasPlanetasInactivos["venus"] = sf::Texture();
    texturasPlanetasInactivos["tierra"] = sf::Texture();
    texturasPlanetasInactivos["marte"] = sf::Texture();
    texturasPlanetasInactivos["jupiter"] = sf::Texture();
    texturasPlanetasInactivos["saturno"] = sf::Texture();
    texturasPlanetasInactivos["urano"] = sf::Texture();
  
    //carga de texturas
    texture.loadFromFile("./niveles/fondoNiveles.jpg");
    //encendidos
    texturasPlanetasActivos["sol"].loadFromFile("./niveles/Planetas/SolActivo.png");
    texturasPlanetasActivos["mercurio"].loadFromFile("./niveles/Planetas/MercurioActivo.png");
    texturasPlanetasActivos["venus"].loadFromFile("./niveles/Planetas/VenusActivo.png");
    texturasPlanetasActivos["tierra"].loadFromFile("./niveles/Planetas/TierraActivo.png");
    texturasPlanetasActivos["marte"].loadFromFile("./niveles/Planetas/MarteActivo.png");
    texturasPlanetasActivos["jupiter"].loadFromFile("./niveles/Planetas/JupiterActivo.png");
    texturasPlanetasActivos["saturno"].loadFromFile("./niveles/Planetas/SaturnoActivo.png");
    texturasPlanetasActivos["urano"].loadFromFile("./niveles/Planetas/UranoActivo.png");
    texturasPlanetasActivos["neptuno"].loadFromFile("./niveles/Planetas/NeptunoActivo.png");
    //apagados
    texturasPlanetasInactivos["sol"].loadFromFile("./niveles/Planetas/SolInactivo.png");
    texturasPlanetasInactivos["mercurio"].loadFromFile("./niveles/Planetas/MercurioInactivo.png");
    texturasPlanetasInactivos["venus"].loadFromFile("./niveles/Planetas/VenusInactivo.png");
    texturasPlanetasInactivos["tierra"].loadFromFile("./niveles/Planetas/TierraInactivo.png");
    texturasPlanetasInactivos["marte"].loadFromFile("./niveles/Planetas/MarteInactivo.png");
    texturasPlanetasInactivos["jupiter"].loadFromFile("./niveles/Planetas/JupiterInactivo.png");
    texturasPlanetasInactivos["saturno"].loadFromFile("./niveles/Planetas/SaturnoInactivo.png");
    texturasPlanetasInactivos["urano"].loadFromFile("./niveles/Planetas/UranoInactivo.png");
    
    
    //creacion de sprites
    sf::Sprite sol(texturasPlanetasInactivos["sol"]);
    sf::Sprite mercurio(texturasPlanetasInactivos["mercurio"]);
    sf::Sprite venus(texturasPlanetasInactivos["venus"]);
    sf::Sprite tierra(texturasPlanetasInactivos["tierra"]);
    sf::Sprite marte(texturasPlanetasInactivos["marte"]);
    sf::Sprite jupiter(texturasPlanetasInactivos["jupiter"]);
    sf::Sprite saturno(texturasPlanetasInactivos["saturno"]);
    sf::Sprite urano(texturasPlanetasInactivos["urano"]);
    sf::Sprite neptuno(texturasPlanetasActivos["neptuno"]);


    //ajuste de tamanio
    background.setSize(sf::Vector2f(1280, 720));
    sol.setScale(0.194, 0.194);
    mercurio.setScale(0.09, 0.09);
    venus.setScale(0.11, 0.11);
    tierra.setScale(0.13, 0.13);
    marte.setScale(0.12, 0.12);
    jupiter.setScale(0.21, 0.21);
    saturno.setScale(0.21, 0.21);
    urano.setScale(0.14, 0.14);
    neptuno.setScale(0.13, 0.13);


    //posicion
    sol.setPosition(0, 194);
    mercurio.setPosition(100+85, 260);
    venus.setPosition(150+85, 250);
    tierra.setPosition(225+57, 250);
    marte.setPosition(300+65, 250);
    jupiter.setPosition(400+35, 235);
    saturno.setPosition(525+65, 250);
    urano.setPosition(775, 250);
    neptuno.setPosition(900, 250);
    

    //textura fondo
    background.setSize(sf::Vector2f(1280, 720));
    background.setTexture(&texture);


    while (window.isOpen()&& currentMenu==LEVEL_MENU) {
            
            switch (currentLevel) {
                case 1:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasInactivos["venus"]);
                    tierra.setTexture(texturasPlanetasInactivos["tierra"]);
                    marte.setTexture(texturasPlanetasInactivos["marte"]);
                    jupiter.setTexture(texturasPlanetasInactivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasInactivos["saturno"]);
                    urano.setTexture(texturasPlanetasInactivos["urano"]);
                    break;
                case 2:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasInactivos["venus"]);
                    tierra.setTexture(texturasPlanetasInactivos["tierra"]);
                    marte.setTexture(texturasPlanetasInactivos["marte"]);
                    jupiter.setTexture(texturasPlanetasInactivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasInactivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 3:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasInactivos["venus"]);
                    tierra.setTexture(texturasPlanetasInactivos["tierra"]);
                    marte.setTexture(texturasPlanetasInactivos["marte"]);
                    jupiter.setTexture(texturasPlanetasInactivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 4:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasInactivos["venus"]);
                    tierra.setTexture(texturasPlanetasInactivos["tierra"]);
                    marte.setTexture(texturasPlanetasInactivos["marte"]);
                    jupiter.setTexture(texturasPlanetasActivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 5:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasInactivos["venus"]);
                    tierra.setTexture(texturasPlanetasInactivos["tierra"]);
                    marte.setTexture(texturasPlanetasActivos["marte"]);
                    jupiter.setTexture(texturasPlanetasActivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 6:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasInactivos["venus"]);
                    tierra.setTexture(texturasPlanetasActivos["tierra"]);
                    marte.setTexture(texturasPlanetasActivos["marte"]);
                    jupiter.setTexture(texturasPlanetasActivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 7:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasInactivos["mercurio"]);
                    venus.setTexture(texturasPlanetasActivos["venus"]);
                    tierra.setTexture(texturasPlanetasActivos["tierra"]);
                    marte.setTexture(texturasPlanetasActivos["marte"]);
                    jupiter.setTexture(texturasPlanetasActivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 8:
                    sol.setTexture(texturasPlanetasInactivos["sol"]);
                    mercurio.setTexture(texturasPlanetasActivos["mercurio"]);
                    venus.setTexture(texturasPlanetasActivos["venus"]);
                    tierra.setTexture(texturasPlanetasActivos["tierra"]);
                    marte.setTexture(texturasPlanetasActivos["marte"]);
                    jupiter.setTexture(texturasPlanetasActivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                case 9:
                    sol.setTexture(texturasPlanetasActivos["sol"]);
                    mercurio.setTexture(texturasPlanetasActivos["mercurio"]);
                    venus.setTexture(texturasPlanetasActivos["venus"]);
                    tierra.setTexture(texturasPlanetasActivos["tierra"]);
                    marte.setTexture(texturasPlanetasActivos["marte"]);
                    jupiter.setTexture(texturasPlanetasActivos["jupiter"]);
                    saturno.setTexture(texturasPlanetasActivos["saturno"]);
                    urano.setTexture(texturasPlanetasActivos["urano"]);
                    break;
                default:
                    break;
            
            }
            
            window.clear();
            window.draw(background);
        
            //dibujar elementos
            window.draw(background);
            window.draw(sol);
            window.draw(mercurio);
            window.draw(venus);
            window.draw(tierra);
            window.draw(marte);
            window.draw(jupiter);
            window.draw(saturno);
            window.draw(urano);
            window.draw(neptuno);
    
            window.display();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == LEVEL_MENU) {
                    if (event.key.code == sf::Keyboard::Down) {
                        currentMenu = MAIN_MENU;
                    } else if (event.key.code == sf::Keyboard::Up) {
                        currentMenu = EXIT;   
                    } else if (event.key.code == sf::Keyboard::Right) {
                        if (currentLevel>=2){
                            currentLevel -= 1;
                        }
                    } else if (event.key.code == sf::Keyboard::Left) {
                        if (currentLevel<=8){
                            currentLevel += 1;
                        }
                    } 
                }
            }
        }
    }
    return currentMenu;
}


Menu menuT(sf::RenderWindow &window, Menu &currentMenu){
    VentanaJuegos datos;
    sf::RectangleShape board;
    sf::Sprite planet;
    sf::Texture texturePLanet;
    sf::Font font;
    
    sf::Text textPlanets;
    sf::Text textMovimientos;
    sf::Text textScore;
    sf::Text textNext;

    texturePLanet.loadFromFile("./niveles/Planetas/VenusActivo.png");
    font.loadFromFile("./Fuentes/prstart.ttf");

    textPlanets.setFont(font);
    textPlanets.setString("Venus");
    textPlanets.setCharacterSize(36);
    textPlanets.setFillColor(sf::Color::White);
    textPlanets.setPosition(50, 50);  // Coordenas X e Y

    planet.setTexture(texturePLanet);
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
    textureFondo.loadFromFile("./menuPrincipal/menuFondo1.png");
    sf::Sprite fondo(textureFondo);
    cargarTexturas();
    sf::Event event;
    while (window.isOpen()&& currentMenu==TABLERO) {
        window.clear();
        window.draw(fondo);
        window.draw(board);
        window.draw(textPlanets);
        window.draw(textMovimientos);
        window.draw(textScore);
        window.draw(textNext);
        window.draw(planet);



        dibujarMatriz(window, datos.filas,  datos.columnas,  datos.celdaAncho,  datos.celdaAlto);
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == TABLERO) {
                    if (event.key.code == sf::Keyboard::Down) {
                        currentMenu = MAIN_MENU;
                    } else if (event.key.code == sf::Keyboard::Up) {
                        currentMenu = EXIT;   
                    } else if (event.key.code == sf::Keyboard::Right) {
                        llenarMatriz();   
                    }
                }
            }
        }
    }
    return currentMenu;
}



int main() {
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Alienigenas Alineados");
    Menu currentMenu = MAIN_MENU;
    llenarMatriz();

    //VentanaJuego ventanaTablero(window, 9, 9, matriz);

    //maquina de estados
    while (currentMenu != EXIT){
        switch (currentMenu) { 
            case MAIN_MENU:
                currentMenu = menuP(window, currentMenu);
                break;

            case LEVEL_MENU:
                    currentMenu = menuN(window, currentMenu);
                break;

            case INSTRUCTIONS_MENU:
                currentMenu = menuI(window, currentMenu);
                break;

            case SETTINGS_MENU:
                currentMenu = menuC(window, currentMenu);
                break;
            
            case TABLERO:
                currentMenu = menuT(window, currentMenu);
                break;

            default:
                break;
        }
    }
    
    return 0;
}



