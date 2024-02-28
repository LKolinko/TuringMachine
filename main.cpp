#pragma gcc optimize("O3")
#include "TuringMachine.h"
#include "Screen.h"
#include "UltimateTable.h"
#include "TextBox.h"
#include "Button.h"
#include <iostream>
#include <map>
UltimateTable table;
TuringMachine tm;
std::string englishKeyboard = "\"#$%&'()*+-/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^abcdefghijklmnopqrstuvwxyz{|}~";
std::vector<std::vector<std::string>> data(1000, std::vector<std::string>(englishKeyboard.size() + 1, ""));

bool is_do_tact = false, DoingTacts = false;
int cnt = 0, speed = 10, dist = 1, from = 1;
std::map<std::string, int> sm, spch;

void SetAlph(std::string a) {
    sm.clear();
    while (*data[0].begin() != "ld") {
        data[0].erase(data[0].begin());
        data[0].push_back("");
    }
    std::sort(a.rbegin(), a.rend());

    for (int i = a.size() - 1; i >= 0; --i) {
        std::string s;
        s.push_back(a[i]);
        sm[s] = a.size() - i;
    }

    for (auto u : a) {
        std::string s;
        s.push_back(u);
        data[0].insert(data[0].begin(), s);
    }

    std::string ld = "ld";
    sm[ld] = a.size() + 1;

    tm.alph = a;
    table.SetData(data);
}

void SetSp(std::string a) {
    spch.clear();

    int ind = 0;
    while (data[0][ind] != "ld") {
        ++ind;
    }

    for (int i = 0; i < a.size(); ++i) {
        std::string s = "";
        s.push_back(a[i]);

        spch[s] = ind + 2;

        data[0][++ind] = a[i];
    }
    while (ind + 1 < data[0].size()) {
        data[0][++ind] = "";
    }
    table.SetData(data);
    tm.sp = a;
}

bool is_bad() {
    auto u = table.get_data();
    bool flag = true;
    for (auto x : u) {
        for (auto e : x) {
            if (!e.empty() && e.back() == '!') {
                flag = false;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }
    bool f2 = false;
    for (int i = 1; i < data.size(); ++i) {
        for (int j = 1; j < data[i].size(); ++j) {
            if (!u[i][j].empty() && std::count(u[i][j].begin(), u[i][j].end(), ',') != 2) {
                f2 = true;
                break;
            }
        }
    }
    return flag || f2 || (!tm.bad_ind.empty());
}

void DoTact() {
    if (!is_do_tact) {
        return;
    }
    std::string q = tm.getQ();
    std::string ch = tm.getChar();

    if (!tm.is_step) {
        q.erase(q.begin());
        int i = std::stoi(q) + 1;
        int j;
        if (sm.find(ch) != sm.end()) {
            j = sm[ch];
        }
        if (spch.find(ch) != spch.end()) {
            j = spch[ch];
        }

        std::string tac = table.getCell(i, j);
        table.ToCell(i - 1, j - 1, sf::Color(48, 99, 142));

        if (tac.empty()) {
            table.ToCell(i - 1, j - 1, sf::Color::Red);
            is_do_tact = false;
            DoingTacts = false;
            return;
        }

        int ind = 0;
        std::string s;
        while (tac[ind] != ',') {
            s.push_back(tac[ind]);
            ++ind;
        }
        if (!s.empty()) {
            tm.setChar(s);
        }

        ++ind;

        if (tac[ind] == 'R') {
            from = 1;
            tm.is_step = true;
        }
        if (tac[ind] == 'L') {
            from = -1;
            tm.is_step = true;
        }

        while (ind < tac.size() && tac[ind] != 'q' && tac[ind] != '!') {
            ++ind;
        }

        q = "";
        while (ind < tac.size()) {
            q.push_back(tac[ind]);
            ++ind;
        }
        if (q == "!") {
            DoingTacts = false;
            tm.setQ("q0");
        } else if (!q.empty()) {
            tm.setQ(q);
        }
    }
    is_do_tact = false;

}


int main() {

    tm.setQ("q0");

    sf::Font font;
    font.loadFromFile("3270NerdFontMono-Regular.ttf");

    Screen::GetInstance()->Init();
    sf::RenderWindow* wnd = Screen::GetInstance()->window;

    TextBox enter_aph;
    TextBox spesh_ent;

    data[0][0] = "ld";
    for (int i = 1; i < data.size(); ++i) {
        data[i][0] = "q" + std::to_string(i - 1);
    }

    table.SetData(data);

    Button btn1, special_ch;
    Button pause, play, spid, slow, exit, doOneTakt;

    while (wnd->isOpen()) {
        sf::Event event{};
        while (wnd->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                wnd->close();
            }
            if (event.type == sf::Event::Resized) {

                sf::Vector2u windowSize = sf::Vector2u(event.size.width, event.size.height);
                wnd->setView(sf::View(sf::Vector2f((float) windowSize.x / 2.f, (float) windowSize.y / 2.f),
                                      sf::Vector2f(windowSize)));

                float shift = windowSize.x / 100;

                tm.Create(sf::Vector2f({(float) windowSize.x * (float) 0.01 + shift, (float) windowSize.y * (float) 0.15 - shift}),
                          sf::Vector2f({(float) windowSize.x * (float) 0.98 - 2 * shift,(float) windowSize.y * (float) 0.12 - shift}),
                          sf::Vector2f(100, 50), 2);

                table.Create(sf::Vector2f({(float) windowSize.x * (float) 0.65, (float) windowSize.y * (float) 0.6}),
                             sf::Vector2f({(float) windowSize.x * (float) 0.35 - shift,
                                           (float) windowSize.y * (float) 0.4 - shift}), sf::Color(58, 183, 149),
                             sf::Color(152, 193, 217), 10, 20, sf::Vector2f({150, 50}));


                btn1.Create(sf::Vector2f({(float) windowSize.x * (float) 0.1, (float) windowSize.y * (float) 0.1}),
                            sf::Vector2f({(float) windowSize.x * (float) 0.2 + 2 * shift,
                                          (float) windowSize.y * (float) 0.4 - shift}),
                            sf::Color(141, 159, 135), "Ok", font, 20);

                enter_aph.Create(sf::Vector2f({(float) windowSize.x * (float) 0.2, (float) windowSize.y * (float) 0.1}),
                                 sf::Vector2f({shift, (float) windowSize.y * (float) 0.4 - shift}),
                                 sf::Color(205, 198, 165), font, "Alphabet:", 20);

                spesh_ent.Create(sf::Vector2f({(float) windowSize.x * (float) 0.2, (float) windowSize.y * (float) 0.1}),
                                 sf::Vector2f({shift, (float) windowSize.y * (float) 0.5}),
                                 sf::Color(205, 198, 165), font, "Special chs:", 20);

                special_ch.Create(
                        sf::Vector2f({(float) windowSize.x * (float) 0.1, (float) windowSize.y * (float) 0.1}),
                        sf::Vector2f(
                                {(float) windowSize.x * (float) 0.2 + 2 * shift, (float) windowSize.y * (float) 0.5}),
                        sf::Color(141, 159, 135), "Ok", font, 20);

                play.Create(sf::Vector2f({(float) windowSize.x * (float) 0.15, (float) windowSize.y * (float) 0.1}),
                            sf::Vector2f({shift, (float) windowSize.y * (float) 0.6 + shift}),
                            sf::Color::Green, ">", font, 20);

                pause.Create(sf::Vector2f({(float) windowSize.x * (float) 0.15, (float) windowSize.y * (float) 0.1}),
                             sf::Vector2f({(float) windowSize.x * (float) 0.15 + 2 * shift,
                                           (float) windowSize.y * (float) 0.6 + shift}),
                             sf::Color::Green, "||", font, 20);

                slow.Create(sf::Vector2f({(float) windowSize.x * (float) 0.15, (float) windowSize.y * (float) 0.1}),
                            sf::Vector2f({shift, (float) windowSize.y * (float) 0.7 + 2 * shift}),
                            sf::Color::Green, "<<", font, 20);

                spid.Create(sf::Vector2f({(float) windowSize.x * (float) 0.15, (float) windowSize.y * (float) 0.1}),
                            sf::Vector2f({(float) windowSize.x * (float) 0.15 + 2 * shift,
                                          (float) windowSize.y * (float) 0.7 + 2 * shift}),
                            sf::Color::Green, ">>", font, 20);

                exit.Create(sf::Vector2f({(float) windowSize.x * (float) 0.15, (float) windowSize.y * (float) 0.1}),
                            sf::Vector2f({shift, (float) windowSize.y * (float) 0.8 + 3 * shift}),
                            sf::Color::Green, "X", font, 20);


                doOneTakt.Create(sf::Vector2f({(float) windowSize.x * (float) 0.15, (float) windowSize.y * (float) 0.1}),
                            sf::Vector2f({(float) windowSize.x * (float) 0.15 + 2 * shift,
                                          (float) windowSize.y * (float) 0.8 + 3 * shift}),
                            sf::Color::Green, "DO 1", font, 20);
            }


            if (event.type == sf::Event::MouseWheelScrolled && table.isMouseOver(*wnd)) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    table.Scroll(std::make_pair((int) event.mouseWheelScroll.delta, 0));
                } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                    table.Scroll(std::make_pair(0, (int) event.mouseWheelScroll.delta));
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                DoingTacts = false;
                tm.is_step = true;
                from = -1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                DoingTacts = false;
                tm.is_step = true;
                from = 1;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                enter_aph.setActive(enter_aph.isMousOver(*wnd));
                spesh_ent.setActive(spesh_ent.isMousOver(*wnd));
            }

            if (btn1.isMouseOver(*wnd)) {
                SetAlph(enter_aph.get_text());
            }
            if (special_ch.isMouseOver(*wnd)) {
                SetSp(spesh_ent.get_text());
            }
            if (spid.isMouseOver(*wnd)) {
                speed = speed - 1;
                if (speed < 1) {
                    speed = 1;
                    dist++;
                    dist = std::min(100, dist);
                    while (100 % dist != 0) {
                        ++dist;
                    }
                }
                cnt = 0;
            }
            if (slow.isMouseOver(*wnd)) {
                if (dist != 1) {
                    dist--;
                    while (100 % dist != 0) {
                        --dist;
                    }
                } else {
                    speed = std::min(100, speed + 1);
                }
                cnt = 0;
            }
            if (doOneTakt.isMouseOver(*wnd)) {
                if (!is_bad()) {
                    is_do_tact = true;
                }
            }
            if (play.isMouseOver(*wnd)) {
                table.ToCell(-1, -1, sf::Color(48, 99, 142));
                if (!is_bad()) {
                    DoingTacts = true;
                }
            }
            if (pause.isMouseOver(*wnd)) {
                DoingTacts = false;
            }
            if (exit.isMouseOver(*wnd)) {
                DoingTacts = false;
                tm.clearData();
                tm.setQ("q0");
                table.ToCell(-1, -1, sf::Color(48, 99, 142));
            }
        }

        DoTact();

        if (DoingTacts) {
            is_do_tact = true;
        }

        enter_aph.enter(event, *wnd);
        spesh_ent.enter(event, *wnd);

        wnd->clear(sf::Color::White);

        table.Draw(*wnd, font, event);

        btn1.Draw(*wnd, font);

        enter_aph.Draw(*wnd);

        doOneTakt.Draw(*wnd, font);

        play.Draw(*wnd, font);

        pause.Draw(*wnd, font);

        slow.Draw(*wnd, font);

        spid.Draw(*wnd, font);

        exit.Draw(*wnd, font);

        spesh_ent.Draw(*wnd);

        special_ch.Draw(*wnd, font);
        special_ch.isMouseOver(*wnd);

        table.EnterSpawn(*wnd);

        if (cnt == speed) {
            cnt = 0;
            tm.Step(dist * from);
        }

        tm.Draw(*wnd, font, event);
        wnd->display();
        ++cnt;
    }

    return 0;
}