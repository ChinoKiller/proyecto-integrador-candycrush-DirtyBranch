#include <SFML/Graphics.hpp>
#include <vector>


enum Menu { MAIN_MENU, LEVEL_MENU, INSTRUCTIONS_MENU, SETTINGS_MENU, EXIT};


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


                } else if (event.key.code == sf::Keyboard::Up) {
                    currentMenu = LEVEL_MENU;


                }
            }
        }
    }
    return currentMenu;
}



Menu menuC(sf::RenderWindow &window, Menu &currentMenu){
    std::vector<sf::Texture> frames;
    sf::Texture texture;
    texture.loadFromFile("./menuConfiguracion/configEncendida.jpg");
    while (window.isOpen()&& currentMenu==SETTINGS_MENU) {
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
            if (currentMenu == SETTINGS_MENU) {
                if (event.key.code == 72) {
                    currentMenu = SETTINGS_MENU;   
                } else if (event.key.code == 71) {
                    currentMenu = MAIN_MENU;
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
    std::vector<sf::Texture> frames;
    sf::Texture texture;
    texture.loadFromFile("./Niveles/nivel9.jpg");
    while (window.isOpen()&& currentMenu==LEVEL_MENU) {
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
            if (currentMenu == LEVEL_MENU) {
                if (event.key.code == sf::Keyboard::Down) {
                    currentMenu = MAIN_MENU;
                } else if (event.key.code == sf::Keyboard::Up) {
                    currentMenu = EXIT;   
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

