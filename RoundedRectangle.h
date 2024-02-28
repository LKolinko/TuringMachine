#pragma once
#include "SFML/Graphics.hpp"

class RoundedRectangle {
public:
    RoundedRectangle() = default;
    RoundedRectangle(sf::Color color, sf::Vector2f size, sf::Vector2f pos, float radius);
    ~RoundedRectangle() = default;
    void Create(sf::Color color, sf::Vector2f size, sf::Vector2f pos, float radius);
    void Draw(sf::RenderWindow& wnd);
    void Draw(sf::RenderTexture& wnd);
    void SetColor(sf::Color color);
    sf::RectangleShape horisont, vertic;
    sf::Vector2f position;
    sf::Color getColor();
private:
    sf::CircleShape LU, RU, LD, RD;
};