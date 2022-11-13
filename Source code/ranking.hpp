#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "gameObject.hpp"
#include "bitmapText.hpp"

class Ranking : public GameObject {
private:
	sf::Vector2f position;
	
	//using a vector of pairs instead of a map
	//because i want to be able to access the players and scores by index
	std::vector<std::pair<std::string, int>> highScores;

	int getPosition(int score) const;

public:
	typedef std::pair<std::string, int> NameByScore;

	Ranking(std::string identifier);
	~Ranking();

	void update() override;
	void render(sf::RenderWindow& window) override;

	std::string getName(int index) const;
	int getScore(int index) const;

	void insertPair(const NameByScore pair);
	void setPosition(const sf::Vector2f position);

	void readFile();
	void writeFile() const;
	void writeNewFile();

	void eraseData();
};