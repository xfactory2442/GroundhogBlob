#pragma once

#include "Tabs.h";

class LogTab : public Tabs
{
public:
	LogTab(sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);
	bool Update(float dt);
	void Render();
	
	void AddToLog(string text);

private:
	vector<sf::Text> log;
	const int maxLineSize = 82;
};