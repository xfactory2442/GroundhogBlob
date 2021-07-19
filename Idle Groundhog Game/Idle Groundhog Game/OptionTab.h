#pragma once
#include "Tabs.h"
#include "SaveAndLoad.h"
class OptionTab : public Tabs
{
public:
	OptionTab(sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font_, LocationManager* location_);
	void SetUpSaveAndLoad(SaveAndLoad* saveAndLoad_);

	void Update();
	void Render();
private:
	SaveAndLoad* saveAndLoad;

	Button* saveButton;
	Button* loadButton;
};

