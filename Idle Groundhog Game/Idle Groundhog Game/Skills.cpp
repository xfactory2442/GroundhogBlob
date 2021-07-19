#include "Skills.h"
#include <string>
#include "GeneralFunctions.h"

using namespace std;

Skills::Skills(string name_, int level_, sf::Font* font, sf::Vector2f position) {
	level = level_;
	name = name_;
	
	//Initalsie the text for the Skill.
	nameText.setString(name);
	nameText.setFont(*font);
	nameText.setCharacterSize(17);
	nameText.setPosition(position - sf::Vector2f(10 * nameText.getString().getSize(), 0));
	nameText.setFillColor(sf::Color::White);

	levelText.setFont(*font);
	levelText.setCharacterSize(15);
	levelText.setPosition(position.x, position.y + 20);
	levelText.setFillColor(sf::Color::White);

	defaultPosition = levelText.getPosition();

	FormatText();
}

void Skills::AddLevels(int i)
{
	level += i;
	FormatText();
}

int Skills::GetLevel()
{
	return level;
}

void Skills::SetLevel(int i)
{
	level = i;
	FormatText();
}

string Skills::GetName()
{
	return name;
}

void Skills::RenderSkill(sf::RenderWindow* window)
{
	window->draw(nameText);
	window->draw(levelText);
}

int Skills::Reset()
{
	int res = level;
	level = 0;
	FormatText();
	return res;
}

void Skills::FormatText()
{
	//Format the text after adding experience.
	levelText.setString("Level: " + GeneralFunctions::FormatNumber(level));
	levelText.setPosition(defaultPosition - sf::Vector2f(10 * levelText.getString().getSize(), 0));
}
