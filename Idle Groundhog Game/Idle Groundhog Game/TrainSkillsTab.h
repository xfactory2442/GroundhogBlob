#pragma once
#include "Tabs.h"
#include "Action.h"
#include "SkillsManager.h"
#include "SaveAndLoad.h"

class LogTab;

class TrainSkillsTab : public Tabs
{
public:
	TrainSkillsTab(sf::Texture* bar_, sf::Texture* barOutline_, LogTab* logTab_,
		sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);
	~TrainSkillsTab();
	bool Update(float dt);
	void Render();
	void RenderUI();

	void ChangeLocation();
	void UnlockAction(int i);
	void UnlockAction(string s);
	void AddAction(int i);
	Action* GetAction(int i);

	vector<string> GetResetData();
	void ResetDay();
	int Reset();

	vector<int> SaveSkills();
	void LoadSkills(vector<int> skill);
	vector<SaveAndLoad::ActionSave> SaveAction();
	void LoadAction(vector<SaveAndLoad::ActionSave> actionSave);

private:
	void CreateActions();
	LogTab* logTab;
	vector<Action*> action;
	static const int numActions = 3;
	Action* allActions[numActions];

	sf::Texture* bar;
	sf::Texture* barOutline;
};

