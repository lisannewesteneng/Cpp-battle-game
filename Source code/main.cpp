#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>

#include "sceneHandler.hpp"
#include "scene.hpp"
#include "spriteObject.hpp"
#include "textObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "ranking.hpp"
#include "FightMechanics.hpp"

void setCharacter(Character& character, Character& player);

int main() {
 
    sf::Color lightGreyColor = sf::Color(129, 144, 165, 255);
    sf::Color darkGreen = sf::Color(41, 117, 55);
    sf::Color black = sf::Color::Black;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML with Scenes!", sf::Style::Close);
    SceneHandler handler;

    Scene mainMenu("mainMenu");
    Scene characterMenu("characterMenu");
    Scene fightScene("fightScene");

    handler.addScene(mainMenu);
    handler.addScene(characterMenu);
    handler.addScene(fightScene);

    Character player("player1", "Sprites\\head.png", 1);
    player.setPosition(250.0f, 100.0f);
    fightScene.addGameObject(player);

    //-------------------------------------------------------------------------------------
    //                           MAIN MENU
    //-------------------------------------------------------------------------------------

    
    TextObject mainText("mainText", "Main Menu");
    mainText.setPosition(sf::Vector2f(500.0f, 50.0f));
    mainText.setCharacterSize(40);
    mainText.setFillColor(lightGreyColor);

    Ranking ranking("ranking");
    ranking.setPosition(sf::Vector2f(200.0f, 400.0f));

    Button playButton("playButton", "PLAY", sf::Vector2f(220.0f, 60.0f), black);
    playButton.setPosition(sf::Vector2f(700.0f, 400.0f));
    playButton.setButtonAction([&handler]() {
        handler.stackScene("characterMenu");
        });
    
    Button eraseDataButton("eraseDataButton", "ERASE DATA", sf::Vector2f(220.0f, 60.0f), black);
    eraseDataButton.setPosition(sf::Vector2f(700.0f, 475.0f));
    eraseDataButton.setButtonAction([&ranking]() {
        ranking.eraseData();
        });

    Button quitButton("quitButton", "QUIT", sf::Vector2f(220.0f, 60.0f), black);
    quitButton.setPosition(sf::Vector2f(700.0f, 550.0f));
    quitButton.setButtonAction([&window]() {
        window.close();
        });

    mainMenu.addGameObject(mainText);
    mainMenu.addGameObject(ranking);
    mainMenu.addGameObject(playButton);
    mainMenu.addGameObject(eraseDataButton);
    mainMenu.addGameObject(quitButton);

    //-------------------------------------------------------------------------------------
    //                        CHARACTER MENU
    //-------------------------------------------------------------------------------------
    
    TextObject selectionText("selectionText", "Character Selection");
    selectionText.setPosition(sf::Vector2f(300.0f, 20.0f));
    selectionText.setCharacterSize(40);
    selectionText.setFillColor(lightGreyColor);

    Character character1("Graverobber", "Sprites\\GraveRobber.png", 6);
    character1.setPosition(sf::Vector2f(130.0f, 110.0f));

    Character character2("Woodcutter", "Sprites\\Woodcutter.png", 8);
    character2.setPosition(sf::Vector2f(530.0f, 110.0f));
    
    Character character3("Steam Man", "Sprites\\SteamMan.png", 10);
    character3.setPosition(sf::Vector2f(930.0f, 110.0f));
    
    Button chooseButton1("chooseButton1", "Choose", sf::Vector2f(220.0f, 60.0f), black);
    chooseButton1.setPosition(sf::Vector2f(100.0f, 400.0f));
    chooseButton1.setButtonAction([&handler, &player, &character1]() {
        setCharacter(character1, player);
        handler.stackScene("fightScene");
        });

    Button chooseButton2("chooseButton2", "Choose", sf::Vector2f(220.0f, 60.0f), black);
    chooseButton2.setPosition(sf::Vector2f(500.0f, 400.0f));
    chooseButton2.setButtonAction([&handler, &player, &character2]() {
        setCharacter(character2, player);
        handler.stackScene("fightScene");
        });

    Button chooseButton3("chooseButton3", "Choose", sf::Vector2f(220.0f, 60.0f), black);
    chooseButton3.setPosition(sf::Vector2f(900.0f, 400.0f));
    chooseButton3.setButtonAction([&handler, &player, &character3]() {
        setCharacter(character3, player);
        handler.stackScene("fightScene");
        });

    Button returnToMain("returnToMain", "< Return", sf::Vector2f(220.0f, 60.0f), black);
    returnToMain.setPosition(sf::Vector2f(500.0f, 600.0f));
    returnToMain.setButtonAction([&handler]() {
        handler.popScene();
        });

    characterMenu.addGameObject(selectionText);
    characterMenu.addGameObject(character1);
    characterMenu.addGameObject(character2);
    characterMenu.addGameObject(character3);
    characterMenu.addGameObject(chooseButton1);
    characterMenu.addGameObject(chooseButton2);
    characterMenu.addGameObject(chooseButton3);
    characterMenu.addGameObject(returnToMain);

    //-------------------------------------------------------------------------------------
    //                        FIGHT SCENE
    //-------------------------------------------------------------------------------------

    Character enemy1("Snake", "Sprites\\Snake.png", 6, true);
    Character enemy2("Vulture", "Sprites\\Vulture.png", 10, true);
    Character enemy3("Hyena", "Sprites\\Hyena.png", 15, true);

    Character enemy("Enemy", "Sprites\\head.png", 10, true);
    enemy.setPosition(sf::Vector2f(650.0f, 100.0f));

    //set enemy1 as the first enemy
    setCharacter(enemy1, enemy);

    TextObject fightMessage("fightMessage", "Choose 'Attack', 'Prepare' or 'Heal'");
    fightMessage.setPosition(sf::Vector2f(450.0f, 500.0f));
    fightMessage.setCharacterSize(20);
    fightMessage.setFillColor(lightGreyColor);

    Button attackButton("attackButton", "Attack", sf::Vector2f(220.0f, 60.0f), black);
    Button prepareButton("prepareButton", "Prepare", sf::Vector2f(220.0f, 60.0f), black);
    Button healButton("healButton", "Heal", sf::Vector2f(220.0f, 60.0f), black);
    Button continueButton("continueButton", "Continue >", sf::Vector2f(220.0f, 60.0f), black, false);

    FightMechanics fight(player, enemy, fightMessage, attackButton, healButton, prepareButton, continueButton);

    attackButton.setPosition(sf::Vector2f(100.0f, 450.0f));
    attackButton.setButtonAction([&fight]() {
        fight.attack();
        });
    
    prepareButton.setPosition(sf::Vector2f(100.0f, 520.0f));
    prepareButton.setButtonAction([&fight]() {
        fight.prepare();
        });

    healButton.setPosition(sf::Vector2f(100.0f, 590.0f));
    healButton.setButtonAction([&fight]() {
        fight.heal();
        });
    
    continueButton.setPosition(sf::Vector2f(900.0f, 600.0f));
    continueButton.setButtonAction([&fight, &fightMessage, &player, &enemy, &enemy1, &enemy2, &enemy3, &ranking, &handler]() {

        if (fight.state == FightMechanics::State::GAMEOVER) {
            ranking.insertPair(std::make_pair(player.getName(), fight.getScore()));
            handler.popScene();
            handler.popScene();
            fight.resetBattle();
            fight.resetGame();
            setCharacter(enemy1, enemy);
        }
        else if (fight.state == FightMechanics::State::VICTORY) {
            fight.counter++;
            if (fight.counter == 1) setCharacter(enemy2, enemy);
            if (fight.counter == 2) setCharacter(enemy3, enemy);
            fight.resetBattle();
        }
        else {
            fight.continueGame();
        }
        
        });

    Button returnToSelect("returnToSelect", "< Return", sf::Vector2f(220.0f, 60.0f), black);
    returnToSelect.setPosition(sf::Vector2f(50.0f, 60.0f));
    returnToSelect.setButtonAction([&fight, &enemy, &enemy1, &fightMessage, &handler]() {
        handler.popScene();
        fight.resetBattle();
        fight.resetGame();
        setCharacter(enemy1, enemy);
        });

    fightScene.addGameObject(enemy);
    fightScene.addGameObject(fightMessage);
    fightScene.addGameObject(fight);
    fightScene.addGameObject(attackButton);
    fightScene.addGameObject(prepareButton);
    fightScene.addGameObject(healButton);
    fightScene.addGameObject(continueButton);
    fightScene.addGameObject(returnToSelect);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                handler.getCurrentScene().handleEvent(event, window);
            }
            
        }
        window.clear();
        handler.update();
        handler.render(window);
        window.display();
    }

    return 0;
}

void setCharacter(Character& character, Character& player) {
    player.setName(character.getName());
    player.setHP(character.getHP());
    player.setSpriteFile(character.getSpriteFile());
    player.update();
}

