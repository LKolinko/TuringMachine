#include "TextBox.h"
void TextBox::Create(sf::Vector2f size, sf::Vector2f pos, sf::Color color, sf::Font &font, std::string str_title,
                     float radius) {
    back.Create(color, size, pos, radius);
    TextBoxWidth = size.x;
    TextBoxHeight = size.y;

    if (str_title.empty()) {
        is_title = false;
    } else {
        is_title = true;
    }

    title.setString(str_title);
    title.setFillColor(sf::Color::Black);
    title.setCharacterSize(back.vertic.getLocalBounds().height / 3.5);
    title.setFont(font);
    title.setPosition({ pos.x + 5, pos.y });

    text_.setFont(font);
    float xPos = pos.x + 5;
    float yPos = (pos.y + TextBoxHeight / 2.7);
    text_.setPosition(xPos, yPos);
    if (is_title) {
        text_.setCharacterSize(back.vertic.getLocalBounds().height / 3);
    } else {
        text_.setCharacterSize(back.vertic.getLocalBounds().height / 2);
    }
    text_.setFillColor(sf::Color::Black);

    position = pos;
    ft = radius;
}
void TextBox::Draw(sf::RenderWindow& wnd) {
    sf::RenderTexture textbox;

    textbox.create(static_cast<unsigned int>(back.horisont.getLocalBounds().width - ft / 2 - 5),
                 static_cast<unsigned int>(back.vertic.getLocalBounds().height / (is_title ? 2.5 : 1) - (is_title ? 0 : ft)));
    textbox.clear(back.getColor());

    back.Draw(wnd);

    wnd.draw(title);

    text_.setPosition(start, 0);
    textbox.draw(text_);


    textbox.display();
    sf::Sprite sprite(textbox.getTexture());
    if (is_title) {
        sprite.setPosition(position.x + 5, position.y + TextBoxHeight / 2.7 );
    } else {
        sprite.setPosition(position.x + ft / 2, position.y + ft / 2);

    }
    wnd.draw(sprite);
}
void TextBox::setActive(bool Active) {
    if (Active) {
        back.SetColor(sf::Color(233, 198, 165));
    } else {
        back.SetColor(sf::Color(205, 198, 165));
        start = 0;
    }
    is_active = Active;
}

void TextBox::enter(sf::Event& event, sf::RenderWindow& wnd) {
    if (is_active) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel
        && text_.getLocalBounds().width > back.horisont.getLocalBounds().width - ft / 2
        && isMousOver(wnd)) {
            start = std::max((int)(back.horisont.getLocalBounds().width -
                    text_.getLocalBounds().width - text_.getCharacterSize()),
                             start + (int)event.mouseWheelScroll.delta);
            start = std::min(0, start);
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.key.code == 8 || event.key.code == 127) {
                if (!str_.empty()) {
                    str_.pop_back();
                }
            } else {
                char c[] = {event.key.code};
                str_.push_back(c[0]);
            }
        }
        text_.setString(str_);
    }
}
std::string TextBox::get_text() {
    return str_;
}
bool TextBox::isMousOver(sf::RenderWindow& wnd) {
    int mouseX = sf::Mouse::getPosition(wnd).x;
    int mouseY = sf::Mouse::getPosition(wnd).y;
    int btnPosX = position.x;
    int btnPosY = position.y;
    int btnxPosWidth = position.x + TextBoxWidth;
    int btnyPosHeight = position.y + TextBoxHeight;
    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

void TextBox::Draw(sf::RenderTexture &wnd) {
    sf::RenderTexture textbox;

    textbox.create(static_cast<unsigned int>(back.horisont.getLocalBounds().width - ft / 2 - 5),
                   static_cast<unsigned int>(back.vertic.getLocalBounds().height / (is_title ? 2.5 : 1) - (is_title ? 0 : ft)));
    textbox.clear(back.getColor());

    back.Draw(wnd);

    wnd.draw(title);

    text_.setPosition(start, 0);
    textbox.draw(text_);


    textbox.display();
    sf::Sprite sprite(textbox.getTexture());
    if (is_title) {
        sprite.setPosition(position.x + 5, position.y + TextBoxHeight / 2.7 );
    } else {
        sprite.setPosition(position.x + ft / 2, position.y + ft / 2);

    }
    wnd.draw(sprite);
}

void TextBox::enter(sf::Event &event, sf::RenderTexture &wnd) {
    if (is_active) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel
            && text_.getLocalBounds().width > back.horisont.getLocalBounds().width - ft / 2) {
            start = std::max((int)(back.horisont.getLocalBounds().width -
                                   text_.getLocalBounds().width - text_.getCharacterSize()),
                             start + (int)event.mouseWheelScroll.delta);
            start = std::min(0, start);
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.key.code == 8 || event.key.code == 127) {
                if (!str_.empty()) {
                    str_.pop_back();
                }
            } else {
                char c[] = {event.key.code};
                str_.push_back(c[0]);
            }
        }
        text_.setString(str_);
    }
}

void TextBox::Clear() {
    str_.clear();
    text_.setString(str_);
}

