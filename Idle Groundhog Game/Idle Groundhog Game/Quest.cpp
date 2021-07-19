#include "Quest.h"

Quest::~Quest()
{
	for (int i = 0; i < actions.size(); i++) {
		actions[i] = NULL;
	}
	for (int i = 0; i < skills.size(); i++) {
		skills[i] = NULL;
	}
}

void Quest::Init(string name_, string description_, vector<Skills*> skills_,
	vector<int> skillsLevel_, vector<Action*> actions_, vector<int> timesFilled_,
	vector<int> quests, sf::Font* font, int index_)
{
	index = index_;

	//Intialise the quests texts for flip side 1.
	name.setString(name_);
	name.setFont(*font);
	name.setPosition(getPosition().x + 5, getPosition().y + 5);
	name.setCharacterSize(30);
	name.setFillColor(sf::Color::Black);
	
	description_ = GeneralFunctions::FormatLine(description_, maxLineSize);
	description.setString(description_);
	description.setFont(*font);
	description.setPosition(getPosition().x + 50, getPosition().y + 35);
	description.setCharacterSize(20);
	description.setFillColor(sf::Color::Black);

	hitbox.left = getPosition().x;
	hitbox.top = getPosition().y;
	hitbox.width = getSize().x;
	hitbox.height = getSize().y;

	skills = skills_;
	skillsLevel = skillsLevel_;
	actions = actions_;
	timesFilled = timesFilled_;
	questsOnComplete = quests;

	//Intialise the quests texts for flip side 2.
	for (int i = 0; i < skills.size(); i++) {
		skillText.push_back(sf::Text());
		skillText.back().setCharacterSize(20);
		skillText.back().setFont(*font);
		skillText.back().setFillColor(sf::Color::Black);
		skillText.back().setString(skills[i]->GetName() + ": " + to_string(skillsLevel[i]));
		skillText.back().setPosition(getPosition().x + 10.0f, getPosition().y + 10.0f + i * 40);
	}
}

bool Quest::IsComplete()
{
	for (int i = 0; i < skills.size(); i++) {
		if (skills[i]->GetLevel() < skillsLevel[i]) {
			return false;
		}
	}
	return true;
}

vector<int> Quest::GetQuestsOnComplete()
{
	return questsOnComplete;
}

void Quest::ResetPosition(sf::Vector2f position)
{
	setPosition(position);
	hitbox.left = position.x;
	hitbox.top = position.y;
	name.setPosition(position.x + 5, position.y + 5);
	description.setPosition(position.x + 50, position.y + 35);
	for (int i = 0; i < skills.size(); i++) {
		skillText[i].setPosition(getPosition().x + 10.0f, getPosition().y + 10.0f + i * 40);
	}
}

bool Quest::Collision(sf::Vector2f mouse_position)
{
	if (hitbox.contains(mouse_position)) {
		flip = !flip;
		return true;
	}
	return false;
}

//Render the quest's text.
void Quest::RenderQuestText(sf::RenderWindow* window)
{
	if (!flip) {
		window->draw(name);
		window->draw(description);
	}
	else {
		for (int i = 0; i < skillText.size(); i++) {
			window->draw(skillText[i]);
		}
	}

}

int Quest::GetIndex()
{
	return index;
}
