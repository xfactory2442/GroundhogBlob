#pragma once
#include "Tabs.h"

class TrainSkillsTab;

class ResetInfoTab : public Tabs
{
public:
	ResetInfoTab(TrainSkillsTab* trainSkillsTab_,
		sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);
	void Render();

	void AddAResetWindow(int resetNum);

private:
	void PushDownResetWindows(float backgroundSize);

	TrainSkillsTab* trainSkillsTab;
	struct ResetInfo {
		vector<sf::Text> changesText;
		sf::RectangleShape background;
	};

	vector<ResetInfo> resetInfo;

	int maxLineSize = 50;
};

