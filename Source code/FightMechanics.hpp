#pragma once
#pragma once

#include "gameObject.hpp"
#include "character.hpp"
#include "textObject.hpp"
#include "button.hpp"

#include <string>

class FightMechanics : public GameObject {
private:
    Character& player;
    Character& enemy;
    TextObject& message;

    Button& attackButton;
    Button& healButton;
    Button& prepareButton;
    Button& continueButton;

    int score;
    bool isPrepared;

public:
    FightMechanics(Character& player, Character& enemy, TextObject& message, 
        Button& attackButton, Button& healButton, Button& prepareButton, Button& continueButton);

    ~FightMechanics();

    enum class State { PLAYERTURN, WAITING, ENEMYTURN, VICTORY, GAMEOVER };
    State state;
    int counter;

    void update() override;
    void render(sf::RenderWindow& window) override;

    void handleState();
    void setState(State state);

    void handlePlayerTurn();
    void handleWaiting();
    void handleEnemyTurn();
    void handleVictoryState();
    void handleGameOverState();

    void attack();
    void heal();
    void prepare();
    
    void enemyAttack();
    void enemyHeal();
    void enemyDoNothing();

    void continueGame();
    void resetBattle();
    void resetGame();

    int getScore() const;
};


