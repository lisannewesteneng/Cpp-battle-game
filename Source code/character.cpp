#include "character.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>

Character::Character(std::string name, std::string spriteFile, int hp, bool enemy) :
    name(name), spriteFile(spriteFile), hp(hp), enemy(enemy), GameObject(name)
{ 
    update();
}

Character::~Character() { }

void Character::update() {
    this->texture.loadFromFile(this->spriteFile);
    this->sprite.setTexture(this->texture);
    this->sprite.setScale(4, 4);
    this->sprite.setPosition(position);

    sf::FloatRect rect = this->sprite.getGlobalBounds();

    this->nameText.setString(this->name);
    if (enemy) {
        this->nameText.setPosition(this->position.x + 90, this->position.y + rect.height);
        this->hpText.setPosition(this->position.x + 90, this->position.y + rect.height + 40);
    }
    else {
        this->nameText.setPosition(this->position.x + 20, this->position.y + rect.height);
        this->hpText.setPosition(this->position.x + 20, this->position.y + rect.height + 40);
    }

    this->nameText.setCharacterSize(20);
    this->nameText.setFillColor(sf::Color::White);

    this->hpText.setString("HP:  " + std::to_string(hp));

    this->hpText.setCharacterSize(18);
    this->hpText.setFillColor(sf::Color::White);
}

void Character::render(sf::RenderWindow& window) {

    window.draw(this->sprite);
    window.draw(this->nameText);
    window.draw(this->hpText);
}

void Character::setPosition(float x, float y) {
    this->position.x = x;
    this->position.y = y;

    sf::FloatRect rect = this->sprite.getGlobalBounds();

    this->sprite.setPosition(position);
    this->nameText.setPosition(this->position.x, this->position.y + rect.height);
    this->hpText.setPosition(this->position.x, this->position.y + rect.height + 30);
}

void Character::setPosition(sf::Vector2f position) {
    this->position = position;

    sf::FloatRect rect = this->sprite.getGlobalBounds();

    this->sprite.setPosition(this->position);
    this->nameText.setPosition(this->position.x, this->position.y + rect.height);
    this->hpText.setPosition(this->position.x, this->position.y + rect.height + 30);
}

int Character::getHP() const {
    return this->hp;
}

void Character::setHP(int hp) {
    this->hp = hp;
    if (this->hp < 0) this->hp = 0;
}

std::string Character::getName() const {
    return this->name;
}

void Character::setName(std::string name) {
    this->name = name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::setSpriteFile(std::string spriteFile) {
    this->spriteFile = spriteFile;
}

bool Character::dead() {
    if (this->hp < 1) {
        return true;
    }
    else return false;
}



