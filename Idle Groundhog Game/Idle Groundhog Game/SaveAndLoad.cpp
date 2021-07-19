#include "SaveAndLoad.h"
#include <string>
#include <fstream>
#include <sstream>
#include "TrainSkillsTab.h"
#include "Unlocks.h"

SaveAndLoad::SaveAndLoad(TrainSkillsTab* trainSkills_, QuestTab* questTab_, Unlocks* unlocks_, 
	TimeClass* timeClass_, LocationManager* location_)
{
	trainSkills = trainSkills_;
	questTab = questTab_;
	unlocks = unlocks_;
	timeClass = timeClass_;
	location = location_;
}

void SaveAndLoad::Save()
{
	ofstream file;
	//Open the quest file.
	file.open(fileName);

	vector<int> skillLevels = trainSkills->SaveSkills();
	string s;

	file << version << "\n";

	for (int i = 0; i < skillLevels.size(); i++) {
		s += "S,";
		s += to_string(skillLevels[i]);
		s += "\n";
	}
	file << s;
	
	vector<ActionSave> actionSave = trainSkills->SaveAction();
	s = "";
	for (int i = 0; i < actionSave.size(); i++) {
		s = "A,";
		s += to_string(actionSave[i].fill) + ",";
		s += to_string(actionSave[i].fillMax) + ",";
		s += to_string(actionSave[i].difficultyIncreaseMultiplier) + ",";
		s += to_string(actionSave[i].timesFilled) + ",";
		s += to_string(actionSave[i].talent);
		s += "\n";
		file << s;
	}

	skillLevels = questTab->SaveQuests();
	for (int i = 0; i < skillLevels.size(); i++) {
		s = "Q,";
		s += to_string(skillLevels[i]);
		s += "\n";
		file << s;
	}

	vector<int> saveUnlocks = unlocks->SaveUnlocks();
	for (int i = 0; i < saveUnlocks.size(); i++) {
		s = "U,";
		s += to_string(saveUnlocks[i]);
		s += "\n";
		file << s;
	}

	s = "T," + to_string(timeClass->GetDay()) + "," + to_string(timeClass->GetLifeSpan()) + ","
		+ to_string(timeClass->GetNumResets()) + "," + to_string(timeClass->GetDayOfHunterStart())
		+ "," + to_string(timeClass->GetChanceOfHunter()) + "," + 
		to_string(timeClass->GetNumHunterDeaths()) + "\n";

	file << s;

	s = "L," + to_string((int)location->GetLocation()) + "\n";

	file << s;

	file.close();
}

void SaveAndLoad::Load()
{
	fstream file;
	//Open the quest file.
	file.open(fileName);

	//Create the inital variables.
	string line, word, temp;
	vector<string> row;

	vector<int> skillLevels;
	vector<ActionSave> actionSave;
	vector<int> quest;
	vector<int> unlock;
	int locationNum = 0;

	//Get the first line of the file.
	getline(file, line);
	stringstream si(line);

	while (getline(si, word, ',')) {
		row.push_back(word);
	}
	 
	bool load = false;
	if (stoi(row[0]) == version) {
		load = true;
	}

	while (file >> temp && load) {
		row.clear();

		getline(file, line);
		temp += line;

		stringstream s(temp);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		if (row[0] == "S") {
			skillLevels.push_back(stoi(row[1]));
		} 
		else if (row[0] == "A") {
			actionSave.push_back(ActionSave());
			actionSave.back().fill = (float)stoi(row[1]);
			actionSave.back().fillMax = (float)stoi(row[2]);
			actionSave.back().difficultyIncreaseMultiplier = (float)stoi(row[3]);
			actionSave.back().timesFilled = stoi(row[4]);
			actionSave.back().talent = (float)stoi(row[5]);
		}
		else if (row[0] == "Q") {
			quest.push_back(stoi(row[1]));
		}
		else if (row[0] == "U") {
			unlock.push_back(stoi(row[1]));
		}
		else if (row[0] == "T") {
			timeClass->SetDay(stoi(row[1]));
			timeClass->SetLifeSpan(stoi(row[2]));
			timeClass->SetNumberOfResets(stoi(row[3]));
			timeClass->SetDayOfHunterStart(stoi(row[4]));
			timeClass->SetChanceOfHunter((float)stoi(row[5]));
			timeClass->SetNumHunterDeaths(stoi(row[6]));
		}
		else if (row[0] == "L") {
			locationNum = stoi(row[1]);
		}
	}

	trainSkills->LoadSkills(skillLevels);
	trainSkills->LoadAction(actionSave);
	questTab->LoadQuests(quest);
	unlocks->LoadUnlocks(unlock);

	location->SetLocation(locationNum);
	timeClass->UnclaimAllBlocks();
}
