#include "ranking.hpp"
#include <fstream>
#include <iostream>

Ranking::Ranking(std::string identifier) : GameObject(identifier) { 
	readFile();
}

Ranking::~Ranking() { }

void Ranking::update() { }

void Ranking::render(sf::RenderWindow& window) {

	std::string string;
	bitmapText text;

	text.setString("High Scores: ");
	text.setPosition(position.x, position.y);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color(132, 146, 166, 255));
	window.draw(text);

	text.setCharacterSize(20);
	text.setFillColor(sf::Color(129, 144, 165, 255));

	for (unsigned int i = 0; i < highScores.size(); i++) {

		text.setString(std::to_string(i + 1) + ". " + highScores[i].first);
		text.setPosition(position.x, position.y + (i + 1) * 30);
		window.draw(text);

		text.setString(std::to_string(highScores[i].second));
		text.setPosition(position.x + 250, position.y + (i + 1) * 30);
		window.draw(text);
	}
}

std::string Ranking::getName(int index) const {
	return highScores[index - 1].first;
}

int Ranking::getScore(int index) const {
	return highScores[index - 1].second;
}

void Ranking::insertPair(const NameByScore pair) {
	int position = getPosition(pair.second);

	if (position >= 0 && position < 5) {

		std::vector<NameByScore>::iterator it = highScores.begin();
		highScores.insert(it + getPosition(pair.second), pair);

		//delete last element, lowest score
		while (highScores.size() > 5) {
			highScores.pop_back();
		}
		writeFile();
	}

}

void Ranking::setPosition(const sf::Vector2f position) {
	this->position = position;
}

void Ranking::readFile() {

	std::ifstream fileRead("highScores.cmgt");
	if (!fileRead.fail()) {

		std::cout << "reading file\n";

		std::string line;

		for (int i = 0; i < 5; i++) {

			std::getline(fileRead, line);
			std::string name = line;

			std::getline(fileRead, line);
			int score = std::stoi(line);

			highScores.push_back(NameByScore(name, score));
		}
		fileRead.close();
	}
	else {
		std::cout << "Could not open file\n";
		writeNewFile();
	}
}

void Ranking::writeFile() const {
	std::cout << "Writing file\n";

	std::ofstream fileRead("highScores.cmgt");
	if (!fileRead.fail()) {

		for (unsigned int i = 0; i < highScores.size(); i++) {

			fileRead << highScores[i].first << "\n";
			fileRead << std::to_string(highScores[i].second) << "\n";
		}
		fileRead.close();
	}
	else std::cout << "writeFile fail\n";
}

void Ranking::writeNewFile() {
	std::cout << "Writing new file\n";

	std::ofstream fileRead("highScores.cmgt");
	if (!fileRead.fail()) {

		for (int i = 0; i < 5; i++) {

			fileRead << "empty" << "\n";
			fileRead << "0" << "\n";
		}
		fileRead.close();
	}
	else std::cout << "writeNewFile fail\n";

	readFile();
}

void Ranking::eraseData() {
	for (unsigned int i = 0; i < highScores.size(); i++) {

		highScores[i].first = "empty";
		highScores[i].second = 0;
	}

	writeFile();
}



int Ranking::getPosition(int score) const {
	std::vector<NameByScore>::const_iterator it = highScores.begin();
	int pos = -1;

	for (unsigned int i = 0; i < highScores.size(); i++) {

		if (score > highScores[i].second) {
			pos = i;
			break;
		}
	}

	return pos;
}

