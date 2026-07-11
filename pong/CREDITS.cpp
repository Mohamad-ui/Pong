#include "UTILS.hpp"
#include "CREDITS.hpp"
#include <SFML/Graphics.hpp>

void ShowCredits() {
    sf::Font font;

    if (!font.openFromFile("assets/fonts/VT323/VT323-Regular.ttf")) {
        println("Failed to load font VT323");
    }

    sf::Text CreditsButton(font);
    CreditsButton.setString("sf::Credits");
    CreditsButton.setCharacterSize(24);
    CreditsButton.setFillColor(sf::Color::White);
    CreditsButton.setPosition({650.f, 200.f});

    
}
