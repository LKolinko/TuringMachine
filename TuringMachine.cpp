#include "TuringMachine.h"
#include "RoundedRectangle.h"
#include "iostream"

void TuringMachine::Create(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f Cs, int d) {
    if (data.empty()) {
        data.assign(1e5, "");
    }
    pos_ = pos;
    size_ = size;
    thickness = d;
    CellSize = Cs;
}

void TuringMachine::Draw(sf::RenderWindow &wnd, sf::Font &font, sf::Event& event) {

    if (!alph.empty()) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsMousOver(wnd)) {
            input = "";
            is_entered = true;
            float mouseX = sf::Mouse::getPosition(wnd).x;
            mouseX -= pos_.x;
            Click_ind = int((mouseX) / CellSize.x) + int(shift / CellSize.x);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

            int first_ind = 0;
            while (first_ind < data.size() && data[first_ind].empty()) {
                ++first_ind;
            }

            while (first_ind < data.size()) {
                if (data[first_ind].empty()) {
                    bad_ind.insert(first_ind - ind);
                } else {
                    bad_ind.erase(first_ind - ind);
                }
                ++first_ind;
            }

            --first_ind;
            while (data[first_ind].empty()) {
                bad_ind.erase(first_ind - ind);
                --first_ind;
            }

            input = "";
            is_entered = false;
        }
        if (event.type == sf::Event::TextEntered && is_entered) {
            if (event.key.code == 8) {
                data[ind + Click_ind + input.size() - (input.empty() ? 0 : 1)] = "";
                if (!input.empty()) {
                    bad_ind.erase(input.size() - 1 + Click_ind);
                    input.pop_back();
                } else {
                    bad_ind.erase( Click_ind);
                }
            } else {
                if (event.key.code != sf::Keyboard::Enter) {
                    char c[] = {event.key.code};
                    if (c[0] != ' ') {
                        if (alph.find(c[0]) == -1 && sp.find(c[0]) == -1) {
                            bad_ind.insert(input.size() + Click_ind);
                        }
                        input.push_back(c[0]);
                    }
                }
            }
            for (int i = 0; i < input.size(); ++i) {
                data[ind + i + Click_ind] = input[i];
            }
        }
    }

    sf::RenderTexture table;
    table.create(static_cast<unsigned int>(size_.x), static_cast<unsigned int>(size_.y));
    table.clear(sf::Color::White);


    sf::RectangleShape line(sf::Vector2f(thickness, size_.y));
    line.setFillColor(sf::Color::Black);

    line.setPosition({ 0, 0 });
    table.draw(line);

    line.setPosition({ size_.x - thickness, 0 });
    table.draw(line);

    line.setSize(sf::Vector2f(size_.x, thickness));
    line.setPosition(sf::Vector2f(0, 0));
    table.draw(line);

    line.setPosition(sf::Vector2f(0, size_.y - thickness));
    table.draw(line);

    sf::RenderTexture atm;
    atm.create(static_cast<unsigned int>(CellSize.x - thickness * 4), static_cast<unsigned int>(size_.y - 10 - thickness * 4));
    atm.clear(sf::Color::White);

    sf::String lambdaSymbol(L"\u03BB");

    int cnt = int(shift / CellSize.x);
    for (int i = cnt - 1; i + ind < 1e5; ++i) {

        if ((i - cnt - 1) * CellSize.x > size_.x) {
            break;
        }
        sf::Text text;
        text.setFont(font);

        sf::RectangleShape blr({ CellSize.x, size_.y - thickness * 2 });
        blr.setPosition((float) (i - cnt) * CellSize.x - (shift - CellSize.x * cnt),
                        (float) thickness );
        if (is_entered && bad_ind.find(i) == bad_ind.end() && i >= Click_ind && i <= Click_ind + (input.empty() ? 0 : (int)input.size() - 1)) {
            blr.setFillColor(sf::Color::Cyan);
            table.draw(blr);
        } else if (bad_ind.find(i) != bad_ind.end()) {
            blr.setFillColor(sf::Color::Red);
            table.draw(blr);
        }

        if (!data[i + ind].empty()) {
            text.setString(data[i + ind]);
            text.setFillColor(sf::Color::Black);
        } else {
            text.setString(lambdaSymbol);
            text.setFillColor(sf::Color(118, 123, 145));
        }

        text.setCharacterSize(size_.y * 0.7);
        text.setPosition({(float) (i - cnt) * CellSize.x - (shift - CellSize.x * cnt) +
        (float) thickness * 2 + CellSize.x / 2 - text.getLocalBounds().width / 2,
        (float) thickness * 2 + size_.y / 2 - text.getLocalBounds().height });
        table.draw(text);


        text.setPosition({(float) (i - cnt) * CellSize.x - (shift - CellSize.x * cnt + pshiht) +
                          (float) thickness * 2 + (CellSize.x - thickness * 4) / 2 - text.getLocalBounds().width / 2,
                          (float) thickness * 2 + (size_.y - 10 - thickness * 4) / 2
                          - (thickness * 4 + 5) - text.getLocalBounds().height });
        atm.draw(text);


        line.setSize(sf::Vector2f(thickness, size_.y));
        line.setPosition(sf::Vector2f(
                {(float) (i - cnt) * CellSize.x - (shift - CellSize.x * cnt),
                 (float) thickness * 2}));
        table.draw(line);

        line.setPosition(sf::Vector2f(
                {(float) (i - cnt) * CellSize.x - (shift - CellSize.x * cnt) - pshiht - thickness * 4,
                 (float) thickness * 2}));
        atm.draw(line);

    }

    table.display();
    sf::Sprite sprite(table.getTexture());
    sprite.setPosition(pos_.x, pos_.y);

    atm.display();
    sf::Sprite spt(atm.getTexture());
    spt.setPosition(pos_.x + pshiht + thickness * 3, pos_.y + thickness * 4 + 5);

    wnd.draw(sprite);


    RoundedRectangle in, out;
    out.Create(sf::Color(114, 110, 151),
               sf::Vector2f(CellSize.x + thickness * 4, size_.y + thickness * 4),
               sf::Vector2f(pos_.x + pshiht - thickness, pos_.y - thickness),
               10);

    in.Create(sf::Color::White,
              sf::Vector2f(CellSize.x - thickness * 4, size_.y - thickness * 4),
              sf::Vector2f(pos_.x + pshiht + thickness * 3,  pos_.y + thickness * 3),
              10);

    out.Draw(wnd);
    in.Draw(wnd);

    wnd.draw(spt);
}

void TuringMachine::Step(float dist) {
    if (!is_step) {
        return;
    }
    pshiht += dist;

    if (pshiht + CellSize.x > size_.x) {
        pshiht -= dist;
        shift += dist;
    }
    if (pshiht < 0) {
        pshiht -= dist;
        shift += dist;
    }

    if (fabs(pshiht + shift) / CellSize.x == int(fabs(pshiht + shift) / CellSize.x)) {
        is_step = false;
        if (dist < 0) {
            avto_ind -= 1;
        } else {
            avto_ind += 1;
        }
    }
}

bool TuringMachine::IsMousOver(sf::RenderWindow &window) const {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int btnPosX = pos_.x;
    int btnPosY = pos_.y;
    int btnxPosWidth = pos_.x + size_.x;
    int btnyPosHeight = pos_.y + size_.y;
    return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
}

std::string TuringMachine::getChar() {
    if (data[avto_ind].empty()) {
        return "ld";
    }
    return data[avto_ind];
}

void TuringMachine::setQ(std::string a) {
    q = a;
}

std::string TuringMachine::getQ() {
    return q;
}

void TuringMachine::setChar(std::string a) {
    if (a == "ld") {
        data[avto_ind] = "";
    } else {
        data[avto_ind] = a;
    }
}

void TuringMachine::clearData() {
    data.assign(1e5, "");
}
