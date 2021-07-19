#include "Unlocks.h"
#include "SkillsManager.h"

Unlocks::Unlocks(SkillsManager* skill, TrainSkillsTab* trainSkills_, 
	BasicTabBackground* background_, TravelTab* travelTab_, LocationManager* location_)
{
	skills = skill;
	trainSkills = trainSkills_;
	background = background_;
	travelTab = travelTab_;
	location = location_;

	AddUnlock(0);

	Reset();
}

void Unlocks::Unlock()
{
	for (int i = 0; i < unlockRequirements.size(); i++) {
		bool allSkills = true;
		bool locationComplete = false;
		UnlockRequirements current = unlockRequirements[i];
		map<Skills*, int>::iterator it = current.skillRequirement.begin();
		for (pair<Skills*, int> element : current.skillRequirement) {
			if (element.first->GetLevel() < element.second) {
				allSkills = false;
				break;
			}
		}
		if (current.locationsWhereAvailable.size() > 0) {
			for (LocationManager::Location location_ : current.locationsWhereAvailable) {
				if (location_ == location->GetLocation()) {
					locationComplete = true;
					break;
				}
			}
		}
		else {
			locationComplete = true;
		}

		if (allSkills && locationComplete) {
			UnlockUnlocks(current, i);
			i--;
		}
	}
}

void Unlocks::AddUnlock(int index)
{
	switch (index) {
	case 0:
		requirementsHolder.push_back(UnlockRequirements());
		requirementsHolder.back().num = 0;
		requirementsHolder.back().skillRequirement.insert(std::pair<Skills*, int>(skills->GetSkill(0), 2));
		requirementsHolder.back().unlocks.insert(std::pair<string, string>("TrainSkills", "Move"));
		requirementsHolder.back().new_unlocks.push_back(1);
		break;
		
	case 1:
		requirementsHolder.push_back(UnlockRequirements());
		requirementsHolder.back().num = 1;
		requirementsHolder.back().skillRequirement.insert(std::pair<Skills*, int>(skills->GetSkill(1), 5));
		requirementsHolder.back().unlocks.insert(std::pair<string, string>("TrainSkills", "Strength"));
		requirementsHolder.back().new_unlocks.push_back(2);
		break;

	case 2:
		requirementsHolder.push_back(UnlockRequirements());
		requirementsHolder.back().num = 2;
		requirementsHolder.back().skillRequirement.insert(std::pair<Skills*, int>(skills->GetSkill(0), 1));
		requirementsHolder.back().unlocks.insert(std::pair<string, string>("Tab", "Quests"));
		requirementsHolder.back().new_unlocks.push_back(3);
		requirementsHolder.back().new_unlocks.push_back(4);
		break;

	case 3:
		requirementsHolder.push_back(UnlockRequirements());
		requirementsHolder.back().num = 3;
		requirementsHolder.back().skillRequirement.insert(std::pair<Skills*, int>(skills->GetSkill(1), 5));
		requirementsHolder.back().unlocks.insert(std::pair<string, string>("Tab", "Travel"));
		break;

	case 4:
		requirementsHolder.push_back(UnlockRequirements());
		requirementsHolder.back().num = 4;
		requirementsHolder.back().skillRequirement.insert(std::pair<Skills*, int>(skills->GetSkill(0), 20));
		requirementsHolder.back().skillRequirement.insert(std::pair<Skills*, int>(skills->GetSkill(1), 10));
		requirementsHolder.back().unlocks.insert(std::pair<string, string>("Location", "Area Just Outside Town"));
		break;
	}
	unlockRequirements.push_back(requirementsHolder.back());
}

void Unlocks::Reset()
{
	unlockRequirements = requirementsHolder;
}

vector<int> Unlocks::SaveUnlocks()
{
	vector<int> unlocks;

	for (int i = 0; i < unlockRequirements.size(); i++) {
		unlocks.push_back(unlockRequirements[i].num);
	}

	return unlocks;
}

void Unlocks::LoadUnlocks(vector<int> unlocks)
{
	unlockRequirements.clear();
	int j = 0;
	for (int i = 0; i < numUnlocks; i++) {
		unlockRequirements.push_back(requirementsHolder[i]);
		if (unlockRequirements.back().num != unlocks[j]) {
			UnlockUnlocks(unlockRequirements.back(), j);
		}
		else {
			j++;
		}
	}
}

void Unlocks::UnlockUnlocks(UnlockRequirements current, int i)
{
	map< string, string>::iterator itter = current.unlocks.begin();
	for (pair< string, string> ele : current.unlocks) {
		if (ele.first == "TrainSkills") {
			trainSkills->UnlockAction(ele.second);
		}
		else if (ele.first == "Tab") {
			background->UnlockTab(ele.second);
		}
		else if (ele.first == "Location") {
			travelTab->AddTravelNode(ele.second);
		}
	}
	for (int i = 0; i < unlockRequirements[i].new_unlocks.size(); i++) {
		AddUnlock(unlockRequirements[i].new_unlocks[i]);
	}
	unlockRequirements.erase(unlockRequirements.begin() + i);
	
}
