#pragma once
#include "SFML/Graphics.hpp"
#include "vector"
#include <string>
#include <set>
#include <cmath>

class TuringMachine {
public:
    TuringMachine() = default;
    ~TuringMachine() = default;
    void Create(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f Cs, int d);
    void Draw(sf::RenderWindow& wnd, sf::Font& font, sf::Event& event);
    void Step(float dist);
    void clearData();

    std::string getChar();
    void setChar(std::string a);
    void setQ(std::string a);
    std::string getQ();

    bool IsMousOver(sf::RenderWindow &window) const;

    bool is_entered = false;
    bool is_step = false;
    std::vector<std::string> data;
    std::string alph, sp;

    std::set<int> bad_ind;

private:
    std::string q;
    std::string input;
    int Click_ind;
    float pshiht = 0;
    int avto_ind = 5e4;
    int ind = 5e4;
    std::pair<int, char> st;
    int thickness;
    sf::Vector2f pos_, size_, CellSize;
    float shift = 0;
};
