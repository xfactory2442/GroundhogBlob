#include "TimeClass.h"
#include "LogTab.h"
#include "Unlocks.h"
#include "QuestTab.h"
#include "ResetInfoTab.h"
#include "BasicTabBackground.h"
#include "TravelTab.h"
#include <algorithm>

void TimeClass::Init(LogTab* logTab_, Unlocks* unlocks_, QuestTab* questTab_,
	TrainSkillsTab* skillsTab_, ResetInfoTab* resetInfoTab_, BasicTabBackground* tabBackground_,
	sf::RenderWindow* window_, sf::Font* font_, Input* input_, TravelTab* travelTab_)
{
	logTab = logTab_;
	unlocks = unlocks_;
	questTab = questTab_;
	trainSkillsTab = skillsTab_;
	resetInfoTab = resetInfoTab_;
	tabBackground = tabBackground_;
	window = window_;
	font = font_;
	input = input_;
	travelTab = travelTab_;

	infoWindow = new InfoWindow(window, font);
}

void TimeClass::ClaimMorningBlock(Action* action)
{
	if (morningBlock) {
		morningBlock->SetButtonColourRed(0);
	}
	morningBlock = action;
}

void TimeClass::ClaimAfternoonBlock(Action* action)
{
	if (afternoonBlock) {
		afternoonBlock->SetButtonColourRed(1);
	}
	afternoonBlock = action;
}

void TimeClass::ClaimEveningBlock(Action* action)
{
	if (eveningBlock) {
		eveningBlock->SetButtonColourRed(2);
	}
	eveningBlock = action;
}

void TimeClass::UnclaimAllBlocks()
{
	if (morningBlock != NULL && morningBlock->GetName() != "Think") {
		morningBlock->SetButtonColourRed(0);
		morningBlock = NULL;
	}
	if (afternoonBlock != NULL && afternoonBlock->GetName() != "Think") {
		afternoonBlock->SetButtonColourRed(1);
		afternoonBlock = NULL;
	}
	if (eveningBlock != NULL && eveningBlock->GetName() != "Think") {
		eveningBlock->SetButtonColourRed(2);
		eveningBlock = NULL;
	}
}

void TimeClass::AdvanceDay()
{
	day++;
	string s = "Day " + to_string(day) + ":";
	logTab->AddToLog(s);
	if (morningBlock) {
		morningBlock->DoAction();
		s = "	(Morning): " + morningBlock->GetLogString();
		logTab->AddToLog(s);
	}
	if (afternoonBlock) {
		afternoonBlock->DoAction();
		s = "	(Afternoon): " + afternoonBlock->GetLogString();
		logTab->AddToLog(s);
	}
	if (eveningBlock) {
		eveningBlock->DoAction();
		s = "	(Evening): " + eveningBlock->GetLogString();
		logTab->AddToLog(s);
	}

	Reset();
}

void TimeClass::AdvanceDayByTravel(int numDays)
{
	day += numDays;
	tabBackground->SetDayText();

	Reset();
}

void TimeClass::Update()
{
	if (input->GetMouseLeftDown() && infoWindow->isAlive()
		&& infoWindow->Collsion(window->mapPixelToCoords(input->GetMouse()))) {
		input->SetMouseLeftDown(false);
	}
}

void TimeClass::Render()
{
	if (infoWindow->isAlive()) {
		window->draw(*infoWindow);
		infoWindow->Render(window);
	}
}

bool TimeClass::CheckResets()
{
	//Do every other form of death before checking for lifespan.
	//Randomise a percentage.
	int percent = rand() % 101;
	//If the hunter is supposed to be active and the percentage is lower than the chance of 
	//hunter, reset the game and the chance of hunter.
	if (day >= dayOfHunterStart) {
		if (percent < chanceOfHunter) {
			infoWindow->ShowWindow("A hunter has come and killed you!");
			cout << "\nDeath by Hunter." << endl;
			numHunterDeaths++;
			if (numHunterDeaths % 5 == 0 && dayOfHunterStart > 5) {
				cout << "The hunter is getting better at predicting the blobs moves...\n";
				dayOfHunterStart--;
			}
			cout << endl;
			return true;
		}
		chanceOfHunter += 5;
	}

	if (lifeSpan <= day) {
		logTab->AddToLog("The blob died of natural causes.");
		infoWindow->ShowWindow("The blob died of natural causes.");
		return true;
	}
	return false;
}

int TimeClass::GetDay()
{
	return day;
}

void TimeClass::SetDay(int day_)
{
	day = day_;
	tabBackground->SetDayText();
}

int TimeClass::GetNumResets()
{
	return numberOfResets;
}

void TimeClass::SetNumberOfResets(int numberOfResets_)
{
	numberOfResets = numberOfResets_;
}

int TimeClass::GetLifeSpan()
{
	return lifeSpan;
}

void TimeClass::SetLifeSpan(int lifeSpan_)
{
	lifeSpan = lifeSpan_;
	tabBackground->SetLifespanText();
}

int TimeClass::GetNumHunterDeaths()
{
	return numHunterDeaths;
}

void TimeClass::SetNumHunterDeaths(int numHunterDeaths_)
{
	numHunterDeaths = numHunterDeaths_;
}

float TimeClass::GetChanceOfHunter()
{
	return chanceOfHunter;
}

void TimeClass::SetChanceOfHunter(float chanceOfHunter_)
{
	chanceOfHunter = chanceOfHunter_;
}

int TimeClass::GetDayOfHunterStart()
{
	return dayOfHunterStart;
}

void TimeClass::SetDayOfHunterStart(int dayOfHunter)
{
	dayOfHunterStart = dayOfHunter;
}

void TimeClass::Reset()
{
	trainSkillsTab->ResetDay();
	unlocks->Unlock();

	if (CheckResets()) {
		day = 0;
		if (numHunterDeaths > 0) {
			chanceOfHunter = 10;
		}
		numberOfResets++;
		resetInfoTab->AddAResetWindow(numberOfResets);
		lifeSpan = minLifeSpan + (int)floor((float)trainSkillsTab->Reset() / 10.0f);
		tabBackground->SetLifespanText();
		tabBackground->UnlockTab("Reset Info");
		questTab->Reset();
		unlocks->Reset();
		travelTab->Reset();

		UnclaimAllBlocks();
		return;
	}

	questTab->CheckQuestsAtEndOfDay();
}
