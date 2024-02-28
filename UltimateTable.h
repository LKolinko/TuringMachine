#pragma once
#include "SFML/Graphics.hpp"
#include "RoundedRectangle.h"
#include "TextBox.h"
#include <vector>
#include <string>

class UltimateTable {
public:
    UltimateTable() = default;
    ~UltimateTable() = default;
    void Create(sf::Vector2f size, sf::Vector2f pos, sf::Color Frame, sf::Color Cin,
                float FrameThickness, float radius, sf::Vector2f CellSZ);
    void Draw(sf::RenderWindow& wnd, sf::Font& font, sf::Event event);
    bool isMouseOver(sf::RenderWindow& window);
    void Scroll(std::pair<int, int> a);
    void EnterSpawn(sf::RenderWindow& wnd);
    void SetData(std::vector<std::vector<std::string>> dt);
    std::vector<std::vector<std::string>> get_data();
    void ToCell(int i, int j);
    std::string getCell(int i, int j);
private:
    int Filli = -1, Fillj = -1;
    int enter_i, enter_j;
    bool is_enter = false;
    TextBox enter;
    float ft;
    sf::Vector2f position;
    std::vector<std::vector<std::string>> data;
    sf::Vector2f CellSize;
    sf::Vector2f Start;
    RoundedRectangle out;
    RoundedRectangle in;
};