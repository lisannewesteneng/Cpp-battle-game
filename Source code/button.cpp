#include "button.hpp"

#include <SFML/Window/Event.hpp>

Button::Button(std::string identifier, std::string buttonText, sf::Vector2f size, sf::Color color, bool isActive, sf::Color hoverColor) :
    GameObject(identifier), buttonText(buttonText), color(color), hoverColor(hoverColor), isActive(isActive)
{
    this->shape.setSize(size);
    this->shape.setFillColor(color);
    this->shape.setOutlineColor(sf::Color(41, 117, 55));
    this->shape.setOutlineThickness(5);

    this->text.setString(buttonText);
    this->text.setCharacterSize(26);
    this->text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = this->text.getLocalBounds();
    this->text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    this->setPosition(sf::Vector2f(0.0f, 0.0f));
}

Button::~Button() { }

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f size = shape.getSize();
    sf::Vector2f position = shape.getPosition();

    if (isActive) {

        setAlpha(255);

        //if mouse is on button
        if (mousePosition.x >= position.x && mousePosition.x <= position.x + size.x &&
            mousePosition.y >= position.y && mousePosition.y <= position.y + size.y) {

            //if clicked
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Button::Left) {

                this->onClick();
            }

            //color is hoverColor
            setColor(hoverColor);
        }
        else setColor(color);
    }
    
    if (!isActive) {
        setColor(color);
        setAlpha(50);
    }
}

void Button::update() { }

void Button::render(sf::RenderWindow& window) {
    window.draw(this->shape);
    window.draw(this->text);
}

void Button::setCharacterSize(const int size) {
    this->text.setCharacterSize(size);
}

void Button::setPosition(const sf::Vector2f position) {
    this->shape.setPosition(position);
    sf::Vector2f size = this->shape.getSize();
    sf::Vector2f centerButton(position.x + (size.x / 2.0f), position.y + (size.y / 2.0f));
    this->text.setPosition(centerButton.x, centerButton.y);
}

void Button::setColor(const sf::Color color) {
    this->shape.setFillColor(color);
}

void Button::onClick() {
    this->action();
}

void Button::setButtonAction(const std::function<void()> action) {
    this->action = action;
}

void Button::setAlpha(const int alpha) {
    
    if (alpha >= 0 && alpha <= 255) {
        sf::Color color = this->shape.getFillColor();
        color.a = alpha;
        this->shape.setFillColor(color);

        color = sf::Color::White;
        color.a = alpha;
        this->text.setFillColor(color);
    }
}

void Button::setText(const std::string text) {
    this->text.setString(text);
}