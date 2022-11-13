#pragma once

#include "gameObject.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "bitmapText.hpp"

#include <string>

class Character : public GameObject {
private:
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;

    bitmapText nameText;
    bitmapText hpText;

    std::string name;
    std::string spriteFile;

    int hp;
    bool enemy;

public:
    Character(std::string name, std::string spriteFile,
        int hp, bool enemy=false);

    ~Character();

    void update() override;
    void render(sf::RenderWindow& window) override;

    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);

    int getHP() const;
    void setHP(int hp);

    std::string getName() const;
    void setName(std::string name);

    std::string getSpriteFile() const;
    void setSpriteFile(std::string spriteFile);

    bool dead();
};