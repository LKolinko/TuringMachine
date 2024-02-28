#include "RoundedRectangle.h"
RoundedRectangle::RoundedRectangle(sf::Color color, sf::Vector2f size, sf::Vector2f pos, float radius) {
    LU.setRadius(radius);
    LD.setRadius(radius);
    RU.setRadius(radius);
    RD.setRadius(radius);

    LU.setPosition(pos);
    LU.setFillColor(color);

    RU.setPosition({ pos.x + size.x - RU.getRadius() * 2, pos.y });
    RU.setFillColor(color);

    LD.setPosition({ pos.x, pos.y + size.y - RU.getRadius() * 2 });
    LD.setFillColor(color);

    RD.setPosition({ pos.x + size.x - RU.getRadius() * 2, pos.y + size.y - RU.getRadius() * 2 });
    RD.setFillColor(color);

    horisont.setPosition({ pos.x, pos.y + RU.getRadius() });
    horisont.setSize({ size.x, size.y - RU.getRadius() * 2 });
    horisont.setFillColor(color);

    vertic.setPosition({ pos.x + RU.getRadius(), pos.y });
    vertic.setSize({ size.x - RU.getRadius() * 2, size.y });
    vertic.setFillColor(color);

    position = pos;
}
void RoundedRectangle::Create(sf::Color color, sf::Vector2f size, sf::Vector2f pos, float radius) {

    LU.setRadius(radius);
    LD.setRadius(radius);
    RU.setRadius(radius);
    RD.setRadius(radius);

    LU.setPosition(pos);
    LU.setFillColor(color);

    RU.setPosition({ pos.x + size.x - RU.getRadius() * 2, pos.y });
    RU.setFillColor(color);

    LD.setPosition({ pos.x, pos.y + size.y - RU.getRadius() * 2 });
    LD.setFillColor(color);

    RD.setPosition({ pos.x + size.x - RU.getRadius() * 2, pos.y + size.y - RU.getRadius() * 2 });
    RD.setFillColor(color);

    horisont.setPosition({ pos.x, pos.y + RU.getRadius() });
    horisont.setSize({ size.x, size.y - RU.getRadius() * 2 });
    horisont.setFillColor(color);

    vertic.setPosition({ pos.x + RU.getRadius(), pos.y });
    vertic.setSize({ size.x - RU.getRadius() * 2, size.y });
    vertic.setFillColor(color);

    position = pos;
}
void RoundedRectangle::Draw(sf::RenderWindow &wnd) {
    wnd.draw(LU);
    wnd.draw(LD);
    wnd.draw(RU);
    wnd.draw(RD);
    wnd.draw(horisont);
    wnd.draw(vertic);
}
void RoundedRectangle::SetColor(sf::Color color) {
    LU.setFillColor(color);
    LD.setFillColor(color);
    RU.setFillColor(color);
    RD.setFillColor(color);
    horisont.setFillColor(color);
    vertic.setFillColor(color);
}
sf::Color RoundedRectangle::getColor() {
    return horisont.getFillColor();
}

void RoundedRectangle::Draw(sf::RenderTexture &wnd) {
    wnd.draw(LU);
    wnd.draw(LD);
    wnd.draw(RU);
    wnd.draw(RD);
    wnd.draw(horisont);
    wnd.draw(vertic);
}
