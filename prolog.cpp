#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "src/manager/game_manager.h"
#include "src/manager/event_manager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "PROLO-G");

    GameManager gameManager;
    EventManager eventManager(&gameManager);

    sf::Clock clock;

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed){
                window.close();
            }
            eventManager.handleEvents(event);
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // effacement de la fenêtre
        window.clear();

        // dessin de tout ce qu'on a à dessiner
        gameManager.draw(window);

        gameManager.update(dt);

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}