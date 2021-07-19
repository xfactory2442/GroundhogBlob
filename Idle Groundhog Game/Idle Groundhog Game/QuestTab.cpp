#include "QuestTab.h"
#include "TrainSkillsTab.h"
#include <string>
#include <fstream>
#include <sstream>


QuestTab::QuestTab(TrainSkillsTab* trainSkillsTab_,
	sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
	TimeClass* timeClass_, sf::Font* font_, LocationManager* location_)
	: Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
	trainSkillsTab = trainSkillsTab_;
}

void QuestTab::AddQuest(int index)
{
	if (index > -1) {
		quests.push_back(Quest());
		quests.back().setSize(sf::Vector2f(window->getSize().x - 120.0f, 200.0f));
		quests.back().setPosition(0.0f, 50.0f + (quests.size() - 1) * 200);
		quests.back().setFillColor(sf::Color::Green);
		quests.back().Init(questHolder[index].name, questHolder[index].description,
			questHolder[index].skills, questHolder[index].skillsLevel, questHolder[index].actions,
			questHolder[index].timesFinished, questHolder[index].questsWhenComplete, font, 
			questHolder[index].index);
	}
}

void QuestTab::RemoveQuest(int index)
{
	quests.erase(quests.begin() + index);
	for (int i = index; i < quests.size(); i++) {
		quests[i].ResetPosition(sf::Vector2f(0.0f, 50.0f + i * 200));
	}
}

void QuestTab::CheckQuestsAtEndOfDay()
{
	for (int i = 0; i < quests.size(); i++) {
		if (quests[i].IsComplete()) {
			vector<int> questsOnComplete = quests[i].GetQuestsOnComplete();
			for (int j = 0; j < questsOnComplete.size(); j++) {
				AddQuest(questsOnComplete[j]);
			}
			RemoveQuest(i);
		}
	}
}

void QuestTab::ReadInQuests() {
	ifstream file;
	//Open the quest file.
	file.open(fileName, ios::in, ios::binary);

	//Create the inital variables.
	string line, word, temp;
	vector<string> row;
	int numSkills = 0;
	int numActions = 0;
	int numQuests = 0;

	//Get the first line of the file.
	getline(file, line);
	stringstream si(line);

	while (getline(si, word, ',')) {
		row.push_back(word);
	}

	//Find out how many skill columns there are.
	int index = 2;
	do {
		if (row[index] == "Skill") {
			numSkills++;
		}
		else {
			break;
		}
		index += 2;
	} while (true);

	do {
		if (row[index] == "Action") {
			numActions++;
		}
		else {
			break;
		}
		index += 2;
	} while (true);

	numQuests = (int)row.size() - numSkills * 2 - numActions * 2 - 2;

	int num = 0;

	//For the rest of the lines, assign the names, descripton, skills and actions to their quests.
	while (file >> temp) {
		row.clear();

		getline(file, line);
		temp += line;

		stringstream s(temp);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		questHolder.push_back(QuestStruct());
		questHolder.back().name = GeneralFunctions::FormatReadInText(row[0]);
		cout << "Quest Name: " << questHolder.back().name << endl;
		questHolder.back().description = GeneralFunctions::FormatReadInText(row[1]);
		cout << "Quest Description: " << questHolder.back().description << endl;

		vector<Skills*> ski;
		vector<Action*> act;
		vector<int> level;
		vector<int> times;
		int in;
		for (int i = 2; i < numSkills * 2 + 2; i += 2) {
			in = i + 1;
			if (stoi(row[i]) > -1) {
				ski.push_back(skills->GetSkill(stoi(row[i])));
				cout << "Skill : " << stoi(row[i]) << endl;
				level.push_back(stoi(row[in]));
				cout << "Skill Level: " << stoi(row[in]) << endl;;
			}
		}
		for (int i = numSkills * 2 + 2; i < numSkills * 2 + 2 + numActions * 2; i+=2) {
			in = i + 1;
			if (stoi(row[i]) > -1) {
				act.push_back(trainSkillsTab->GetAction(stoi(row[i])));
				cout << "Action: " << stoi(row[i]) << endl;
				times.push_back(stoi(row[in]));
				cout << "Action Times: " << stoi(row[in]) << endl;
			}
		}
		for (int i = numSkills * 2 + 2 + numActions * 2; i < numSkills * 2 + 2 + numActions * 2 +  numQuests; i++) {
			questHolder.back().questsWhenComplete.push_back(stoi(row[i]));
			cout << "Quest: " << stoi(row[i]) << endl;
		}
		questHolder.back().skills = ski;
		questHolder.back().skillsLevel = level;
		questHolder.back().actions = act;
		questHolder.back().timesFinished = times;
		questHolder.back().index = num;
		num++;
	}

	file.close();
}

void QuestTab::Update(float dt)
{
	if (input->GetMouseLeftDown()) {
		for (int i = 0; i < quests.size(); i++) {
			if (quests[i].Collision(window->mapPixelToCoords(input->GetMouse()))) {
				input->SetMouseLeftDown(false);
				break;
			}
		}
	}
}

void QuestTab::Render()
{
	for (int i = 0; i < quests.size(); i++) {
		window->draw(quests[i]);
		quests[i].RenderQuestText(window);
	}
}

void QuestTab::Reset()
{
	quests.clear();
	AddQuest(0);
}

vector<int> QuestTab::SaveQuests()
{
	vector<int> savedQuests;
	for (int i = 0; i < quests.size(); i++) {
		savedQuests.push_back(quests[i].GetIndex());
	}
	return savedQuests;
}

void QuestTab::LoadQuests(vector<int> loadedQuests)
{
	quests.clear();
	for (int i = 0; i < loadedQuests.size(); i++) {
		AddQuest(loadedQuests[i]);
	}
}
