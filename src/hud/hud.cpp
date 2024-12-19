#include "hud.h"

HUD::HUD(sf::Vector2u origin, sf::Vector2u size, Joueur* joueur)
    : origin(origin), size(size), joueur(joueur),
      leftArrow(sf::Vector2f(origin.x + 10, origin.y + 110), sf::Vector2f(32,32), "assets/boutons/LEFT.png"),
      downArrow(sf::Vector2f(origin.x + 50, origin.y + 150), sf::Vector2f(32,32), "assets/boutons/DOWN.png"),
      rightArrow(sf::Vector2f(origin.x + 90, origin.y + 110), sf::Vector2f(32,32), "assets/boutons/RIGHT.png"),
      upArrow(sf::Vector2f(origin.x + 50, origin.y + 70), sf::Vector2f(32,32), "assets/boutons/UP.png"),
      useRadar(sf::Vector2f(origin.x + 50, origin.y + 110), sf::Vector2f(32,32), "assets/boutons/RADAR.png"),
      mineB(sf::Vector2f(origin.x + 140, origin.y + 90), sf::Vector2f(32,32), "assets/hud/MINE.png"),
      batterieB(sf::Vector2f(origin.x + 200, origin.y + 90), sf::Vector2f(32,32), "assets/hud/BATTERIE.png"),
      bombeB(sf::Vector2f(origin.x + 140, origin.y + 130), sf::Vector2f(32,32), "assets/hud/BOMBE.png"),
      detecteurB(sf::Vector2f(origin.x + 200, origin.y + 130), sf::Vector2f(32,32), "assets/hud/DETECTEUR.png")
{
    if (!font.loadFromFile("assets/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font : assets/fonts/arial.ttf" << std::endl;
    }
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outline.setPosition(sf::Vector2f(origin));
    outline.setSize(sf::Vector2f(size.x, size.y));

    heart.setSize(sf::Vector2f(32, 32));
    heart.setPosition(sf::Vector2f(origin.x + 10, origin.y + 10));
    heart.setFillColor(sf::Color::Red);

    mineT.setFont(font);
    mineT.setCharacterSize(20);
    mineT.setFillColor(sf::Color::White);
    mineT.setPosition(sf::Vector2f(origin.x + 180, origin.y + 100));
    mineT.setString("0");

    batterieT.setFont(font);
    batterieT.setCharacterSize(20);
    batterieT.setFillColor(sf::Color::White);
    batterieT.setPosition(sf::Vector2f(origin.x + 240, origin.y + 100));
    batterieT.setString("0");

    bombeT.setFont(font);
    bombeT.setCharacterSize(20);
    bombeT.setFillColor(sf::Color::White);
    bombeT.setPosition(sf::Vector2f(origin.x + 180, origin.y + 140));
    bombeT.setString("0");

    detecteurT.setFont(font);
    detecteurT.setCharacterSize(20);
    detecteurT.setFillColor(sf::Color::White);
    detecteurT.setPosition(sf::Vector2f(origin.x + 240, origin.y + 140));
    detecteurT.setString("0");

    ramasserText.setFont(font);
    ramasserText.setCharacterSize(20);
    ramasserText.setFillColor(sf::Color::White);
    ramasserText.setPosition(sf::Vector2f(origin.x + 10, origin.y + 190));
    ramasserText.setString("Ramasser :");
    // ramasserActions.push_back(ButtonImage(sf::Vector2f(origin.x + 10, origin.y + 310), sf::Vector2f(32,32), "assets/boutons/ITEM.png"));

    interagireText.setFont(font);
    interagireText.setCharacterSize(24);
    interagireText.setFillColor(sf::Color::White);
    interagireText.setPosition(sf::Vector2f(origin.x + 10, origin.y + 350));
    interagireText.setString("Interagir :");
    // interagireActions.push_back(ButtonImage(sf::Vector2f(origin.x + 10, origin.y + 390), sf::Vector2f(32,32), "assets/boutons/ITEM.png"));

    buttonsText.setFont(font);
    buttonsText.setCharacterSize(24);
    buttonsText.setFillColor(sf::Color::White);
    buttonsText.setPosition(sf::Vector2f(origin.x + 10, origin.y + 430));
    buttonsText.setString("Boutons : ON/OFF");
    // buttonsActions.push_back(ButtonLevier(sf::Vector2f(origin.x + 10, origin.y + 470), sf::Vector2f(32,32), "assets/boutons/ITEM.png"));
}

void HUD::onClic(sf::Vector2f mousePosition)
{
    if (leftArrow.isClicked(mousePosition))
    {
        std::cout << "left" << std::endl;
        joueur->move(Direction::LEFT);
    }
    else if (downArrow.isClicked(mousePosition))
    {
        std::cout << "down" << std::endl;
        joueur->move(Direction::DOWN);
    }
    else if (rightArrow.isClicked(mousePosition))
    {
        std::cout << "right" << std::endl;
        joueur->move(Direction::RIGHT);
    }
    else if (upArrow.isClicked(mousePosition))
    {
        std::cout << "up" << std::endl;
        joueur->move(Direction::UP);
    }
    else if (useRadar.isClicked(mousePosition))
    {
        std::cout << "radar" << std::endl;
        // joueur->useRadar();
    }
    else if (mineB.isClicked(mousePosition))
    {
        std::cout << "mine" << std::endl;
        // joueur->useItem(Item::ItemType::MINE);
    }
    else if (batterieB.isClicked(mousePosition))
    {
        std::cout << "batterie" << std::endl;
        // joueur->useItem(Item::ItemType::BATTERIE);
    }
    else if (bombeB.isClicked(mousePosition))
    {
        std::cout << "bombe" << std::endl;
        // joueur->useItem(Item::ItemType::BOMBE);
    }
    else if (detecteurB.isClicked(mousePosition))
    {
        std::cout << "detecteur" << std::endl;
        // joueur->useItem(Item::ItemType::DETECTEUR);
    }
}

void HUD::update(float dt)
{
    mineT.setString(std::to_string(joueur->getInventaire().getQuantity(Item::ItemType::MINE)));
    batterieT.setString(std::to_string(joueur->getInventaire().getQuantity(Item::ItemType::BATTERIE)));
    bombeT.setString(std::to_string(joueur->getInventaire().getQuantity(Item::ItemType::BOMBE)));
    detecteurT.setString(std::to_string(joueur->getInventaire().getQuantity(Item::ItemType::DETECTEUR)));
}

void HUD::draw(sf::RenderWindow &window)
{
    window.draw(outline);
    for(int h = 0; h < joueur->getHealth(); h++)
    {
        heart.setPosition(sf::Vector2f(origin.x + 10 + h*50, origin.y + 10));
        window.draw(heart);
    }
    leftArrow.draw(window);
    downArrow.draw(window);
    rightArrow.draw(window);
    upArrow.draw(window);
    useRadar.draw(window);
    mineB.draw(window);
    window.draw(mineT);
    batterieB.draw(window);
    window.draw(batterieT);
    bombeB.draw(window);
    window.draw(bombeT);
    detecteurB.draw(window);
    window.draw(detecteurT);
    window.draw(ramasserText);
    for (auto &action : ramasserActions)
    {
        action.draw(window);
    }
    window.draw(interagireText);
    for (auto &action : interagireActions)
    {
        action.draw(window);
    }
    window.draw(buttonsText);
    for (auto &action : buttonsActions)
    {
        action.draw(window);
    }
}