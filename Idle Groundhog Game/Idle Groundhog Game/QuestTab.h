#pragma once
#include "Tabs.h"
#include "Skills.h"
#include "SkillsManager.h"
#include "Action.h"
#include "Quest.h"
#include <iostream>

class TrainSkillsTab;

using namespace std;

class QuestTab : public Tabs
{
public:
	QuestTab(TrainSkillsTab* trainSkillsTab_,
		sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);
	void AddQuest(int index);
	void RemoveQuest(int index);
	void CheckQuestsAtEndOfDay();
	void ReadInQuests();
	void Update(float dt);
	void Render();

	void Reset();

	vector<int> SaveQuests();
	void LoadQuests(vector<int> loadedQuests);

private:
	TrainSkillsTab* trainSkillsTab;

	//Holds the data for a future quest.
	struct QuestStruct {
		int index = 0;
		string name = "";
		string description = "";
		vector<Skills*> skills;
		vector<int> skillsLevel;
		vector<Action*> actions;
		vector<int> timesFinished;
		vector<int> questsWhenComplete;
	};

	//Holds all of the quests in the game.
	vector<QuestStruct> questHolder;
	//Holds the directory of the file holding the quests.
	const string fileName = "CSV_files/Quests.csv";

	//Holds the current active quests.
	vector<Quest> quests;
};

