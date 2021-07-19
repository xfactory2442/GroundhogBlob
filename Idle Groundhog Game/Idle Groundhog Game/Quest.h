#pragma once
#include <SFML/Graphics.hpp>
#include "Skills.h"
#include "Action.h"
class Quest : public sf::RectangleShape
{
public:
	~Quest();
	void Init(string name_, string description_, vector<Skills*> skills_,
		vector<int> skillsLevel_, vector<Action*> actions_, vector<int> timesFilled_,
		vector<int> quests, sf::Font* font, int index_);
	bool IsComplete();
	vector<int> GetQuestsOnComplete();
	void ResetPosition(sf::Vector2f position);
	bool Collision(sf::Vector2f mouse_position);
	void RenderQuestText(sf::RenderWindow* window);

	int GetIndex();
private:
	int index = 0;

	bool flip = false;
	sf::FloatRect hitbox;

	//Flip side 1.
	sf::Text name;
	sf::Text description;

	//Flip side 2.
	vector<sf::Text> skillText;
	vector<Skills*> skills;
	vector<int> skillsLevel;

	vector<sf::Text> actionText;
	vector<Action*> actions;
	vector<int> timesFilled;

	vector<int> questsOnComplete;

	int maxLineSize = 50;
};

