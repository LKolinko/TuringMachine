#include "UltimateTable.h"

#include <iostream>

void UltimateTable::Create(sf::Vector2f size, sf::Vector2f pos, sf::Color Frame, sf::Color Cin,
                           float FrameThickness, float radius, sf::Vector2f CellSZ) {
    out.Create(Frame, size, pos, radius);
    in.Create(Cin, sf::Vector2f({ size.x - FrameThickness * 2, size.y - FrameThickness * 2 }),
              sf::Vector2f({ pos.x + FrameThickness, pos.y + FrameThickness }), radius / 2);
    CellSize = CellSZ;
    ft = FrameThickness;
    position = { pos.x + ft / 2, pos.y + ft / 2 };
}
void UltimateTable::Draw(sf::RenderWindow &wnd, sf::Font& font, sf::Event event) {

    sf::RenderTexture table;
    table.create(static_cast<unsigned int>(in.horisont.getLocalBounds().width - ft - CellSize.x), static_cast<unsigned int>(in.vertic.getLocalBounds().height - ft - CellSize.y));
    table.clear(in.getColor());

    sf::RenderTexture up;
    up.create(static_cast<unsigned int>(in.horisont.getLocalBounds().width - ft - CellSize.x), static_cast<unsigned int>(CellSize.y));
    up.clear(in.getColor());

    sf::RenderTexture left;
    left.create(static_cast<unsigned int>(CellSize.x), static_cast<unsigned int>(in.vertic.getLocalBounds().height - ft - CellSize.y));
    left.clear(in.getColor());

    out.Draw(wnd);
    in.Draw(wnd);

    sf::String lambdaSymbol(L"\u03BB");

    sf::RectangleShape line(sf::Vector2f(2, in.vertic.getSize().y));
    line.setFillColor(sf::Color::Black);

    int cnt = int(Start.x / CellSize.x);

    for (int i = cnt + 1; i < data[0].size(); ++i) {
        if ((i - cnt - 2) * CellSize.x > table.getSize().x) {
            break;
        }
        sf::Text text;
        text.setFont(font);
        if (data[0][i - 1] != "ld") {
            text.setString(data[0][i - 1]);
        } else {
            text.setString(lambdaSymbol);
        }
        text.setCharacterSize(CellSize.y * 0.7);
        text.setFillColor(sf::Color::Black);

        text.setPosition(sf::Vector2f((float)(i - cnt) * CellSize.x - text.getLocalBounds().width / 2 - (Start.x - CellSize.x * cnt)  - CellSize.x / 2,
                                      CellSize.y / 2 - text.getLocalBounds().height / 1.5));
        up.draw(text);

        line.setPosition(sf::Vector2f({ (float)(i - cnt) * CellSize.x - (Start.x - CellSize.x * cnt), 0 }));
        table.draw(line);
        line.setPosition(sf::Vector2f({ (float)(i - cnt) * CellSize.x - (Start.x - CellSize.x * cnt), 0 }));
        up.draw(line);
    }


    cnt = int(Start.y / CellSize.y);
    line.setSize(sf::Vector2f(in.horisont.getSize().x, 2));
    for (int i = cnt + 1; i < data.size(); ++i) {
        if ((i - cnt - 2) * CellSize.y > table.getSize().y) {
            break;
        }
        sf::Text text;
        text.setFont(font);

        if (data[i][0] != "ld") {
            text.setString(data[i][0]);
        } else {
            text.setString(lambdaSymbol);
        }
        text.setCharacterSize(CellSize.y * 0.7);
        text.setFillColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(CellSize.x / 2 - text.getLocalBounds().width / 2,
                                      (float)(i - cnt) * CellSize.y - text.getLocalBounds().height / 1.5 - (Start.y - CellSize.y * cnt) - CellSize.y / 2));
        left.draw(text);

        line.setPosition(sf::Vector2f({ 0, (float)(i - cnt) * CellSize.y - (Start.y - CellSize.y * cnt) }));
        table.draw(line);
        line.setPosition(sf::Vector2f({ 0, (float)(i - cnt) * CellSize.y - (Start.y - CellSize.y * cnt) }));
        left.draw(line);
    }


    int cnt_x = int(Start.x / CellSize.x),
    cnt_y = int(Start.y / CellSize.y);
    for (int i = cnt_y; i < data.size() - 1; ++i) {
        if ((i - cnt_y - 2) * CellSize.y > table.getSize().y) {
            break;
        }
        for (int j = cnt_x; j < data[i].size() - 1; ++j) {
            if ((j - cnt_x - 2) * CellSize.x > table.getSize().x) {
                break;
            }
            if (i == Filli && j == Fillj) {
                sf::RectangleShape blr({CellSize.x - 2, CellSize.y - 2});
                blr.setPosition({(float)(j - cnt_x) * CellSize.x - (Start.x - CellSize.x * cnt_x) + 2
                                        , (float) (i - cnt_y) * CellSize.y - (Start.y - CellSize.y * cnt_y) + 2} );
                blr.setFillColor(sf::Color(48, 99, 142));
                table.draw(blr);
            }
            if (is_enter && i + 1 == enter_i && j + 1 == enter_j) {
                enter.Create({ CellSize.x - 2, CellSize.y - 2 },
                             sf::Vector2f({(float)(j - cnt_x) * CellSize.x - (Start.x - CellSize.x * cnt_x) + 2
                                           , (float) (i - cnt_y) * CellSize.y - (Start.y - CellSize.y * cnt_y) + 2}),
                             sf::Color(118, 152, 179), font, "", 0);

                enter.Draw(table);
            } else {
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(CellSize.y * 0.5);
                text.setFillColor(sf::Color::Black);
                text.setString(data[i + 1][j + 1]);
                if (data[i + 1][j + 1].size() >= 2 && data[i + 1][j + 1][0] == 'l' && data[i + 1][j + 1][1] == 'd') {
                    sf::String dt = lambdaSymbol;
                    for (int k = 2; k < data[i + 1][j + 1].size(); ++k) {
                        dt += data[i + 1][j + 1][k];
                    }
                    text.setString(dt);
                }
                text.setPosition(sf::Vector2f((float) (j - cnt_x + 1) * CellSize.x - text.getLocalBounds().width / 2 -
                                              (Start.x - CellSize.x * cnt_x) - CellSize.x / 2,
                                              (float) (i - cnt_y + 1) * CellSize.y -
                                              text.getLocalBounds().height / 1.5 -
                                              (Start.y - CellSize.y * cnt_y) - CellSize.y / 2));
                table.draw(text);
            }
        }
    }

    if (is_enter) {
        enter.enter(event, wnd);
    }

    table.display();
    sf::Sprite sprite(table.getTexture());
    sprite.setPosition(position.x + CellSize.x + ft, position.y + CellSize.y + ft);
    wnd.draw(sprite);

    up.display();
    sf::Sprite sp2(up.getTexture());
    sp2.setPosition(position.x + CellSize.x + ft, position.y + ft);
    wnd.draw(sp2);

    left.display();
    sf::Sprite sp3(left.getTexture());
    sp3.setPosition(position.x + ft, position.y + ft + CellSize.y);
    wnd.draw(sp3);

    line.setSize(sf::Vector2f(in.horisont.getSize().x - ft, 2));
    line.setPosition(sf::Vector2f(position.x + ft, position.y + CellSize.y + ft));
    wnd.draw(line);

    line.setSize(sf::Vector2f(2, in.vertic.getSize().y - ft));
    line.setPosition(sf::Vector2f(position.x + CellSize.x + ft, position.y + ft));
    wnd.draw(line);
}
bool UltimateTable::isMouseOver(sf::RenderWindow &window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int btnPosX = out.position.x;
    int btnPosY = out.position.y;
    int btnxPosWidth = btnPosX + out.horisont.getSize().x;
    int btnyPosHeight = btnPosY + out.vertic.getSize().y;
    return (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY);
}
void UltimateTable::Scroll(std::pair<int, int> a) {
    Start.y -= (float)a.first * 5;
    Start.x -= (float)a.second * 5;
    Start.x = std::max(Start.x, (float)0);
    Start.y = std::max(Start.y, (float)0);

}
void UltimateTable::SetData(std::vector<std::vector<std::string>> dt) {
    data = dt;
}

void UltimateTable::EnterSpawn(sf::RenderWindow &wnd) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (isMouseOver(wnd)) {
            int mouseX = sf::Mouse::getPosition(wnd).x;
            int mouseY = sf::Mouse::getPosition(wnd).y;

            int PosX = in.position.x;
            int PosY = in.position.y;

            enter_i = (mouseY - PosY + Start.y) / CellSize.y;
            enter_j = (mouseX - PosX + Start.x) / CellSize.x;

            if (enter_i != 0 && enter_j != 0) {
                is_enter = true;
                enter.setActive(true);
            }

        } else {
            is_enter = false;
        }
    }
    if (is_enter) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            data[enter_i][enter_j] = enter.get_text();
            is_enter = false;
            enter.Clear();
        }
    }
}

std::vector<std::vector<std::string>> UltimateTable::get_data() {
    return data;
}

void UltimateTable::ToCell(int i, int j) {
    Filli = i;
    Fillj = j;
    //Start.x = j * CellSize.x;
    //Start.y = i * CellSize.y;
}

std::string UltimateTable::getCell(int i, int j) {
    return data[i][j];
}
