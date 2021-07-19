#pragma once
#include "Action.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "Input.h"
#include "InfoWindow.h"

using namespace std;

class LogTab;
class Unlocks;
class QuestTab;
class TrainSkillsTab;
class ResetInfoTab;
class BasicTabBackground;
class TravelTab;

class TimeClass
{
public:
	void Init(LogTab* logTab_, Unlocks* unlocks_, QuestTab* questTab_, 
		TrainSkillsTab* skillsTab_, ResetInfoTab* resetInfoTab_, 
		BasicTabBackground* tabBackground_, sf::RenderWindow* window_, sf::Font* font_,
		Input* input_, TravelTab* travelTab_);
	void ClaimMorningBlock(Action* action);
	void ClaimAfternoonBlock(Action* action);
	void ClaimEveningBlock(Action* action);
	void UnclaimAllBlocks();
	void AdvanceDay();
	void AdvanceDayByTravel(int numDays);
	void Update();
	void Render();
	bool CheckResets();

	//Get and setters for saving;
	int GetDay();
	void SetDay(int day_);
	int GetNumResets();
	void SetNumberOfResets(int numberOfResets_);
	int GetLifeSpan();
	void SetLifeSpan(int lifeSpan_);
	int GetNumHunterDeaths();
	void SetNumHunterDeaths(int numHunterDeaths_);
	float GetChanceOfHunter();
	void SetChanceOfHunter(float chanceOfHunter_);
	int GetDayOfHunterStart();
	void SetDayOfHunterStart(int dayOfHunter);

private:
	void Reset();

	LogTab* logTab;
	Unlocks* unlocks;
	QuestTab* questTab;
	TrainSkillsTab* trainSkillsTab;
	ResetInfoTab* resetInfoTab;
	BasicTabBackground* tabBackground;
	sf::RenderWindow* window;
	sf::Font* font;
	Input* input;
	TravelTab* travelTab;

	Action* morningBlock = NULL;
	Action* afternoonBlock = NULL;
	Action* eveningBlock = NULL;

	InfoWindow* infoWindow;

	int day = 0;
	int numberOfResets = 0;

	const int minLifeSpan = 10;
	int lifeSpan = minLifeSpan;

	int numHunterDeaths = 0;
	float chanceOfHunter = 100;
	int dayOfHunterStart = 15;
};

