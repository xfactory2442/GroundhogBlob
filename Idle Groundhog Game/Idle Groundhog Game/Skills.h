#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Skills
{
public:
	Skills(string name_, int level, sf::Font* font,
		sf::Vector2f position);
	void AddLevels(int i);
	int GetLevel();
	void SetLevel(int i);
	string GetName();
	void RenderSkill(sf::RenderWindow* window);

	int Reset();
private:
	void FormatText();

	string name;
	int level = 0;
	sf::Vector2f defaultPosition;
	
	sf::Text levelText;
	sf::Text nameText;
};

