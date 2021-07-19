#pragma once
#include "Input.h"
#include "SceneManager.h"
#include <SFML/Graphics.hpp>
#include "Skills.h"
#include "TimeClass.h"
#include "Button.h"
#include "SkillsManager.h"
#include "GeneralFunctions.h"
#include "LocationManager.h"

class Tabs
{
public:
	Tabs(sf::RenderWindow* window_, Input* inp, SceneManager* scene, SkillsManager* skill,
		TimeClass* timeClass_, sf::Font* font, LocationManager* location_);

protected:
	sf::RenderWindow* window;
	Input* input;
	SceneManager* sceneManager;
	SkillsManager* skills;
	TimeClass* timeClass;
	sf::Font* font;
	LocationManager* location;
};

