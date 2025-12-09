#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "src/manager/game_manager.hpp"
#include "src/manager/event_manager.hpp"
#ifndef _RELEASE
#include "src/_devTool/debug_console.hpp"
#endif // _RELEASE

int main()
{
    sf::Vector2u baseSize(480, 270);
    sf::Vector2u scale(2, 2);
    sf::Vector2u windowSize = sf::Vector2u(baseSize.x * scale.x, baseSize.y * scale.y);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "PROLO-G");

    // Initialize the GameManager singleton
    GameManager::initialize(windowSize, "assets/level/test3.txt");
    EventManager eventManager;

    sf::Clock clock;

#ifndef _RELEASE
    // Initialize debug console (F1 to toggle)
    DebugConsole debugConsole(sf::Vector2f(windowSize.x - 410, 10));
    debugConsole.loadFont("assets/font/arial.ttf");
#endif // _RELEASE

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

#ifndef _RELEASE
            // Debug console handles input first (F1 and number keys when visible)
            if (!debugConsole.handleInput(event))
            {
                // If console didn't handle it, pass to game
                eventManager.handleEvents(event);
            }
#else
            eventManager.handleEvents(event);
#endif // _RELEASE
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // effacement de la fenêtre
        window.clear();

        // dessin de tout ce qu'on a à dessiner
        GameManager::getInstance().draw(window);

        GameManager::getInstance().update(dt);

#ifndef _RELEASE
        // Draw debug console overlay (if visible)
        debugConsole.draw(window);
#endif // _RELEASE

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    // Clean up the singleton
    GameManager::destroy();

    return 0;
}