#pragma once
#include "Tabs.h"

class BasicTabBackground : public Tabs
{
public:
	BasicTabBackground(sf::RenderWindow* window_, Input* inp, SceneManager* scene, 
		SkillsManager* skill, TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);

	void UpdateDay();

	void RenderStart();
	void RenderUI();
	void RenderEnd();
	
	void SetDayText();
	void SetLifespanText();

	void UnlockTab(int index);
	void UnlockTab(string s);

private:
	Button* nextDayButton;

	sf::Text dayText;
	sf::Text lifeSpanText;

	sf::RectangleShape skillsSection;
	sf::RectangleShape tabBackground;
	int static const numSceneButtons = 6;
	Button* sceneButtons[numSceneButtons];
	vector<Button*> unlockedTabButtons;
	
};

