#include "TrainSkillsTab.h"
#include "LogTab.h"

TrainSkillsTab::TrainSkillsTab(sf::Texture* bar_, sf::Texture* barOutline_, LogTab* logTab_,
	sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
	TimeClass* timeClass_, sf::Font* font_, LocationManager* location_)
	: Tabs(window_, inp, scene, skill, timeClass_, font_, location_)
{
	bar = bar_;
	barOutline = barOutline_;
	logTab = logTab_;

	CreateActions();
	UnlockAction("Think");
}

TrainSkillsTab::~TrainSkillsTab()
{
	bar = NULL;
	barOutline = NULL;
}

bool TrainSkillsTab::Update(float dt)
{
	for (int i = 0; i < action.size(); i++) {
		sf::Vector2f mousePosition = window->mapPixelToCoords(input->GetMouse());
		action[i]->CollideWithAction(mousePosition);
		if (input->GetMouseLeftDown()) {
			int buttonNumber = action[i]->CollideWithButtons(mousePosition);
			switch (buttonNumber) {
			case 0:
				timeClass->ClaimMorningBlock(action[i]);
				action[i]->SetButtonColourGreen(buttonNumber);
				input->SetMouseLeftDown(false);
				break;
			case 1:
				timeClass->ClaimAfternoonBlock(action[i]);
				action[i]->SetButtonColourGreen(buttonNumber);
				input->SetMouseLeftDown(false);
				break;
			case 2:
				timeClass->ClaimEveningBlock(action[i]);
				action[i]->SetButtonColourGreen(buttonNumber);
				input->SetMouseLeftDown(false);
				break;
			}
		}
	}
	return false;
}

void TrainSkillsTab::Render()
{
	//Render the actions.
	for (int i = 0; i < action.size(); i++) {
		action[i]->RenderAction(window);
	}
}

void TrainSkillsTab::RenderUI()
{
	//Render the actions.
	for (int i = 0; i < action.size(); i++) {
		action[i]->RenderUI(window);
	}
}

void TrainSkillsTab::ChangeLocation()
{
	action.clear();
	for (int i = 0; i < numActions; i++) {
		vector<LocationManager::Location> locationsWhereAvailable =
			allActions[i]->GetLocationsWhereAvailable();
		for (int j = 0; j < locationsWhereAvailable.size(); j++) {
			if (locationsWhereAvailable[j] == location->GetLocation() 
				&& allActions[i]->GetUnlocked()) {
				action.push_back(allActions[i]);
				action.back()->SetPosition(sf::Vector2f(10.0f, 5.0f + 50.0f * 
					(float)(action.size() - 1)));
				break;
			}
		}
	}
}

void TrainSkillsTab::UnlockAction(int i)
{
	allActions[i]->SetUnlocked(true);
	vector<LocationManager::Location> locationsWhereAvailable = 
		allActions[i]->GetLocationsWhereAvailable();
	for (int j = 0; j < locationsWhereAvailable.size(); j++) {
		if (locationsWhereAvailable[j] == location->GetLocation()) {
			AddAction(i);
			return;
		}
	}
}

void TrainSkillsTab::UnlockAction(string s)
{
	for (int i = 0; i < numActions; i++) {
		if (allActions[i]->GetName() == s) {
			UnlockAction(i);
			break;
		}
	}
	
}

void TrainSkillsTab::AddAction(int i)
{
	action.push_back(allActions[i]);
	action.back()->SetPosition(sf::Vector2f(10.0f, 55.0f + 50.0f * (float)(action.size() - 1)));
	if (action.back()->GetUnlockText().size() > 0) {
		logTab->AddToLog(action.back()->GetUnlockText());
	}
	for (int i = 0; i < action.back()->GetSkills().size(); i++) {
		skills->AddSkill(action.back()->GetSkills()[i]);
	}
}

Action* TrainSkillsTab::GetAction(int i)
{
	return allActions[i];
}

vector<string> TrainSkillsTab::GetResetData()
{
	vector<string> s;
	for (int i = 0; i < action.size(); i++) {
		if (action[i]->GetTimesCompleted() > 0) {
			s.push_back("Action " + action[i]->GetName() + " was completed "
				+ to_string(action[i]->GetTimesCompleted()) + " times giving additional talent of "
				+ GeneralFunctions::FormatNumber(action[i]->CalculateTalent()) + ".");
		}
	}
	return s;
}

void TrainSkillsTab::ResetDay()
{
	for (int i = 0; i < action.size(); i++) {
		action[i]->ResetActionDay();
	}
}

int TrainSkillsTab::Reset()
{
	int res = skills->Reset();
	for (int i = 0; i < numActions; i++) {
		allActions[i]->Reset();
	}
	action.clear();
	UnlockAction(0);
	return res;
}

vector<int> TrainSkillsTab::SaveSkills()
{
	vector<int> skillLevel;
	skillLevel = skills->GetAllSkillsLevels();
	return skillLevel;
}

void TrainSkillsTab::LoadSkills(vector<int> skill)
{
	skills->SetAllSkillsLevels(skill);
}

vector<SaveAndLoad::ActionSave> TrainSkillsTab::SaveAction()
{
	vector<SaveAndLoad::ActionSave> actionSave;

	for (int i = 0; i < numActions; i++) {
		actionSave.push_back(SaveAndLoad::ActionSave());
		actionSave.back().timesFilled = allActions[i]->GetTimesCompleted();
		actionSave.back().difficultyIncreaseMultiplier = allActions[i]->GetDifficultyIncrease();
		actionSave.back().fill = allActions[i]->GetFill();
		actionSave.back().fillMax = allActions[i]->GetFillMax();
		actionSave.back().talent = allActions[i]->GetTalent();
	}

	return actionSave;
}

void TrainSkillsTab::LoadAction(vector<SaveAndLoad::ActionSave> actionSave)
{
	for (int i = 0; i < numActions; i++) {
		allActions[i]->SetTalent(actionSave[i].talent);
		allActions[i]->SetFill(actionSave[i].fill);
		allActions[i]->SetMaxFill(actionSave[i].fillMax);
		allActions[i]->SetTimesFilled(actionSave[i].timesFilled);
		allActions[i]->SetDifficultyIncrease(actionSave[i].difficultyIncreaseMultiplier);
		allActions[i]->FormatFillBar();
	}
	action.clear();
	AddAction(0);
}

void TrainSkillsTab::CreateActions()
{
	//Initalise all Actions.

	//Initlialise the vectors.
	vector<Skills*> actionSkills;
	vector<LocationManager::Location> locationsWhereAvailable;

	//Action 1 - Think.
	actionSkills.push_back(skills->GetSkill(0));
	locationsWhereAvailable.push_back(LocationManager::Location::Forest);
	allActions[0] = new Action(locationsWhereAvailable, "Think", 
		"The blob tries to use its brain.", actionSkills, sf::Vector2f(10.0f, 55.0f), bar,
		barOutline, font);
	actionSkills.clear();
	locationsWhereAvailable.clear();

	//Action 2 - Move.
	actionSkills.push_back(skills->GetSkill(1));
	locationsWhereAvailable.push_back(LocationManager::Location::Forest);
	allActions[1] = new Action(locationsWhereAvailable, "Move",
		"The blob tries to move its mass around.", actionSkills, sf::Vector2f(10.0f, 105.0f),
		bar, barOutline, font, 450.0f, 300.0f, 20.0f,
		"The blob realises that it should probably learn to move around.");
	actionSkills.clear();
	locationsWhereAvailable.clear();

	//Action 3 - Grab.
	actionSkills.push_back(skills->GetSkill(1));
	actionSkills.push_back(skills->GetSkill(2));
	locationsWhereAvailable.push_back(LocationManager::Location::Forest);
	allActions[2] = new Action(locationsWhereAvailable, "Grab",
		"The blob tries to pick up the stick.",
		actionSkills, sf::Vector2f(10.0f, 155.0f), bar, barOutline, font, 450.0f, 700.0f, 20.0f,
		"The blob spots a stick and decides to try and pick it up. It might be useful.");
	actionSkills.clear();
	locationsWhereAvailable.clear();
}
