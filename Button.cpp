#include "Button.h"
void Button::Create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, std::string btnText, sf::Font &font,
                    float radius) {
    btnWidth = size.x;
    btnHeight = size.y;
    button.Create(color, size, pos, radius);
    text.setString(btnText);
    text.setCharacterSize(button.vertic.getLocalBounds().height / 2.5);
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
    float xPos = (pos.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
    float yPos = (pos.y + btnHeight / 2.7) - (text.getLocalBounds().height / 2);
    text.setPosition(xPos, yPos);
}
Button::Button(sf::Vector2f size, sf::Vector2f pos, sf::Color color, std::string btnText, sf::Font &font,
               float radius) {
    text.setString(btnText);
    text.setCharacterSize(button.vertic.getLocalBounds().height / 2.5);
    text.setFillColor(sf::Color::Black);
    text.setFont(font);
    btnWidth = size.x;
    btnHeight = size.y;
    button.Create(color, size, pos, radius);
    float xPos = (pos.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
    float yPos = (pos.y + btnHeight / 2.7) - (text.getLocalBounds().height / 2);
    text.setPosition(xPos, yPos);
}
void Button::SetBackColor(sf::Color color) {
    button.SetColor(color);
}
void Button::Draw(sf::RenderWindow &window, sf::Font &font) {
    text.setFont(font);
    button.Draw(window);
    window.draw(text);
}
bool Button::isMouseOver(sf::RenderWindow &window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int btnPosX = button.position.x;
    int btnPosY = button.position.y;
    int btnxPosWidth = button.position.x + btnWidth;
    int btnyPosHeight = button.position.y + btnHeight;
    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        SetBackColor(sf::Color(111, 146, 131));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            SetBackColor(sf::Color(105, 109, 125));
            if (!is_cliced) {
                return true;
            }
            is_cliced = true;
        } else {
            is_cliced = false;
        }
    } else {
        SetBackColor(sf::Color(141, 159, 135));
    }
    return false;
}