#pragma once

#include "gameObject.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

#include "scene.hpp"
#include "bitmapText.hpp"

// typedef std::function<void()> buttonAction;

class Button : public GameObject {

private:
    bitmapText text;
    sf::RectangleShape shape;
    std::string buttonText;
    sf::Color color;
    sf::Color hoverColor;

    std::function<void()> action;

public:
    Button(std::string identifier, std::string buttonText,
        sf::Vector2f size, sf::Color color, bool isActive = true, sf::Color hoverColor=sf::Color(17, 46, 22));
    ~Button();

    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    virtual void onClick();

    void update() override;
    void render(sf::RenderWindow& window) override;

    void setButtonAction(const std::function<void()> action);
    void setCharacterSize(const int size);
    void setPosition(const sf::Vector2f position);
    void setColor(const sf::Color color);
    void setAlpha(const int alpha);
    void setText(const std::string text);

    bool isActive;
};
