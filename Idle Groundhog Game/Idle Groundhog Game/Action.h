#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#include "Skills.h"
#include "Button.h"
#include "GeneralFunctions.h"
#include "LocationManager.h"

using namespace std;
class Action
{
public:
	Action(vector<LocationManager::Location> locationsWhereAvailable_, 
		string name_, string logString_, vector<Skills*> actionsSkills,
		sf::Vector2f position, sf::Texture* barTexture, 
		sf::Texture* barOutlineTexture, sf::Font* font, float barSize_ = 450.0f,
		float fillMax_ = 100, float fillAmount_ = 20, string unlockText_ = "");
	
	string GetLogString();
	string GetUnlockText();
	vector<Skills*> GetSkills();
	int GetTimesCompleted();
	string GetName();
	float GetFill();
	float GetFillMax();
	float GetDifficultyIncrease();
	float GetTalent();
	int GetTimesFilled();

	void SetFill(float fill_);
	void SetMaxFill(float maxFill_);
	void SetDifficultyIncrease(float difficultyIncrease_);
	void SetTalent(float talent_);
	void SetTimesFilled(int timesFilled_);

	void DoAction();
	int CollideWithButtons(sf::Vector2f mousePosition);
	void CollideWithAction(sf::Vector2f mousePosition);
	void FormatFillBar();

	void SetButtonColourRed(int i);
	void SetButtonColourGreen(int i);

	void RenderAction(sf::RenderWindow* window);
	void RenderUI(sf::RenderWindow* window);

	vector<LocationManager::Location> GetLocationsWhereAvailable();

	void SetUnlocked(bool unlocked_);
	bool GetUnlocked();

	void SetPosition(sf::Vector2f position);

	void ResetActionDay();

	float CalculateTalent();
	void Reset();

private:
	bool unlocked = false;
	vector<LocationManager::Location> locationsWhereAvailable;
	string name;
	string unlockText;
	string logString;
	float fill = 0.0f;
	float fillMax;
	float initFillMax;
	float fillAdd;
	float initFillDifficultyIncrease = 1.04f;
	float fillDifficultyIncrease = initFillDifficultyIncrease;
	float difficultyIncreaseMultiplier = 0.01f;
	float talent = 1.0f;
	int difficultyIncreaseLevel = 20;
	int maxTimesFilledInOneDay = 5;
	int timesFilledInDay = 0;
	int timesFilled = 0;

	vector<Skills*> skills;
	Button* buttons[3];

	float barSize;
	sf::Text barName;
	sf::FloatRect nameHitbox;
	sf::RectangleShape bar;
	sf::RectangleShape barOutline;
	sf::FloatRect barHitbox;

	bool showTalent = false;
	sf::Text talentText;
	sf::RectangleShape talentBox;

	bool showFillAmount = false;
	sf::Text fillText;
	sf::RectangleShape fillBox;
};

