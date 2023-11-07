#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

enum Menu { MAIN_MENU, LEVEL_MENU, INSTRUCTIONS_MENU, SETTINGS_MENU, EXIT};
int crrntTxreMsc = 0;   //esto debe estar ligado al booleano de la musica
int crrntTxreSfx = 0;   // este al booleando de los efectos de sonido

int matriz [5][5]={ {4, 2, 3, 4, 5},
                    {2, 5, 5, 3, 4},
                    {4, 2, 3, 5, 4},
                    {5, 2, 2, 4, 2},
                    {4, 2, 3, 4, 5}};


Menu menuP(sf::RenderWindow &window, Menu &currentMenu){
    int NUM_FRAMES = 7;
    // Cargar una serie de imágenes en un vector
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= NUM_FRAMES; i++) {
        sf::Texture texture;
        if (texture.loadFromFile("./menuPrincipal/frame" + std::to_string(i) + ".jpg")) {
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
        }
        // Mostrar el cuadro actual
        window.clear();
        sf::Sprite sprite(frames[currentFrame]);
        window.draw(sprite);
        window.display();

        // Avanzar al siguiente cuadro
        sf::sleep(sf::seconds(frameTime));
        currentFrame = (currentFrame + 1) % frames.size();

        if (event.type == sf::Event::KeyPressed) {
            if (currentMenu == MAIN_MENU) {
                if (event.key.code == 72) {
                    currentMenu = SETTINGS_MENU;

                        
                } else if (event.key.code == 71) {
                    currentMenu = INSTRUCTIONS_MENU;


                } else if (event.key.code == sf::Keyboard::Up) { //////// cambiar "Up" por "X" para probar si les funciona la X
                    currentMenu = LEVEL_MENU;


                }
            }
        }
    }
    return currentMenu;
}



Menu menuC(sf::RenderWindow &window, Menu &currentMenu){
    sf::Texture texture;
    sf::Texture textureMusica;
    sf::Texture textureSfx;
    std::vector<sf::Texture> texturasMusica;
    std::vector<sf::Texture> texturasSfx;
    //sf::Sprite sprite(frames[currentFrame]);
    texture.loadFromFile("./menuConfiguracion/configEncendida.jpg");
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
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        sf::Sprite sprite(texture);
        sf::Sprite musica(texturasMusica[crrntTxreMsc]);
        sf::Sprite sfx(texturasSfx[crrntTxreSfx]);
        musica.setPosition(790, 245);
        sfx.setPosition(790, 360);
        musica.setScale(0.3f, 0.3f);
        sfx.setScale(0.3f, 0.3f);
        window.draw(sprite);
        window.draw(musica);
        window.draw(sfx);
        window.display();
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
                if (event.key.code == sf::Keyboard::Up) {
                    if(crrntTxreMsc == 0){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreMsc = 1;
                    } else if(crrntTxreMsc == 1){
                        sf::sleep(sf::seconds(0.2));
                        crrntTxreMsc = 0;
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
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
    return currentMenu;
}



Menu menuI(sf::RenderWindow &window, Menu &currentMenu){
    std::vector<sf::Texture> frames;
    sf::Texture texture;
    texture.loadFromFile("./menuInstrucciones/instrucciones.jpg");
    while (window.isOpen()&& currentMenu==INSTRUCTIONS_MENU) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        sf::Sprite sprite(texture);
        window.draw(sprite);
        window.display();
        if (event.type == sf::Event::KeyPressed) {
            if (currentMenu == INSTRUCTIONS_MENU) {
                if (event.key.code == 72) {
                    currentMenu = MAIN_MENU;
                } else if (event.key.code == 71) {
                    currentMenu = INSTRUCTIONS_MENU;   
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
    
    /*
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
    */

    //textura fondo
     background.setSize(sf::Vector2f(1280, 720));
    background.setTexture(&texture);
    
    


    while (window.isOpen()&& currentMenu==LEVEL_MENU) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
          window.draw(background);
     /*
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
     */

               // Dibujar la matriz de planetas
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int planetaID = matriz[i][j]; // Obtén el número de la matriz
                std::string clave;

                switch (planetaID)
                {
                case 1:
                    clave = "venus";
                    break;
                case 2:
                    clave = "mercurio";
                    break;
                case 3:
                    clave = "venus";
                    break;
                case 4:
                    clave = "tierra";
                    break;
                case 5:
                    clave = "marte";
                    break;
                case 6:
                    clave = "marte";
                    break;
                case 7:
                    clave = "tierra";
                    break;
                case 8:
                    clave = "urano";
                    break;
                case 9:
                    clave = "neptuno";
                    break;
                
                default:
                    break;
                }

                // Crea un sprite para el planeta utilizando la textura correspondiente
                sf::Sprite planetaSprite(texturasPlanetasActivos[clave]);

                // Establece el tamanio
                planetaSprite.setScale(0.14, 0.14);

                // Establece la posición del sprite en la ventana
                planetaSprite.setPosition(10 + j * 50, 10 + i * 50);

                // Dibuja el sprite en la ventana
                window.draw(planetaSprite);
            }
        }




        window.display();

        sf::sleep(sf::seconds(0.5));
        if (event.type == sf::Event::KeyPressed) {
            if (currentMenu == LEVEL_MENU) {
                if (event.key.code == sf::Keyboard::Down) {
                    currentMenu = MAIN_MENU;
                } else if (event.key.code == sf::Keyboard::Up) {
                    currentMenu = EXIT;   
                } else if (event.key.code == sf::Keyboard::Right) {
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            matriz[i][j] += 1; 
                        }
                    }
                } else if (event.key.code == sf::Keyboard::Left) {
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            matriz[i][j] -= 1; 
                        }
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

            default:
                break;
        }
    }
    
    return 0;
}



