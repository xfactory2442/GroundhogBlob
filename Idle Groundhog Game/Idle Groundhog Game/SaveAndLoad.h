#pragma once
#include <iostream>
#include "QuestTab.h"
#include "TimeClass.h"
#include "LocationManager.h"

using namespace std;

class TrainSkillsTab;
class Unlocks;

class SaveAndLoad
{
public:
	struct ActionSave {
		float fill;
		float fillMax;
		float difficultyIncreaseMultiplier;
		float talent;
		int timesFilled;
	};

	SaveAndLoad(TrainSkillsTab* trainSkills_, QuestTab* questTab_, Unlocks* unlocks_,
		TimeClass* timeClass_, LocationManager* location_);

	void Save();
	void Load();

private:
	string fileName = "Saves/save.csv";
	int version = 0;

	TrainSkillsTab* trainSkills;
	QuestTab* questTab;
	Unlocks* unlocks;
	TimeClass* timeClass;
	LocationManager* location;
};

