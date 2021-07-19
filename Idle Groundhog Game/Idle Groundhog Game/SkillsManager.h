#pragma once
#include "Skills.h"
class SkillsManager
{
public:
	void Init(sf::Font* font, sf::RenderWindow* window);
	void AddSkill(Skills* skill);
	void AddSkill(int index);
	Skills* GetSkill(int index);
	vector<Skills*> GetOpenSkills();

	int Reset();

	vector<int> GetAllSkillsLevels();
	void SetAllSkillsLevels(vector<int> skillLevels);

private:
	static int const NumSkills = 3;
	//Create array of skills.
	Skills* skills[NumSkills];
	vector<Skills*> openSkills;
};

