#pragma once
#include "Skills.h"
#include "TrainSkillsTab.h"
#include "BasicTabBackground.h"
#include "TravelTab.h"
#include "LocationManager.h"
#include <iostream>

using namespace std;

class SkillsManager;

class Unlocks
{
public:
	struct UnlockRequirements {
		map<Skills*, int> skillRequirement;
		map<string, string> unlocks;
		vector<LocationManager::Location> locationsWhereAvailable;
		int num;
		std::vector<uint32_t> new_unlocks;
	};

	Unlocks(SkillsManager* skill, TrainSkillsTab* trainSkills_, BasicTabBackground* background_,
		TravelTab* travelTab_, LocationManager* location);
	void Unlock();
	void AddUnlock(int index);

	void Reset();

	vector<int> SaveUnlocks();
	void LoadUnlocks(vector<int> unlocks);

private:
	void UnlockUnlocks(UnlockRequirements current, int i);

	SkillsManager* skills;
	TrainSkillsTab* trainSkills;
	BasicTabBackground* background;
	TravelTab* travelTab;
	LocationManager* location;
	
	const int numUnlocks = 7;
	vector<UnlockRequirements> unlockRequirements;
	vector<UnlockRequirements> requirementsHolder;
};