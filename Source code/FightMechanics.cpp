#include "FightMechanics.hpp"
#include <iostream>

FightMechanics::FightMechanics(Character& player, Character& enemy, TextObject& message, 
	Button& attackButton, Button& healButton, Button& prepareButton, Button& continueButton):
	GameObject(""), player(player), enemy(enemy), message(message), attackButton(attackButton),
	healButton(healButton), prepareButton(prepareButton), continueButton(continueButton) {

	score = 0;
	counter = 0;
	isPrepared = false;
	state = State::PLAYERTURN;
	handleState();
}

FightMechanics::~FightMechanics() { }


void FightMechanics::update() {

}

void FightMechanics::render(sf::RenderWindow& window) {

}


//-------------------------------------------------------------------------------------
//                        STATES STUFF
//-------------------------------------------------------------------------------------

void FightMechanics::handleState() {
	switch (this->state) {
	case State::PLAYERTURN:
		std::cout << "State is PLAYERTURN\n";
		handlePlayerTurn();
		break;
	case State::WAITING:
		std::cout << "State is WAITING\n";
		handleWaiting();
		break;
	case State::ENEMYTURN:
		std::cout << "State is ENEMYTURN\n";
		handleEnemyTurn();
		break;
	case State::VICTORY:
		std::cout << "State is VICTORY\n";
		handleVictoryState();
		break;
	case State::GAMEOVER:
		std::cout << "State is GAMEOVER\n";
		handleGameOverState();
		break;
	}
}

void FightMechanics::setState(const State state) {
	this->state = state;
	handleState();
}

void FightMechanics::handlePlayerTurn() {
	attackButton.isActive = true;
	healButton.isActive = true;
	prepareButton.isActive = true;
	continueButton.isActive = false;
}

void FightMechanics::handleWaiting() {
	attackButton.isActive = false;
	healButton.isActive = false;
	prepareButton.isActive = false;
	continueButton.isActive = true;
}

void FightMechanics::handleEnemyTurn() {
	if (state == State::ENEMYTURN) {
		int random = rand() % 6 + 1;
		switch (random) {
		case 1:
			enemyAttack();
			break;
		case 2:
			enemyAttack();
			break;
		case 3:
			enemyAttack();
			break;
		case 4:
			enemyHeal();
			break;
		case 5:
			enemyHeal();
			break;
		case 6:
			enemyDoNothing();
			break;
		}

		if (player.dead()) {
			setState(State::GAMEOVER);
		}
		else setState(State::PLAYERTURN);
	}
}

void FightMechanics::handleVictoryState() {
	message.setText("Victory! You killed " + enemy.getName() + ".");

	attackButton.isActive = false;
	healButton.isActive = false;
	prepareButton.isActive = false;
	continueButton.isActive = true;
}

void FightMechanics::handleGameOverState() {
	score = counter * 20;
	message.setText("Game Over. You died. Score: " + std::to_string(score));

	attackButton.isActive = false;
	healButton.isActive = false;
	prepareButton.isActive = false;
	continueButton.isActive = true;

	continueButton.setText("Quit");
}


//-------------------------------------------------------------------------------------
//                        ACTION METHODS
//-------------------------------------------------------------------------------------

void FightMechanics::attack() {
	int damage;

	if (isPrepared) {
		damage = 3;
		isPrepared = false;
	}
	else damage = 2;

	enemy.setHP(enemy.getHP() - damage);
	enemy.update();

	if (enemy.dead()) {
		setState(State::VICTORY);
	}
	else {
		message.setText("You attacked: " + enemy.getName() + " lost " + std::to_string(damage) + " health points.");
		setState(State::WAITING);
	}
}

void FightMechanics::heal() {
	if (isPrepared) isPrepared = false;

	player.setHP(player.getHP() + 1);
	player.update();
	message.setText("You gained 1 health point.");

	setState(State::WAITING);
}

void FightMechanics::prepare() {
	isPrepared = true;
	message.setText("You prepared.");

	setState(State::WAITING);
}

void FightMechanics::enemyAttack() {
	int damage;

	if (isPrepared) {
		damage = 1;
		isPrepared = false;
	}
	else damage = 2;

	player.setHP(player.getHP() - damage);
	player.update();

	message.setText(enemy.getName() + " attacked you, you lost "+std::to_string(damage)+" health points.");
}

void FightMechanics::enemyHeal() {
	enemy.setHP(enemy.getHP() + 1);
	enemy.update();

	message.setText(enemy.getName()+" gained 1 health point.");
}

void FightMechanics::enemyDoNothing() {
	message.setText(enemy.getName()+" did nothing.");
}


//-------------------------------------------------------------------------------------
//                        OTHER
//-------------------------------------------------------------------------------------

void FightMechanics::continueGame() {
	if (state == State::WAITING) {
		setState(State::ENEMYTURN);
	}
}

void FightMechanics::resetBattle() {
	setState(FightMechanics::State::PLAYERTURN);
	message.setText("Choose 'Attack', 'Prepare' or 'Heal'");
	continueButton.setText("Continue >");
}

void FightMechanics::resetGame() {
	counter = 0;
}

int FightMechanics::getScore() const {
	return this->score;
}



