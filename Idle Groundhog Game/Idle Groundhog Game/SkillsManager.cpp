#include "SkillsManager.h"

void SkillsManager::Init(sf::Font* font, sf::RenderWindow* window)
{
	skills[0] = new Skills("Intelligence", 0, font, sf::Vector2f(window->getSize().x, 50));
	skills[1] = new Skills("Movement", 0, font, sf::Vector2f(window->getSize().x, 85));
	skills[2] = new Skills("Strength", 0, font, sf::Vector2f(window->getSize().x, 120));
}

void SkillsManager::AddSkill(Skills* skill)
{
	for (int i = 0; i < openSkills.size(); i++) {
		if (skill == openSkills[i]) {
			return;
		}
	}
	openSkills.push_back(skill);
}

void SkillsManager::AddSkill(int index)
{
	for (int i = 0; i < openSkills.size(); i++) {
		if (skills[index] == openSkills[i]) {
			return;
		}
	}
	openSkills.push_back(skills[index]);
}

Skills* SkillsManager::GetSkill(int index)
{
	return skills[index];
}

vector<Skills*> SkillsManager::GetOpenSkills()
{
	return openSkills;
}

int SkillsManager::Reset()
{
	int res = 0;
	for (int i = 0; i < openSkills.size(); i++) {
		res += openSkills[i]->Reset();
	}
	openSkills.clear();
	return res;
}

vector<int> SkillsManager::GetAllSkillsLevels()
{
	vector<int> skillLevels;
	for (int i = 0; i < NumSkills; i++) {
		skillLevels.push_back(skills[i]->GetLevel());
	}
	return skillLevels;
}

void SkillsManager::SetAllSkillsLevels(vector<int> skillLevels)
{
	for (int i = 0; i < NumSkills; i++) {
		skills[i]->SetLevel(skillLevels[i]);
	}
}
