#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics/Texture.hpp"
#include "utils.hpp"
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
#include <cwchar>
#include <random>
#include <iterator>
#include <optional>
#include <cmath>
#include <vector>

enum class GameState {
    Menu,
    Playing,
    Settings,
    Credits,
    Donate,
    EndButtonConfirm,
    Paused
};

struct Particle {
    sf::CircleShape Particles;
    sf::Vector2f velocity;
    float lifetime;
};

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(0.3f, 2.0f);
    int RandomParticleRadius = distrib(gen);

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

    sf::RectangleShape Right_Paddle({10.f, 800.f});
    Right_Paddle.setPosition({780.f, 0.f});
    Right_Paddle.setFillColor(sf::Color::Blue);

    sf::RectangleShape Left_Paddle({10.f, 100.f});
    Left_Paddle.setPosition({10.f, 380.f});
    Left_Paddle.setFillColor(sf::Color::Blue);

    sf::Text PlayButton(font);
    PlayButton.setString("std::Play();");
    PlayButton.setCharacterSize(24);
    PlayButton.setFillColor(sf::Color::White);
    PlayButton.setPosition({620.f, 250.f});

    sf::Text BackButton(font);
    BackButton.setCharacterSize(24);
    BackButton.setString("return 0;");
    BackButton.setPosition({5.f, 10.f});
    BackButton.setFillColor(sf::Color::White);

    sf::RectangleShape EndButtonConfirmBox({320.f, 150.f});
    EndButtonConfirmBox.setPosition({240.f, 300.f});
    EndButtonConfirmBox.setFillColor(sf::Color::Black);
    EndButtonConfirmBox.setOutlineThickness(-3.f);
    EndButtonConfirmBox.setOutlineColor(sf::Color::White);

    sf::Text EndButtonConfirmText(font);
    EndButtonConfirmText.setString("you want to exit?");
    EndButtonConfirmText.setCharacterSize(24);
    EndButtonConfirmText.setFillColor(sf::Color::White);
    EndButtonConfirmText.setPosition({305.f, 325.f});

    sf::Text EndButton(font);
    EndButton.setString("etl::End();");
    EndButton.setCharacterSize(24);
    EndButton.setFillColor(sf::Color::White);
    EndButton.setPosition({620.f, 350.f});

    sf::Text EndButtonYes(font);
    EndButtonYes.setString("Yes");
    EndButtonYes.setCharacterSize(18);
    EndButtonYes.setFillColor(sf::Color::White);
    EndButtonYes.setPosition({305.f, 405.f});

    sf::Text EndButtonNo(font);
    EndButtonNo.setString("Nah");
    EndButtonNo.setCharacterSize(18);
    EndButtonNo.setFillColor(sf::Color::White);
    EndButtonNo.setPosition({480.f, 600.f});

    sf::Text TitleText(font);
    TitleText.setString("#include <pong.hpp>");
    TitleText.setCharacterSize(48);
    TitleText.setFillColor(sf::Color::White);
    TitleText.setPosition({170.f, 100.f});

    sf::Text CreditsButton(font);
    CreditsButton.setString("glm::Credits();");
    CreditsButton.setCharacterSize(24);
    CreditsButton.setFillColor(sf::Color::White);
    CreditsButton.setPosition({620.f, 300.f});

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

    std::vector<Particle> particles;

    while (window.isOpen()) {

        float LeftZoneHeight = Left_Paddle.getSize().y / 3.f;
        float RightZoneHeight = Right_Paddle.getSize().y / 3.f;
        float BallY= Ball.getPosition().y;
        float Right_PaddleY = Right_Paddle.getPosition().y;
        float Left_PaddleY = Left_Paddle.getPosition().y;

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

            if (state == GameState::Menu && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (EndButton.getGlobalBounds().contains(mousePosition)) {
                   state = GameState::EndButtonConfirm; 
                }
            }

			if (state == GameState::EndButtonConfirm && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (EndButtonYes.getGlobalBounds().contains(mousePosition)) {
                    window.close(); 
                }
			}

            if (state == GameState::EndButtonConfirm && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (EndButtonNo.getGlobalBounds().contains(mousePosition)) {
                    state = GameState::Menu;
                }
            }

            if (state == GameState::Credits && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (BackButton.getGlobalBounds().contains(mousePosition)) {
                    state = GameState::Menu;
                }
            }

            if (state == GameState::Playing && event->is<sf::Event::MouseButtonPressed>()) {
                auto mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (BackButton.getGlobalBounds().contains(mousePosition)) {
                    state = GameState::Menu;
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
            if (BallY < Left_PaddleY + LeftZoneHeight) {
                velocity.y = -10.f;

            } else if (BallY < Left_PaddleY + 2 * LeftZoneHeight) {
                velocity.y = 0.f;

            } else {
                velocity.y = 10.f;
            }

            for (int i = 0; i < 20; i++) {
                Particle particle;

                particle.Particles.setRadius(distrib(gen));
                particle.Particles.setPosition(Ball.getPosition());

                particle.velocity = {
                    static_cast<float>(rand() % 20 - 10),
                    static_cast<float>(rand() % 20 - 10)
                };

                particle.lifetime = 10.f;
                particles.push_back(particle);
        }

        }

        if (Ball.getGlobalBounds().findIntersection(Right_Paddle.getGlobalBounds())) {
            velocity.x = -std::abs(velocity.x);
            if (BallY < Right_PaddleY + RightZoneHeight) {
                velocity.y = -10.f;

            } else if (BallY < Right_PaddleY + 2 * RightZoneHeight) {
                velocity.y = 0.f;

            } else {
                velocity.y = 10.f;
            }


        }

        window.clear();
        for (auto it = particles.begin(); it != particles.end();) {
            it->Particles.move(it->velocity);
            it->lifetime--;

            if (it->lifetime <=0) {
                it = particles.erase(it);

            } else {
                ++it;
            }
        }
 

        switch (state) {
            case GameState::Menu:
                window.draw(PlayButton);
                window.draw(CreditsButton);
                window.draw(TitleText);
                window.draw(EndButton);
                break;

            case GameState::Credits:
                window.draw(CreditsText);
                window.draw(StudioProfileArt);
                window.draw(BackButton);
                break;

            case GameState::Playing:
                window.draw(Left_Paddle);
                window.draw(Right_Paddle);
                window.draw(Ball);
                window.draw(BackButton);

                for (const Particle& particle : particles) {
                    window.draw(particle.Particles);
                }

                Ball.move(velocity);
                break;

            case GameState::EndButtonConfirm:
                window.draw(EndButtonConfirmBox);
                window.draw(EndButtonYes);
                window.draw(EndButtonNo);
                window.draw(EndButtonConfirmText);
 
        }

        window.display();
    }

    return 0;
}
