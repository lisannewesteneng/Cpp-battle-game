#include "textObject.hpp"

TextObject::TextObject(std::string identifier, std::string textStr) : GameObject(identifier), textStr(textStr) {
    this->text.setString(this->textStr);
    this->text.setPosition(this->position.x, this->position.y);
    this->text.setCharacterSize(12);
    this->text.setFillColor(sf::Color::Black);
}

TextObject::~TextObject() { }

void TextObject::update() { }

void TextObject::render(sf::RenderWindow& window) {
    window.draw(this->text);
}

std::string TextObject::getTextStr() const {
    return this->textStr;
}

void TextObject::setText(const std::string textStr) {
    this->textStr = textStr;
    this->text.setString(this->textStr);
}

void TextObject::setCharacterSize(const int size) {
    this->text.setCharacterSize(size);
}

void TextObject::setFillColor(const sf::Color color) {
    this->text.setFillColor(color);
}

void TextObject::setPosition(const sf::Vector2f position) {
    this->text.setPosition(position.x, position.y);
}
