#pragma once
#include <SFML/Graphics.hpp>
#include "RoundedRectangle.h"
class Button {
public:
    Button() = default;
    Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color, std::string btnText, sf::Font& font, float radius);
    void Create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, std::string btnText, sf::Font& font, float radius);
    void SetBackColor(sf::Color color);
    void Draw(sf::RenderWindow& window, sf::Font& font);
    bool isMouseOver(sf::RenderWindow& window);
private:
    bool is_cliced = false;
    RoundedRectangle button;
    sf::Text text;
    int btnWidth;
    int btnHeight;
};
