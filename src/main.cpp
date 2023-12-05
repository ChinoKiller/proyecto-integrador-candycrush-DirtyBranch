#include "Controlador.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>


enum Menu { MAIN_MENU, LEVEL_MENU, INSTRUCTIONS_MENU, SETTINGS_MENU, EXIT, TABLERO, CREDITS_MENU, GAME_OVER, WIN};
int crrntTxreMsc = 0;   //esto debe estar ligado al booleano de la musica
int crrntTxreSfx = 0;   // este al booleando de los efectos de sonido
int currentLevelNumber = 1;


Menu menuP(sf::RenderWindow &window, Menu &currentMenu, sf::Music& music){
    int NUM_FRAMES = 7;
    // Cargar una serie de imágenes en un vector
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= NUM_FRAMES; i++) {
        sf::Texture texture;
        if (texture.loadFromFile("./assets/menuPrincipal/MENU_RESIZED" + std::to_string(i) + ".png")) {
            frames.push_back(texture);
        }
    }
    if(!music.openFromFile("assets/musica/Sailor_Girl.wav")) {
        std::cout << "No se abrió la musica" << std::endl;
    }
    if(crrntTxreMsc==0){
        music.play();
        music.setLoop(true);
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


Menu menuGameOver(sf::RenderWindow &window, Menu &currentMenu){
    int NUM_FRAMES = 15;
    // Cargar una serie de imágenes en un vector
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= NUM_FRAMES; i++) {
        sf::Texture texture;
        if (texture.loadFromFile("./assets/gameOver/game_over" + std::to_string(i) + ".png")) {
            frames.push_back(texture);
        }
    }
    return currentMenu;
}

Menu winMenu(sf::RenderWindow &window, Menu &currentMenu) {
    int NUM_FRAMES = 12;
    // Cargar una serie de imágenes en un vector
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= NUM_FRAMES; i++) {
        sf::Texture texture;
        if (texture.loadFromFile("./assets/sol_gane/GANE_SOL" + std::to_string(i) + ".png")) {
            frames.push_back(texture);
        }
    }

    // Variables para controlar la animación menu principal
    int currentFrame = 0;
    float frameTime = 0.1f;

    while (window.isOpen()&& currentMenu==WIN) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (currentMenu == WIN) {
                    if (event.key.code == sf::Keyboard::X) {
                        currentMenu = MAIN_MENU;
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

Menu menuC(sf::RenderWindow &window, Menu &currentMenu, sf::Music& music){
    sf::Texture textureFondo;
    sf::Texture textureconfigBoard;
    sf::Texture textureMusica;
    sf::Texture textureSfx;
    std::vector<sf::Texture> texturasMusica;
    std::vector<sf::Texture> texturasSfx;
    //sf::Sprite sprite(frames[currentFrame]);
    textureFondo.loadFromFile("./assets/menuPrincipal/menuFondo1.png");
    textureconfigBoard.loadFromFile("./assets/menuConfiguracion/configBoard.png");
    textureMusica.loadFromFile("./assets/menuConfiguracion/musicaActivada.png");
    texturasMusica.push_back(textureMusica);
    textureMusica.loadFromFile("./assets/menuConfiguracion/musicaDesactivada.png");
    texturasMusica.push_back(textureMusica);
    textureSfx.loadFromFile("./assets/menuConfiguracion/sfxActivados.png");
    texturasSfx.push_back(textureSfx);
    textureSfx.loadFromFile("./assets/menuConfiguracion/sfxDesactivados.png");
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
                        currentMenu = CREDITS_MENU;   
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
                        music.pause();
                    } else if(crrntTxreMsc == 1){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreMsc = 0;
                        music.play();
                        music.setLoop(true);
                    }
                } else if (event.key.code == sf::Keyboard::S) {
                    if(crrntTxreSfx == 0){ //activada
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreSfx = 1;
                    } else if(crrntTxreSfx == 1){ //desactivada
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
    texture.loadFromFile("./assets/menuInstrucciones/instrucciones.png");
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
                        texture.loadFromFile("./assets/menuInstrucciones/puntos.png");   
                    } else if (event.key.code == sf::Keyboard::C) {
                        texture.loadFromFile("./assets/menuInstrucciones/combinaciones.png");  
                    } 
                }
            }
        }
    }
    return currentMenu;
}

// Menu Créditos
Menu menuCr(sf::RenderWindow &window, Menu &currentMenu, sf::Music& music){
    std::vector<sf::Texture> frames;
    sf::Texture texture;
    texture.loadFromFile("./assets/menuConfiguraciones/creditos.jpg");
    if(!music.openFromFile("assets/musica/creditos.wav")) {
        std::cout << "No se abrió la musica" << std::endl;
    }
    if(crrntTxreMsc==0){
        music.play();
    }
    while (window.isOpen()&& currentMenu==CREDITS_MENU) {
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
                if (currentMenu == CREDITS_MENU) {
                    if (event.key.code == sf::Keyboard::Left) {
                        currentMenu = MAIN_MENU;
                    } else if (event.key.code == sf::Keyboard::Right) {
                        currentMenu = CREDITS_MENU;   
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
    texture.loadFromFile("./assets/niveles/fondoNiveles.jpg");
    //encendidos
    texturasPlanetasActivos["sol"].loadFromFile("./assets/niveles/Planetas/SolActivo.png");
    texturasPlanetasActivos["mercurio"].loadFromFile("./assets/niveles/Planetas/MercurioActivo.png");
    texturasPlanetasActivos["venus"].loadFromFile("./assets/niveles/Planetas/VenusActivo.png");
    texturasPlanetasActivos["tierra"].loadFromFile("./assets/niveles/Planetas/TierraActivo.png");
    texturasPlanetasActivos["marte"].loadFromFile("./assets/niveles/Planetas/MarteActivo.png");
    texturasPlanetasActivos["jupiter"].loadFromFile("./assets/niveles/Planetas/JupiterActivo.png");
    texturasPlanetasActivos["saturno"].loadFromFile("./assets/niveles/Planetas/SaturnoActivo.png");
    texturasPlanetasActivos["urano"].loadFromFile("./assets/niveles/Planetas/UranoActivo.png");
    texturasPlanetasActivos["neptuno"].loadFromFile("./assets/niveles/Planetas/NeptunoActivo.png");
    //apagados
    texturasPlanetasInactivos["sol"].loadFromFile("./assets/niveles/Planetas/SolInactivo.png");
    texturasPlanetasInactivos["mercurio"].loadFromFile("./assets/niveles/Planetas/MercurioInactivo.png");
    texturasPlanetasInactivos["venus"].loadFromFile("./assets/niveles/Planetas/VenusInactivo.png");
    texturasPlanetasInactivos["tierra"].loadFromFile("./assets/niveles/Planetas/TierraInactivo.png");
    texturasPlanetasInactivos["marte"].loadFromFile("./assets/niveles/Planetas/MarteInactivo.png");
    texturasPlanetasInactivos["jupiter"].loadFromFile("./assets/niveles/Planetas/JupiterInactivo.png");
    texturasPlanetasInactivos["saturno"].loadFromFile("./assets/niveles/Planetas/SaturnoInactivo.png");
    texturasPlanetasInactivos["urano"].loadFromFile("./assets/niveles/Planetas/UranoInactivo.png");
    
    
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

    bool blockedLevels = true;
    if (currentLevelNumber == 10) {
        blockedLevels = false;
    }
    while (window.isOpen()&& currentMenu==LEVEL_MENU) {
        
        switch (currentLevelNumber) {
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
            case 10:
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
                    } else if (event.key.code == sf::Keyboard::X) { 
                        currentMenu = TABLERO;
                    } else if ((event.key.code == sf::Keyboard::Right) && (blockedLevels == false)){
                        if (currentLevelNumber>=2){
                            currentLevelNumber -= 1;
                        }
                    }else if ((event.key.code == sf::Keyboard::Left) && (blockedLevels == false)) {
                        if (currentLevelNumber<=8){
                            currentLevelNumber += 1;
                        }
                    }
                    
                }
            }
        }
    }
    return currentMenu;
}


Menu menuT(sf::RenderWindow &window, Menu &currentMenu){
    // Crear instancia del controlador
    int sfxEnable = crrntTxreSfx;
    if (currentLevelNumber == 10) {
        return WIN;
    }
    if(sfxEnable == 0){
        sfxEnable = 1;
    } else if (sfxEnable == 1){
        sfxEnable = 0;
    } 
	Controlador gameController = Controlador(window, currentLevelNumber, sfxEnable);
    currentLevelNumber = gameController.getCurrentLevel();
	// Controlador crea Nivel y empieza a jugar
    if (gameController.runGame()) {
        // Si se gano el juego ir a menu de niveles
        currentMenu = LEVEL_MENU;
        currentLevelNumber++;
        //gameController.setCurrentLevel(currentLevelNumber);
    } else {
        // Mostrar Game Over
        currentMenu = GAME_OVER;

    }
   
    return currentMenu;
}

int main() {
    sf::Music music;
    music.setVolume(10);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Alienigenas Alienados");
    Menu currentMenu = MAIN_MENU;
    
    //VentanaJuego ventanaTablero(window, 9, 9, matriz);

    //maquina de estados
    while (currentMenu != EXIT){
        switch (currentMenu) { 
            case MAIN_MENU:
                currentMenu = menuP(window, currentMenu, music);
                break;

            case LEVEL_MENU:
                currentMenu = menuN(window, currentMenu);
                break;

            case INSTRUCTIONS_MENU:
                currentMenu = menuI(window, currentMenu);
                break;

            case SETTINGS_MENU:
                currentMenu = menuC(window, currentMenu, music);
                break;
            
            case TABLERO:
                currentMenu = menuT(window, currentMenu);
                break;
            case CREDITS_MENU:
                currentMenu = menuCr(window, currentMenu, music);
                break;
            case GAME_OVER:
                currentMenu = menuGameOver(window, currentMenu);
                break;
            case WIN:
                currentMenu = winMenu(window, currentMenu);
                break;
            default:
                break;
        }
    }
    
    return EXIT_SUCCESS;
}