#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics/Texture.hpp"
#include "UTILS.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cstdlib>
#include <optional>
#include <cmath>

enum class GameState {
    Menu,
    Playing,
    Settings,
    Credits,
    Donate,
    Paused
};

int main() {
    GameState state = GameState::Menu;
    sf::Font font;
    sf::Vector2f velocity(5.f, 5.f);
    sf::Texture texture;

    sf::RenderWindow window(sf::VideoMode({800, 800}), "Pong :D");

    if (!texture.loadFromFile("assets/images/StudioProfileArt/EdgyAlapca.png")) {
        println("Failed to load StudioProfileArt"); 
    }

    if (!font.openFromFile("assets/fonts/VT323/VT323-Regular.ttf")) {
        println("Failed to load font VT323");
    }

    sf::RectangleShape Right_Paddle({10.f, 100.f});
    Right_Paddle.setPosition({780.f, 380.f});
    Right_Paddle.setFillColor(sf::Color::Blue);

    sf::RectangleShape Left_Paddle({10.f, 100.f});
    Left_Paddle.setPosition({10.f, 380.f});
    Left_Paddle.setFillColor(sf::Color::Blue);

    sf::Text PlayButton(font);
    PlayButton.setString("std::Play");
    PlayButton.setCharacterSize(24);
    PlayButton.setFillColor(sf::Color::White);
    PlayButton.setPosition({650.f, 250.f});

    sf::Text TitleText(font);
    TitleText.setString("#Include <Pong>");
    TitleText.setCharacterSize(48);
    TitleText.setFillColor(sf::Color::White);
    TitleText.setPosition({170.f, 100.f});

    sf::Text CreditsButton(font);
    CreditsButton.setString("sf::Credits");
    CreditsButton.setCharacterSize(24);
    CreditsButton.setFillColor(sf::Color::White);
    CreditsButton.setPosition({650.f, 300.f});

    sf::Sprite StudioProfileArt(texture);
    StudioProfileArt.setPosition({200.f, 200.f}); 

    sf::Text CreditsText(font);
    CreditsText.setString("Name's Alpaca... Edgy Alpaca");
    CreditsText.setCharacterSize(24);
    CreditsText.setFillColor(sf::Color::White);
    CreditsText.setPosition({250.f, 550.f});

    sf::CircleShape Ball(10.f);
    Ball.setPosition({30.f, 400.f});
    Ball.setFillColor(sf::Color::Blue);

    StudioProfileArt.setScale({0.3f, 0.3f});

    float speed = 10.f;

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }        
        

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
               if (key->code == sf::Keyboard::Key::W) {
                Left_Paddle.move({0.f, -speed});
               }
            
                if (key->code == sf::Keyboard::Key::S) {
                Left_Paddle.move({0.f, speed});
               }
            }

            if (const auto* MousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                print(MousePressed->position.x);
                print(",");
                println(MousePressed->position.y);
            }

            if (state == GameState::Menu && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (PlayButton.getGlobalBounds().contains(mousePosition)) {
                    state = GameState::Playing;
                }
            }

            if (state == GameState::Menu && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (CreditsButton.getGlobalBounds().contains(mousePosition)) {
                    state = GameState::Credits;
                }
            }
        }


        if (Ball.getPosition().x < 0) {
            window.close();
        }

        if (Ball.getPosition().x > 800) {
            window.close();
        }

        if (Ball.getPosition().y < 0) {
            velocity.y = std::abs(velocity.y);    
        }    

        if (Ball.getPosition().y > 780) {
            velocity.y = -std::abs(velocity.y);
        }

        if (Ball.getGlobalBounds().findIntersection(Left_Paddle.getGlobalBounds())) {
            velocity.x = std::abs(velocity.x); 
        }

        if (Ball.getGlobalBounds().findIntersection(Right_Paddle.getGlobalBounds())) {
            velocity.x = -std::abs(velocity.x); 
        }

        window.clear();

        if (state == GameState::Menu) {
           window.draw(PlayButton); 
           window.draw(CreditsButton);
           window.draw(TitleText);
        }

        if (state == GameState::Credits) {
            window.draw(CreditsText);
            window.draw(StudioProfileArt);
        }

        if (state == GameState::Playing) {
           window.draw(Left_Paddle);
           window.draw(Right_Paddle);
           window.draw(Ball);
           Ball.move(velocity);
        }

        window.display();
    }

    return 0;
}
