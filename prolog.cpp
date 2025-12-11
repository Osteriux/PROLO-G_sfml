#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "src/manager/game_manager.hpp"
#include "src/manager/event_manager.hpp"
#include "src/utils/logger/logger.hpp"
#ifdef _DEV_MODE
#include "src/_devTool/debug_console.hpp"
#endif // _DEV_MODE

int main()
{
    // Initialize Logger
    Logger::initialize(Logger::DEBUG, "./log/prolog.log");
#ifdef _RELEASE
    Logger::log("Game started, release mode : true", Logger::INFO);
#else
    Logger::log("Game started, release mode : false", Logger::INFO);
#endif

    sf::Vector2u windowSize(960, 540);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "PR0L0-G");

    // Initialize the GameManager singleton
    GameManager::initialize(windowSize, "assets/level/test3.txt");
    EventManager eventManager;

    sf::Clock clock;

#ifdef _DEV_MODE
    // Initialize debug console (F1 to toggle)
    DebugConsole debugConsole(sf::Vector2f(windowSize.x - 410, 10));
    debugConsole.loadFont("assets/font/arial.ttf");
#endif // _DEV_MODE

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

#ifdef _DEV_MODE
            // Debug console handles input first (F1 and number keys when visible)
            if (!debugConsole.handleInput(event))
            {
                // If console didn't handle it, pass to game
                eventManager.handleEvents(event);
            }
#else
            eventManager.handleEvents(event);
#endif // _DEV_MODE
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // effacement de la fenêtre
        window.clear();

        // dessin de tout ce qu'on a à dessiner
        GameManager::getInstance().draw(window);

        GameManager::getInstance().update(dt);

#ifdef _DEV_MODE
        // Draw debug console overlay (if visible)
        debugConsole.draw(window);
#endif // _DEV_MODE

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    // Clean up the singleton
    GameManager::destroy();

    Logger::log("Game exited", Logger::INFO);
    Logger::destroy();

    return 0;
}