#pragma once
#include "SFML/Graphics.hpp"
#include "RoundedRectangle.h"
#include <string>

class TextBox {
public:
    void Create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, sf::Font& font, std::string title, float radius);
    void enter(sf::Event& event, sf::RenderWindow& wnd);
    void enter(sf::Event& event, sf::RenderTexture& wnd);
    bool isMousOver(sf::RenderWindow& wnd);
    void Draw(sf::RenderWindow& wnd);
    void Draw(sf::RenderTexture& wnd);
    void setActive(bool Active);
    void Clear();
    std::string get_text();
private:
    bool is_title = true;
    float ft;
    sf::Vector2f position;
    int start = 0;
    int TextBoxWidth;
    int TextBoxHeight;
    bool is_active = false;
    RoundedRectangle back;
    std::string str_;
    sf::Text text_;
    sf::Text title;
};
